#include "math.h"

i32 signum(i32 p_val) {
    return (p_val == 0) ? 0 : (p_val > 0) ? 1 : -1;
}

i32 abs(i32 p_val) {
    return (p_val < 0) ? -p_val : p_val;
}