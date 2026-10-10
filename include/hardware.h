#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "typedefs.h"

#define SCREEN_WIDTH  (72)
#define SCREEN_HEIGHT (54)

extern void set_fptr(volatile u8* p_ptr);

extern u32 dbg0;
extern u32 dbg1;
extern u32 dbg2;
extern u32 dbg3;

#endif // #ifndef __HARDWARE_H__