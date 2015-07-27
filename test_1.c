#include <stdio.h>
#include "libLBFGS.h"

int main(void) {
    // take a pair (s, y)
    double s[10] = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f};
    double y[10] = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f};
    // initialize the buffer
    libLBFGS_buffer * b = libLBFGS_init(10, 5);
    // do a series of pushes
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    libLBFGS_push(b, s, y);
    // clear the buffer
    libLBFGS_clear(b);
    return 0;
}

