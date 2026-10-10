#include "hardware.h"
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
    draw_model(vertices, vertices_len, edges, edges_len, 255);
    swap();
}