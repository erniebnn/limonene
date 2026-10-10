#ifndef __RENDERING_H__
#define __RENDERING_H__

#include "typedefs.h"
#include "math.h"

typedef enum _RenderingMode {
    RM_SINGLEBUFFER,
    RM_DOUBLEBUFFER,
} RenderingMode;

typedef struct _Model3D {
    fix32 (*vertices)[3];
    fix32 (*edges)   [2];
} Model3D;

void initialize_rendering(RenderingMode p_mode);
void setpixel(u32 p_x, u32 p_y, u8 p_val);
u8 getpixel(u32 p_x, u32 p_y);
void clear(u8 p_val);
void draw_line(u32 p_x0, u32 p_y0, u32 p_x1, u32 p_y1, u8 p_val);
void draw_model(u32 p_vertices[][2], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val);
void swap();

#endif // #ifndef __RENDERING_H__