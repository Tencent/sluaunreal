#ifndef UDP_H
#define UDP_H
/*=========================================================================*\
* UDP object
* LuaSocket toolkit
*
* The udp.h module provides LuaSocket with support for UDP protocol
* (AF_INET, SOCK_DGRAM).
*
* Two classes are defined: connected and unconnected. UDP objects are
* originally unconnected. They can be "connected" to a given address 
* with a call to the setpeername function. The same function can be used to
* break the connection.
\*=========================================================================*/
#include "lua.h"

#include "timeout.h"
#include "socket.h"

/* can't be larger than wsocket.c MAXCHUNK!!! */
#define UDP_DATAGRAMSIZE 8192

namespace NS_SLUA {    

typedef struct t_udp_ {
    t_socket sock;
    t_timeout tm;
    int family;
} t_udp;
typedef t_udp *p_udp;

int udp_open(lua_State *L);

} // end NS_SLUA

#endif /* UDP_H */
