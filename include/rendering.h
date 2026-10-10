#ifndef __RENDERING_H__
#define __RENDERING_H__

#include "typedefs.h"
#include "math.h"
#include "q16.h"

typedef enum _RenderingMode {
    RM_SINGLEBUFFER,
    RM_DOUBLEBUFFER,
} RenderingMode;

typedef struct _Transform3D {
    q16 tx, ty, tz;
    q16 rx, ry, rz;
} Transform3D;

void initialize_rendering(RenderingMode p_mode);
void setpixel(u32 p_x, u32 p_y, u8 p_val);
u8 getpixel(u32 p_x, u32 p_y);
void clear(u8 p_val);
void draw_line(u32 p_x0, u32 p_y0, u32 p_x1, u32 p_y1, u8 p_val);
void to_screenspace(q16 p_x0, q16 p_y0, u32* r_x0, u32* r_y0);
void draw_model_2d(q16 p_vertices[][2], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val);
void draw_model_3d(Transform3D p_transform, q16 p_vertices[][3], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val);
void swap();

#endif // #ifndef __RENDERING_H__