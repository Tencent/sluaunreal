/*=========================================================================*\
* Unix domain socket 
* LuaSocket toolkit
\*=========================================================================*/


#include <string.h> 

#include "lua.h"
#include "lauxlib.h"

#include "auxiliar.h"
#include "socket.h"
#include "options.h"
#include "unix.h"

#ifndef _WIN32
#include <sys/un.h> 
#endif // _WIN32

namespace NS_SLUA {    

/*=========================================================================*\
* Internal function prototypes
\*=========================================================================*/
static int unix_global_create(lua_State *L);
static int unix_meth_connect(lua_State *L);
static int unix_meth_listen(lua_State *L);
static int unix_meth_bind(lua_State *L);
static int unix_meth_send(lua_State *L);
static int unix_meth_shutdown(lua_State *L);
static int unix_meth_receive(lua_State *L);
static int unix_meth_accept(lua_State *L);
static int unix_meth_close(lua_State *L);
static int unix_meth_setoption(lua_State *L);
static int unix_meth_settimeout(lua_State *L);
static int unix_meth_getfd(lua_State *L);
static int unix_meth_setfd(lua_State *L);
static int unix_meth_dirty(lua_State *L);
static int unix_meth_getstats(lua_State *L);
static int unix_meth_setstats(lua_State *L);

static const char *unix_tryconnect(p_unix un, const char *path);
static const char *unix_trybind(p_unix un, const char *path);

/* unix object methods */
static luaL_Reg unix_methods[] = {
    {"__gc",        unix_meth_close},
    {"__tostring",  auxiliar_tostring},
    {"accept",      unix_meth_accept},
    {"bind",        unix_meth_bind},
    {"close",       unix_meth_close},
    {"connect",     unix_meth_connect},
    {"dirty",       unix_meth_dirty},
    {"getfd",       unix_meth_getfd},
    {"getstats",    unix_meth_getstats},
    {"setstats",    unix_meth_setstats},
    {"listen",      unix_meth_listen},
    {"receive",     unix_meth_receive},
    {"send",        unix_meth_send},
    {"setfd",       unix_meth_setfd},
    {"setoption",   unix_meth_setoption},
    {"setpeername", unix_meth_connect},
    {"setsockname", unix_meth_bind},
    {"settimeout",  unix_meth_settimeout},
    {"shutdown",    unix_meth_shutdown},
    {NULL,          NULL}
};

/* socket option handlers */
static t_opt unix_optset[] = {
    {"keepalive",   opt_set_keepalive},
    {"reuseaddr",   opt_set_reuseaddr},
    {"linger",      opt_set_linger},
    {NULL,          NULL}
};

/* our socket creation function */
/* this is an ad-hoc module that returns a single function 
 * as such, do not include other functions in this array. */
static luaL_Reg unix_func[] = {
    {"unix", unix_global_create},
    {NULL,          NULL}
};


/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
int luaopen_socket_unix(lua_State *L) {
    /* create classes */
    auxiliar_newclass(L, "unix{master}", unix_methods);
    auxiliar_newclass(L, "unix{client}", unix_methods);
    auxiliar_newclass(L, "unix{server}", unix_methods);
    /* create class groups */
    auxiliar_add2group(L, "unix{master}", "unix{any}");
    auxiliar_add2group(L, "unix{client}", "unix{any}");
    auxiliar_add2group(L, "unix{server}", "unix{any}");
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
    lua_pushcfunction(L, unix_global_create);
    (void)unix_func;
#else
    /* set function into socket namespace */
    luaL_openlib(L, "socket", unix_func, 0);
    lua_pushcfunction(L, unix_global_create);
#endif
    /* return the function instead of the 'socket' table */
    return 1;
}

/*=========================================================================*\
* Lua methods
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Just call buffered IO methods
\*-------------------------------------------------------------------------*/
static int unix_meth_send(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{client}", 1);
    return buffer_meth_send(L, &un->buf);
}

static int unix_meth_receive(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{client}", 1);
    return buffer_meth_receive(L, &un->buf);
}

static int unix_meth_getstats(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{client}", 1);
    return buffer_meth_getstats(L, &un->buf);
}

static int unix_meth_setstats(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{client}", 1);
    return buffer_meth_setstats(L, &un->buf);
}

/*-------------------------------------------------------------------------*\
* Just call option handler
\*-------------------------------------------------------------------------*/
static int unix_meth_setoption(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    return opt_meth_setoption(L, unix_optset, &un->sock);
}

/*-------------------------------------------------------------------------*\
* Select support methods
\*-------------------------------------------------------------------------*/
static int unix_meth_getfd(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    lua_pushnumber(L, (int) un->sock);
    return 1;
}

/* this is very dangerous, but can be handy for those that are brave enough */
static int unix_meth_setfd(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    un->sock = (t_socket) luaL_checknumber(L, 2); 
    return 0;
}

static int unix_meth_dirty(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    lua_pushboolean(L, !buffer_isempty(&un->buf));
    return 1;
}

/*-------------------------------------------------------------------------*\
* Waits for and returns a client object attempting connection to the 
* server object 
\*-------------------------------------------------------------------------*/
static int unix_meth_accept(lua_State *L) {
    p_unix server = (p_unix) auxiliar_checkclass(L, "unix{server}", 1);
    p_timeout tm = timeout_markstart(&server->tm);
    t_socket sock;
    int err = socket_accept(&server->sock, &sock, NULL, NULL, tm);
    /* if successful, push client socket */
    if (err == IO_DONE) {
        p_unix clnt = (p_unix) lua_newuserdata(L, sizeof(t_unix));
        auxiliar_setclass(L, "unix{client}", -1);
        /* initialize structure fields */
        socket_setnonblocking(&sock);
        clnt->sock = sock;
        io_init(&clnt->io, (p_send)socket_send, (p_recv)socket_recv, 
                (p_error) socket_ioerror, &clnt->sock);
        timeout_init(&clnt->tm, -1, -1);
        buffer_init(&clnt->buf, &clnt->io, &clnt->tm);
        return 1;
    } else {
        lua_pushnil(L); 
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
}

/*-------------------------------------------------------------------------*\
* Binds an object to an address 
\*-------------------------------------------------------------------------*/
static const char *unix_trybind(p_unix un, const char *path) {
#ifndef _WIN32
    struct sockaddr_un local;
    size_t len = strlen(path);
    int err;
    if (len >= sizeof(local.sun_path)) return "path too long";
    memset(&local, 0, sizeof(local));
    strcpy(local.sun_path, path);
    local.sun_family = AF_UNIX;
#ifdef UNIX_HAS_SUN_LEN
    local.sun_len = sizeof(local.sun_family) + sizeof(local.sun_len) 
        + len + 1;
    err = socket_bind(&un->sock, (SA *) &local, local.sun_len);

#else 
    err = socket_bind(&un->sock, (SA *) &local, 
            sizeof(local.sun_family) + len);
#endif
    if (err != IO_DONE) socket_destroy(&un->sock);
    return socket_strerror(err); 
#else
	return NULL;
#endif
}

static int unix_meth_bind(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{master}", 1);
    const char *path =  luaL_checkstring(L, 2);
    const char *err = unix_trybind(un, path);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Turns a master unix object into a client object.
\*-------------------------------------------------------------------------*/
static const char *unix_tryconnect(p_unix un, const char *path)
{
#ifndef _WIN32
    struct sockaddr_un remote;
    int err;
    size_t len = strlen(path);
    if (len >= sizeof(remote.sun_path)) return "path too long";
    memset(&remote, 0, sizeof(remote));
    strcpy(remote.sun_path, path);
    remote.sun_family = AF_UNIX;
    timeout_markstart(&un->tm);
#ifdef UNIX_HAS_SUN_LEN
    remote.sun_len = sizeof(remote.sun_family) + sizeof(remote.sun_len) 
        + len + 1;
    err = socket_connect(&un->sock, (SA *) &remote, remote.sun_len, &un->tm);
#else
    err = socket_connect(&un->sock, (SA *) &remote, 
            sizeof(remote.sun_family) + len, &un->tm);
#endif
    if (err != IO_DONE) socket_destroy(&un->sock);
    return socket_strerror(err);
#else
	return NULL;
#endif
}

static int unix_meth_connect(lua_State *L)
{
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{master}", 1);
    const char *path =  luaL_checkstring(L, 2);
    const char *err = unix_tryconnect(un, path);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    /* turn master object into a client object */
    auxiliar_setclass(L, "unix{client}", 1);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Closes socket used by object 
\*-------------------------------------------------------------------------*/
static int unix_meth_close(lua_State *L)
{
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    socket_destroy(&un->sock);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Puts the sockt in listen mode
\*-------------------------------------------------------------------------*/
static int unix_meth_listen(lua_State *L)
{
    p_unix un = (p_unix) auxiliar_checkclass(L, "unix{master}", 1);
    int backlog = (int) luaL_optnumber(L, 2, 32);
    int err = socket_listen(&un->sock, backlog);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
    /* turn master object into a server object */
    auxiliar_setclass(L, "unix{server}", 1);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Shuts the connection down partially
\*-------------------------------------------------------------------------*/
static int unix_meth_shutdown(lua_State *L)
{
    /* SHUT_RD,  SHUT_WR,  SHUT_RDWR  have  the value 0, 1, 2, so we can use method index directly */
    static const char* methods[] = { "receive", "send", "both", NULL };
    p_unix tcp = (p_unix) auxiliar_checkclass(L, "unix{client}", 1);
    int how = luaL_checkoption(L, 2, "both", methods);
    socket_shutdown(&tcp->sock, how);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Just call tm methods
\*-------------------------------------------------------------------------*/
static int unix_meth_settimeout(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "unix{any}", 1);
    return timeout_meth_settimeout(L, &un->tm);
}

/*=========================================================================*\
* Library functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Creates a master unix object 
\*-------------------------------------------------------------------------*/
static int unix_global_create(lua_State *L) {
    t_socket sock;
    int err = socket_create(&sock, AF_UNIX, SOCK_STREAM, 0);
    /* try to allocate a system socket */
    if (err == IO_DONE) { 
        /* allocate unix object */
        p_unix un = (p_unix) lua_newuserdata(L, sizeof(t_unix));
        /* set its type as master object */
        auxiliar_setclass(L, "unix{master}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        un->sock = sock;
        io_init(&un->io, (p_send) socket_send, (p_recv) socket_recv, 
                (p_error) socket_ioerror, &un->sock);
        timeout_init(&un->tm, -1, -1);
        buffer_init(&un->buf, &un->io, &un->tm);
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
}

} // end NS_SLUA
