#include "hardware.h"
#include "models.h"
#include "typedefs.h"
#include "math.h"
#include "rendering.h"

u32 vertices[][2] = {
    {  SCREEN_WIDTH/2,   SCREEN_HEIGHT/4},
    {3*SCREEN_WIDTH/4,   SCREEN_HEIGHT/2},
    {  SCREEN_WIDTH/2, 3*SCREEN_HEIGHT/4},
    {  SCREEN_WIDTH/4,   SCREEN_HEIGHT/2},
};
u32 vertices_len = sizeof(vertices) / sizeof(vertices[0]);

u32 edges[][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
};
u32 edges_len = sizeof(edges) / sizeof(edges[0]);

void main() {
    initialize_rendering(RM_SINGLEBUFFER);
    //u8 color = 255;
    //while (1) {
    //    clear(color);
    //    color = color >> 1;
    //    swap();
    //}
    //setpixel(0             ,               0, 255);
    //setpixel(SCREEN_WIDTH-1,               0, 255);
    //setpixel(SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 255);
    //setpixel(0             , SCREEN_HEIGHT-1, 255);
    //draw_line(5, 20, 20, 5, 255);
    Transform3D transform = {
        .tx = 0,
        .ty = 0,
        .tz = utoq(5),
        .rx = 0,
        .ry = 0,
        .rz = 0,
    };
    u32 x0, y0, x1, y1;
    to_screenspace(itoq(-1), itoq(-1), &x0, &y0);
    to_screenspace(itoq( 1), itoq( 1), &x1, &y1);
    draw_line(x0, y0, x1, y1, 255);
    //draw_model_3d(transform, cube_vertices, cube_vertices_len, cube_edges, cube_edges_len, 255);
    swap();
}