#ifndef __MATH_H__
#define __MATH_H__

#include "typedefs.h"

// 32 Bit 16.16 Fixed Point
typedef u32 fix32;

i32 signum(i32 p_val);
i32 abs(i32 p_val);

fix32 fmul(fix32 p_f0, fix32 p_f1);
fix32 fdiv(fix32 p_f0, fix32 p_f1);

#endif // #ifndef __MATH_H__