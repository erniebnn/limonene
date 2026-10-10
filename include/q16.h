#ifndef __Q16_H__
#define __Q16_H__

#include "typedefs.h"

typedef i32 q16;

extern const q16 Q16_PI;
extern const q16 Q16_ONE;

q16 itoq(i32 p_i0);
i32 qtoi(q16 p_q0);
q16 utoq(u32 p_u0);
u32 qtou(q16 p_q0);

q16 qabs(q16 p_q0);

q16 qfloor(q16 p_q0);
q16 qceil(q16 p_q0);
q16 qround(q16 p_q0);

q16 qmul(q16 p_q0, q16 p_q1);
q16 qdiv(q16 p_q0, q16 p_q1);
q16 qrem(q16 p_q0, q16 p_q1);

q16 qsin(q16 p_q0);
q16 qcos(q16 p_q0);
q16 qtan(q16 p_q0);

void qmatmul4(q16 p_qmd[4][4], q16 p_qm0[4][4], q16 p_qm1[4][4]);
void qmatvecmul4(q16 p_qvd[4], q16 p_qm0[4][4], q16 p_qv0[4]);

#endif // #ifndef __Q16_H__