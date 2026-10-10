#include "rendering.h"
#include "math.h"
#include "hardware.h"
#include "q16.h"

static RenderingMode rendering_mode;

static volatile u8 framebuffer[2][SCREEN_WIDTH * SCREEN_HEIGHT] = {};

static volatile u8* fptr;
static volatile u8* bptr;

static q16 tscrnc0;
static q16 tscrnc1;
static q16 asprat;
static q16 prspc0;
static q16 prspc1;

static const q16 fov = 0x10C15;
static const q16 far = 0x1 << 26;
static const q16 near = 0x1 << 16;
static q16 fcnst0;
static q16 fcnst1;

void initialize_rendering(RenderingMode p_mode) {
    rendering_mode = p_mode;
    fptr = framebuffer[0];
    bptr = rendering_mode == RM_DOUBLEBUFFER ? framebuffer[1] : framebuffer[0];
    set_fptr(fptr);
    dbg0 = (u32) fptr;
    dbg1 = (u32) bptr;
    tscrnc0 = qdiv(1 << 16, (SCREEN_WIDTH  / 2) << 16);
    tscrnc1 = qdiv(1 << 16, (SCREEN_HEIGHT / 2) << 16);
    asprat = qdiv(utoq(SCREEN_WIDTH), utoq(SCREEN_HEIGHT));
    prspc0 = qdiv(Q16_ONE, qmul(asprat, qtan(qdiv(fov, 2))));
    prspc0 = qdiv(Q16_ONE,              qtan(qdiv(fov, 2)) );
    fcnst0 = qdiv(far, far - near);
    fcnst1 = qdiv(qmul(far, near), far - near);
}

void setpixel(u32 p_x, u32 p_y, u8 p_val) {
    if (SCREEN_WIDTH <= p_x || SCREEN_HEIGHT <= p_y) { return; } // bad performance?
    u32 px_idx = p_y * SCREEN_WIDTH + p_x;
    px_idx = px_idx ^ 0b11;
    *(bptr + px_idx) = p_val;
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
    i32 dx = (i32) p_x1 - (i32) p_x0;
    i32 dy = (i32) p_y1 - (i32) p_y0;
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
        if (err <= 0) {
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

void to_screenspace(q16 p_x0, q16 p_y0, u32* r_x0, u32* r_y0) {
    *r_x0 = qtou(qround(qmul(p_x0 + Q16_ONE, tscrnc0)));
    *r_y0 = qtou(qround(-qmul(p_y0 + Q16_ONE, tscrnc1)));
}

void draw_model_2d(q16 p_vertices[][2], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val) {
    for (u32 i = 0; i < p_edges_len; i++) {
        u32 v0 = p_edges   [ i][0], v1 = p_edges   [ i][1];
        q16 x0 = p_vertices[v0][0], y0 = p_vertices[v0][1];
        q16 x1 = p_vertices[v1][0], y1 = p_vertices[v1][1];
        u32 ux0, ux1, uy0, uy1;
        to_screenspace(x0, y0, &ux0, &uy0); // bisschen dumm ?
        to_screenspace(x1, y1, &ux1, &uy1);
        draw_line(ux0, uy0, ux1, uy1, p_val);
    }
}

void draw_model_3d(Transform3D p_transform, q16 p_vertices[][3], u32 p_vertices_len, u32 p_edges[][2], u32 p_edges_len, u8 p_val) {
    q16 sx = qsin(p_transform.rx), cx = qcos(p_transform.rx);
    q16 sy = qsin(p_transform.ry), cy = qcos(p_transform.ry);
    q16 sz = qsin(p_transform.rz), cz = qcos(p_transform.rz);
    q16 tx = p_transform.tx, ty = p_transform.ty, tz = p_transform.tz;
    q16 mat0[4][4];
    q16 mat1[4][4];
    q16 mat2[4][4];
    // Rotation Around X
    mat0[0][0] = Q16_ONE; mat0[1][0] =   0; mat0[2][0] =   0; mat0[3][0] =   0;
    mat0[0][1] =   0; mat0[1][1] =  cx; mat0[2][1] = -sx; mat0[3][1] =   0;
    mat0[0][2] =   0; mat0[1][2] =  sx; mat0[2][2] =  cx; mat0[3][2] =   0;
    mat0[0][3] =   0; mat0[1][3] =   0; mat0[2][3] =   0; mat0[3][3] =   Q16_ONE;
    // Rotation Around Y
    mat1[0][0] =  cy; mat1[1][0] =   0; mat1[2][0] =  sy; mat1[3][0] =   0;
    mat1[0][1] =   0; mat1[1][1] =   Q16_ONE; mat1[2][1] =   0; mat1[3][1] =   0;
    mat1[0][2] = -sy; mat1[1][2] =   0; mat1[2][2] =  cy; mat1[3][2] =   0;
    mat1[0][3] =   0; mat1[1][3] =   0; mat1[2][3] =   0; mat1[3][3] =   Q16_ONE;
    qmatmul4(mat2, mat1, mat0);
    // Rotation Around Z
    mat1[0][0] =  cz; mat1[1][0] = -sz; mat1[2][0] =   0; mat1[3][0] =   0;
    mat1[0][1] =  sz; mat1[1][1] =  cz; mat1[2][1] =   0; mat1[3][1] =   0;
    mat1[0][2] =   0; mat1[1][2] =   0; mat1[2][2] =   Q16_ONE; mat1[3][2] =   0;
    mat1[0][3] =   0; mat1[1][3] =   0; mat1[2][3] =   0; mat1[3][3] =   Q16_ONE;
    qmatmul4(mat0, mat1, mat2);
    // Translation
    mat1[0][0] =   Q16_ONE; mat1[1][0] =   0; mat1[2][0] =   0; mat1[3][0] =  tx;
    mat1[0][1] =   0; mat1[1][1] =   Q16_ONE; mat1[2][1] =   0; mat1[3][1] =  ty;
    mat1[0][2] =   0; mat1[1][2] =   0; mat1[2][2] =   Q16_ONE; mat1[3][2] =  tz;
    mat1[0][3] =   0; mat1[1][3] =   0; mat1[2][3] =   0; mat1[3][3] =   Q16_ONE;
    qmatmul4(mat2, mat1, mat0);
    // Perspective
    mat1[0][0] = prspc0; mat1[1][0] =      0; mat1[2][0] =       0; mat1[3][0] =       0;
    mat1[0][1] =      0; mat1[1][1] = prspc1; mat1[2][1] =       0; mat1[3][1] =       0;
    mat1[0][2] =      0; mat1[1][2] =      0; mat1[2][2] =  fcnst0; mat1[3][2] =  fcnst0;
    mat1[0][3] =      0; mat1[1][3] =      0; mat1[2][3] = Q16_ONE; mat1[3][3] = Q16_ONE;
    qmatmul4(mat0, mat1, mat2);
    q16 vertices[p_vertices_len][4];
    u32 vertices2d[p_vertices_len][2];
    for (u32 i = 0; i < p_vertices_len; i++) {
        q16 vertex[4] = {
            p_vertices[i][0],
            p_vertices[i][1],
            p_vertices[i][2],
            Q16_ONE,
        };
        qmatvecmul4(vertices[i], mat0, vertex);
        vertices[i][0] = qdiv(vertices[i][0], vertices[i][3]);
        vertices[i][1] = qdiv(vertices[i][1], vertices[i][3]);
        to_screenspace(vertices[i][0], vertices[i][1], &vertices2d[i][0], &vertices2d[i][1]);
    }
    for (u32 i = 0; i < p_edges_len; i++) {
        u32 v0 = p_edges   [ i][0], v1 = p_edges   [ i][1];
        q16 x0 = vertices2d[v0][0], y0 = vertices2d[v0][1];
        q16 x1 = vertices2d[v1][0], y1 = vertices2d[v1][1];
        draw_line(x0, y0, x1, y1, p_val);
    }
}

void swap() {
    volatile u8* tmp = fptr;
    fptr = bptr;
    bptr = tmp;
    dbg0 = (u32) fptr;
    dbg1 = (u32) bptr;
    set_fptr(fptr);
}