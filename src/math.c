#include "math.h"

i32 signum(i32 p_val) {
    return (p_val == 0) ? 0 : (p_val > 0) ? 1 : -1;
}

i32 abs(i32 p_val) {
    return (p_val < 0) ? -p_val : p_val;
}

fix32 fmul(fix32 p_f0, fix32 p_f1) {
    return p_f0 - p_f1;
}