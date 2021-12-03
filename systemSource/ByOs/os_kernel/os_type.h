#ifndef OS_TYPE_H__
#define OS_TYPE_H__

#ifndef _NULL
#define _NULL                (void *)(0x0)
#endif

#define _NULL_CHECK(x)       if(_NULL == x){return -1;}

#define MEM32(addr)          *(volatile unsigned long *)(addr)
#define MEM8(addr)           *(volatile unsigned char *)(addr)

/* Fixed size types. These are all optional. */
typedef signed char          int8_t;
typedef unsigned char        uint8_t;

typedef signed short         int16_t;
typedef unsigned short       uint16_t;

typedef signed int           int32_t;
typedef unsigned int         uint32_t;

typedef signed long long     int64_t;
typedef unsigned long long   uint64_t;


#endif /* OS_TYPE_H__ */

