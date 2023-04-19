#ifndef PB_H
#define PB_H

#include <stddef.h>
#include <limits.h>

#ifndef PB_API
# define PB_API extern
#endif

#if defined(_MSC_VER) || defined(__UNIXOS2__) || defined(__SOL64__)
typedef unsigned char      uint8_t;
typedef signed   char       int8_t;
typedef unsigned short     uint16_t;
typedef signed   short      int16_t;
typedef unsigned int       uint32_t;
typedef signed   int        int32_t;
typedef unsigned long long uint64_t;
typedef signed   long long  int64_t;

#ifndef INT64_MIN
#define INT64_MIN LLONG_MIN
#endif
#ifndef INT64_MAX
#define INT64_MAX LLONG_MAX
#endif

#elif defined(__SCO__) || defined(__USLC__) || defined(__MINGW32__)
# include <stdint.h>
#else
# include <inttypes.h>
# if (defined(__sun__) || defined(__digital__))
#   if defined(__STDC__) && (defined(__arch64__) || defined(_LP64))
typedef unsigned long int  uint64_t;
typedef signed   long int   int64_t;
#   else
typedef unsigned long long uint64_t;
typedef signed   long long  int64_t;
#   endif /* LP64 */
# endif /* __sun__ || __digital__ */
#endif

#define PB_MAX_SIZET          ((size_t)~0 - 100)
#define PB_MIN_STRTABLE_SIZE  16
#define PB_MIN_HASHTABLE_SIZE 8
#define PB_HASHLIMIT          5

namespace NS_SLUA {

    /* types */

#define PB_WIRETYPES(X) /* X(name, index) */\
    X(VARINT, "varint", 0) X(64BIT,  "64bit", 1) X(BYTES, "bytes", 2)  \
    X(GSTART, "gstart", 3) X(GEND,   "gend",  4) X(32BIT, "32bit", 5)  \

#define PB_TYPES(X)           /* X(name, type, index) */\
    X(double,   double,   1)  X(float,    float,    2)  \
    X(int64,    int64_t,  3)  X(uint64,   uint64_t, 4)  \
    X(int32,    int32_t,  5)  X(fixed64,  uint64_t, 6)  \
    X(fixed32,  uint32_t, 7)  X(bool,     int,      8)  \
    X(string,   pb_Slice, 9)  X(group,    pb_Slice, 10) \
    X(message,  pb_Slice, 11) X(bytes,    pb_Slice, 12) \
    X(uint32,   uint32_t, 13) X(enum,     int32_t,  14) \
    X(sfixed32, int32_t,  15) X(sfixed64, int64_t,  16) \
    X(sint32,   int32_t,  17) X(sint64,   int64_t,  18) \

    typedef enum pb_WireType {
#define X(name, s, index) PB_T##name,
        PB_WIRETYPES(X)
#undef  X
        PB_TWIRECOUNT
    } pb_WireType;

    typedef enum pb_FieldType {
#define X(name, type, index) PB_T##name = index,
        PB_TYPES(X)
#undef  X
        PB_TYPECOUNT
    } pb_FieldType;


    /* conversions */

    PB_API uint64_t pb_expandsig(uint32_t v);
    PB_API uint32_t pb_encode_sint32(int32_t v);
    PB_API  int32_t pb_decode_sint32(uint32_t v);
    PB_API uint64_t pb_encode_sint64(int64_t v);
    PB_API  int64_t pb_decode_sint64(uint64_t v);
    PB_API uint32_t pb_encode_float(float    v);
    PB_API float    pb_decode_float(uint32_t v);
    PB_API uint64_t pb_encode_double(double   v);
    PB_API double   pb_decode_double(uint64_t v);


    /* decode */

    typedef struct pb_Slice { const char *p, *end; } pb_Slice;
#define pb_gettype(v)       ((v) &  7)
#define pb_gettag(v)        ((v) >> 3)
#define pb_pair(tag, type)  ((tag) << 3 | ((type) & 7))

    PB_API pb_Slice pb_slice(const char *p);
    PB_API pb_Slice pb_lslice(const char *p, size_t len);
    PB_API size_t   pb_len(pb_Slice s);

    PB_API size_t pb_readvarint32(pb_Slice *s, uint32_t *pv);
    PB_API size_t pb_readvarint64(pb_Slice *s, uint64_t *pv);
    PB_API size_t pb_readfixed32(pb_Slice *s, uint32_t *pv);
    PB_API size_t pb_readfixed64(pb_Slice *s, uint64_t *pv);

    PB_API size_t pb_readslice(pb_Slice *s, size_t len, pb_Slice *pv);
    PB_API size_t pb_readbytes(pb_Slice *s, pb_Slice *pv);
    PB_API size_t pb_readgroup(pb_Slice *s, uint32_t tag, pb_Slice *pv);

    PB_API size_t pb_skipvarint(pb_Slice *s);
    PB_API size_t pb_skipbytes(pb_Slice *s);
    PB_API size_t pb_skipslice(pb_Slice *s, size_t len);
    PB_API size_t pb_skipvalue(pb_Slice *s, uint32_t tag);

    PB_API const char *pb_wtypename(int wiretype, const char *def);
    PB_API const char *pb_typename(int type, const char *def);

    PB_API int pb_typebyname(const char *name, int def);
    PB_API int pb_wtypebyname(const char *name, int def);
    PB_API int pb_wtypebytype(int type);


    /* encode */

#define PB_BUFFERSIZE   (1024)

    typedef struct pb_Buffer {
        size_t size;
        size_t capacity;
        char  *buff;
        char   init_buff[PB_BUFFERSIZE];
    } pb_Buffer;

#define pb_buffer(b)      ((b)->buff)
#define pb_bufflen(b)     ((b)->size)
#define pb_addsize(b, sz) ((void)((b)->size += (sz)))
#define pb_addchar(b, ch) \
    ((void)((b)->size < (b)->capacity || pb_prepbuffsize((b), 1)), \
     ((b)->buff[(b)->size++] = (ch)))

    PB_API void   pb_initbuffer(pb_Buffer *b);
    PB_API void   pb_resetbuffer(pb_Buffer *b);
    PB_API size_t pb_resizebuffer(pb_Buffer *b, size_t len);
    PB_API void  *pb_prepbuffsize(pb_Buffer *b, size_t len);

    PB_API pb_Slice pb_result(pb_Buffer *b);

    PB_API size_t pb_addvarint32(pb_Buffer *b, uint32_t v);
    PB_API size_t pb_addvarint64(pb_Buffer *b, uint64_t v);
    PB_API size_t pb_addfixed32(pb_Buffer *b, uint32_t v);
    PB_API size_t pb_addfixed64(pb_Buffer *b, uint64_t v);

    PB_API size_t pb_addslice(pb_Buffer *b, pb_Slice s);
    PB_API size_t pb_addbytes(pb_Buffer *b, pb_Slice s);
    PB_API size_t pb_addlength(pb_Buffer *b, size_t len);


    /* type info database state and name table */

    typedef struct pb_State pb_State;
    typedef struct pb_Name  pb_Name;

    PB_API void pb_init(pb_State *S);
    PB_API void pb_free(pb_State *S);

    PB_API pb_Name *pb_newname(pb_State *S, pb_Slice    s);
    PB_API void     pb_delname(pb_State *S, pb_Name    *name);
    PB_API pb_Name *pb_name(pb_State *S, const char *name);

    PB_API pb_Name *pb_usename(pb_Name *name);


    /* type info */

    typedef struct pb_Type  pb_Type;
    typedef struct pb_Field pb_Field;

#define PB_OK     0
#define PB_ERROR  1
#define PB_ENOMEM 2

    PB_API int pb_load(pb_State *S, pb_Slice *s);

    PB_API pb_Type  *pb_newtype(pb_State *S, pb_Name *tname);
    PB_API void      pb_deltype(pb_State *S, pb_Type *t);
    PB_API pb_Field *pb_newfield(pb_State *S, pb_Type *t, pb_Name *fname, int32_t number);
    PB_API void      pb_delfield(pb_State *S, pb_Type *t, pb_Field *f);

    PB_API pb_Type  *pb_type(pb_State *S, pb_Name *tname);
    PB_API pb_Field *pb_fname(pb_Type *t, pb_Name *tname);
    PB_API pb_Field *pb_field(pb_Type *t, int32_t number);

    PB_API pb_Name *pb_oneofname(pb_Type *t, int oneof_index);

    PB_API int pb_nexttype(pb_State *S, pb_Type **ptype);
    PB_API int pb_nextfield(pb_Type *t, pb_Field **pfield);


    /* util: memory pool */

#define PB_POOLSIZE 4096

    typedef struct pb_Pool {
        void  *pages;
        void  *freed;
        size_t obj_size;
    } pb_Pool;

    PB_API void pb_initpool(pb_Pool *pool, size_t obj_size);
    PB_API void pb_freepool(pb_Pool *pool);

    PB_API void *pb_poolalloc(pb_Pool *pool);
    PB_API void  pb_poolfree(pb_Pool *pool, void *obj);

    /* util: hash table */

    typedef struct pb_Table pb_Table;
    typedef struct pb_Entry pb_Entry;
    typedef ptrdiff_t pb_Key;

    PB_API void pb_inittable(pb_Table *t, size_t entrysize);
    PB_API void pb_freetable(pb_Table *t);

    PB_API size_t pb_resizetable(pb_Table *t, size_t size);

    PB_API pb_Entry *pb_gettable(pb_Table *t, pb_Key key);
    PB_API pb_Entry *pb_settable(pb_Table *t, pb_Key key);
    PB_API int pb_nextentry(pb_Table *t, pb_Entry **pentry);

    struct pb_Table {
        size_t    size;
        size_t    lastfree;
        unsigned  entry_size : sizeof(unsigned)*CHAR_BIT - 1;
        unsigned  has_zero : 1;
        pb_Entry *hash;
    };

    struct pb_Entry {
        ptrdiff_t next;
        pb_Key    key;
    };


    /* fields */

    typedef struct pb_NameEntry {
        struct pb_NameEntry *next;
        unsigned       hash : 32;
        unsigned       length : 16;
        unsigned       refcount : 16;
    } pb_NameEntry;

    typedef struct pb_NameTable {
        size_t         size;
        size_t         count;
        pb_NameEntry **hash;
    } pb_NameTable;

    struct pb_State {
        pb_Table     types;
        pb_NameTable nametable;
        pb_Pool      typepool;
        pb_Pool      fieldpool;
    };

    struct pb_Field {
        pb_Name *name;
        pb_Type *type;
        pb_Name *default_value;
        int32_t  number;
        unsigned oneof_idx : 24;
        unsigned type_id : 5; /* PB_T* enum */
        unsigned repeated : 1;
        unsigned packed : 1;
        unsigned scalar : 1;
    };

    struct pb_Type {
        pb_Name    *name;
        const char *basename;
        pb_Table    field_tags;
        pb_Table    field_names;
        pb_Table    oneof_index;
        unsigned    field_count : 28;
        unsigned    is_enum : 1;
        unsigned    is_map : 1;
        unsigned    is_proto3 : 1;
        unsigned    is_dead : 1;
    };

}

#endif /* PB_H */
