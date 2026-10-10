#include "models.h"

q16 cube_vertices[][3] = {
    {-0x8000, -0x8000, -0x8000},
    {-0x8000, -0x8000,  0x8000},
    {-0x8000,  0x8000, -0x8000},
    {-0x8000,  0x8000,  0x8000},
    { 0x8000, -0x8000, -0x8000},
    { 0x8000, -0x8000,  0x8000},
    { 0x8000,  0x8000, -0x8000},
    { 0x8000,  0x8000,  0x8000},
};
u32 cube_vertices_len = sizeof(cube_vertices) / sizeof(cube_vertices[0]);

u32 cube_edges[][2] = {
    {0, 4},
    {0, 2},
    {0, 1},
    {5, 1},
    {5, 7},
    {5, 4},
    {6, 2},
    {6, 4},
    {6, 7},
    {3, 7},
    {3, 1},
    {3, 2},
};
u32 cube_edges_len = sizeof(cube_edges) / sizeof(cube_edges[0]);