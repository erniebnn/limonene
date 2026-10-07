#include "hardware.h"
#include "typedefs.h"
#include "math.h"
#include "rendering.h"

u32 vertices[][2] = {
    {200,  50},
    {360, 120},
    {240, 290},
    {100, 200},
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
    draw_model(vertices, vertices_len, edges, edges_len, 255);
}