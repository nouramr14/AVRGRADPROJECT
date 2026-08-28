/*
 * STD_Types.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef signed short        s16;
typedef signed long         s32;
typedef signed long long    s64;
typedef float               f32;
typedef double              f64;

typedef enum
{
    false = 0,
    true = 1
} bool;

#ifndef NULL
#define NULL ((void*)0)
#endif

#define IDLE 0
#define BUSY 1
#define OK 0
#define NOK 1
#define NULL_POINTER 2
#define BUSY_STATE 3
#define TIMEOUT_STATE 4


#endif /* LIB_STD_TYPES_H_ */
