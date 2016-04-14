/*
    Test of the matvec operation
    - initialize 5 points and compute the gradient of
        f(x) 0.5*x'Qx
      with Q = diag(1e0,1e0,1e-1,1e-1,...,1e-4,1e-4)
    - compute the gradient g at point x = (1e0,...,1e0)
    - compute pairs of successive differences and push them in the buffer
    - apply the matvec operation to g
    - clear the buffer
    The test is performed for buffers of increasing dimension mem = 1,3,6,10
*/

#include <stdio.h>
#include "../libLBFGS.h"

int main(void) {
    double xs[5][10] = { {1.0f,0.01f,0.02f,0.03f,0.04f,0.05f,0.06f,0.07f,0.08f,0.09f},
                        {0.09f,1.0f,0.01f,0.02f,0.03f,0.04f,0.05f,0.06f,0.07f,0.08f},
                        {0.08f,0.09f,1.0f,0.01f,0.02f,0.03f,0.04f,0.05f,0.06f,0.07f},
                        {0.07f,0.08f,0.09f,1.0f,0.01f,0.02f,0.03f,0.04f,0.05f,0.06f},
                        {0.06f,0.07f,0.08f,0.09f,1.0f,0.01f,0.02f,0.03f,0.04f,0.05f} };
    double diagQ[10] = {1e0,1e0,1e-1,1e-1,1e-2,1e-2,1e-3,1e-3,1e-4,1e-4};
    double x[10] = {1e0,1e0,1e0,1e0,1e0,1e0,1e0,1e0,1e0,1e0};
    double gs[5][10];
    double s[10], y[10], g[10], d[10];
    int i, j;
    libLBFGS_buffer * b;
    // compute gradients
    for (i=0; i<10; i++) gs[0][i] = diagQ[i]*xs[0][i];
    for (j=1; j<5; j++) {
        for (i=0; i<10; i++) {
            gs[j][i] = diagQ[i]*xs[j][i];
        }
    }
    // compute the gradient at x
    for (i=0; i<10; i++) g[i] = diagQ[i]*x[i];
    // initialize the buffer
    b = libLBFGS_init(10, 1);
    // push pairs (s, y)
    for (j=1; j<5; j++) {
        for (i=0; i<10; i++) {
            s[i] = xs[j][i]-xs[j-1][i];
            y[i] = gs[j][i]-gs[j-1][i];
        }
        libLBFGS_push(b, s, y);
    }
    libLBFGS_matvec(b, 1.0, g, d);
    libLBFGS_clear(b);
    // initialize the buffer
    b = libLBFGS_init(10, 3);
    // push pairs (s, y)
    for (j=1; j<5; j++) {
        for (i=0; i<10; i++) {
            gs[j][i] = diagQ[i]*xs[j][i];
            s[i] = xs[j][i]-xs[j-1][i];
            y[i] = gs[j][i]-gs[j-1][i];
        }
        libLBFGS_push(b, s, y);
    }
    libLBFGS_matvec(b, 1.0, g, d);
    libLBFGS_clear(b);
    // initialize the buffer
    b = libLBFGS_init(10, 6);
    // push pairs (s, y)
    for (j=1; j<5; j++) {
        for (i=0; i<10; i++) {
            gs[j][i] = diagQ[i]*xs[j][i];
            s[i] = xs[j][i]-xs[j-1][i];
            y[i] = gs[j][i]-gs[j-1][i];
        }
        libLBFGS_push(b, s, y);
    }
    libLBFGS_matvec(b, 1.0, g, d);
    libLBFGS_clear(b);
    // initialize the buffer
    b = libLBFGS_init(10, 10);
    // push pairs (s, y)
    for (j=1; j<5; j++) {
        for (i=0; i<10; i++) {
            gs[j][i] = diagQ[i]*xs[j][i];
            s[i] = xs[j][i]-xs[j-1][i];
            y[i] = gs[j][i]-gs[j-1][i];
        }
        libLBFGS_push(b, s, y);
    }
    libLBFGS_matvec(b, 1.0, g, d);
    libLBFGS_clear(b);
    return 0;
}

