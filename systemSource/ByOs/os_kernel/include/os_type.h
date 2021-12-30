/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: Define structure of task.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#ifndef OS_TYPE_H__
#define OS_TYPE_H__

#ifndef OS_NULL
#define OS_NULL                (void *)(0x0)
#endif

#define OS_NULL_CHECK(x)       if(OS_NULL == x){return -1;}

#define MEM32(addr)          *(volatile unsigned long *)(addr)
#define MEM8(addr)           *(volatile unsigned char *)(addr)

/* Fixed size types. These are all optional. */
typedef signed char          by_int8_t;
typedef unsigned char        by_uint8_t;

typedef signed short         by_int16_t;
typedef unsigned short       by_uint16_t;

typedef signed int           by_int32_t;
typedef unsigned int         by_uint32_t;

typedef signed long long     by_int64_t;
typedef unsigned long long   by_uint64_t;


#endif /* OS_TYPE_H__ */

