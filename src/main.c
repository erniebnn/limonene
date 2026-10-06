#include "hardware.h"
#include "typedefs.h"
#include "math.h"

typedef enum _RenderingMode {
    RM_SINGLEBUFFER,
    RM_DOUBLEBUFFER,
} RenderingMode;

extern volatile u8* fptr;
volatile u8* bptr;

RenderingMode rendering_mode = RM_SINGLEBUFFER;

volatile u8 framebuffer[2][SCREEN_WIDTH * SCREEN_HEIGHT] = {};

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

void setpixel(u32 p_x, u32 p_y, u8 p_val) {
    *(bptr + p_y * SCREEN_WIDTH + p_x) = p_val;
}

u8 getpixel(u32 p_x, u32 p_y) {
    return *(bptr + p_y * SCREEN_WIDTH + p_x);
}

void clear(u8 p_val) {
    for (u32 y = 0; y < SCREEN_HEIGHT; y++) {
        for (u32 x = 0; x < SCREEN_WIDTH; x++) {
            setpixel(x, y, p_val);
        }
    }
}

void draw_line(u32 p_x0, u32 p_y0, u32 p_x1, u32 p_y1, u8 p_val) {
    i32 dx = p_x1 - p_x0;
    i32 dy = p_y1 - p_y0;
    i32 ddx = signum(dx);
    i32 ddy = signum(dy);
    dx = abs(dx);
    dy = abs(dy);
    i32 pdx, pdy, dsd, dfd;
    if (dx > dy) {
        pdx = ddx; pdy = 0  ;
        dsd = dy ; dfd = dx ;
    }
    else {
        pdx = 0  ; pdy = ddy;
        dsd = dx ; dfd = dy ;
    }
    i32 x = p_x0, y = p_y0;
    i32 err = dfd / 2;
    setpixel(x, y, p_val);
    for (u32 t = 0; t < dfd; t++) {
        err -= dsd;
        if (err < 0) {
            err += dfd;
            x   += ddx;
            y   += ddy;
        }
        else {
            x   += pdx;
            y   += pdy;
        }
        setpixel(x, y, p_val);
    }
}

void draw_model(u32 p_vertices[][2], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val) {
    for (u32 i = 0; i < p_edges_len; i++) {
        u32 v0 = p_edges   [ i][0], v1 = p_edges   [ i][1];
        u32 x0 = p_vertices[v0][0], y0 = p_vertices[v0][1];
        u32 x1 = p_vertices[v1][0], y1 = p_vertices[v1][1];
        draw_line(x0, y0, x1, y1, p_val);
    }
}

void swap() {
    volatile u8* tmp = fptr;
    fptr = bptr;
    bptr = fptr;
}

void main() {
    fptr = framebuffer[0];
    bptr = rendering_mode == RM_DOUBLEBUFFER ? framebuffer[1] : framebuffer[0];

    draw_model(vertices, vertices_len, edges, edges_len, 255);
}