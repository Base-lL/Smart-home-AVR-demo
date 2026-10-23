/*
 * std_types.h
 *
 *  Created on: Aug 5, 2026
 *      Author: emad.yousry
 */

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

#define FCPU 8000000UL

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long  int s32;

typedef float  f32;
typedef double f64;

#ifndef NULL
    #define NULL 0
#endif

#endif /* LIB_STD_TYPES_H_ */
