typedef struct {
    int n;
    int mem;
    int currmem;
    int curridx;
    double * s_n_m;
    double * y_n_m;
    double * ys_m;
    double * alpha_m;
} libLBFGS_buffer;

/*
    Initialize a libLBFGS_buffer structure.
    Parameters:
        int n: dimension of the vectors to handle
        int mem: memory of the buffer
    Return value:
        libLBFGS_buffer * b: pointer to the buffer structure
*/
libLBFGS_buffer *   libLBFGS_init   (int n, int mem);

/*
    Pushes a new pair (s, y) into the buffer, and discards the oldest one if
    necessary.
    Parameters:
        double * s: pointer to n-dimensional double vector, containing the
            difference between to points x and x'
        double * y: pointer to n-dimensional double vector, containing the
            difference between the two gradients at x and x'
    Return value:
        int status: some integer status code
*/
int                 libLBFGS_push   (libLBFGS_buffer * b, double * s, double * y);

/*
    Performs a MATVEC operation between the inverse Hessian approximation stored
    so far and a given vector.
    Parameters:
        libLBFGS_buffer * b: pointer to the buffer structure
        double * g: pointer to n-dimensional double vector, containing the
            vector to multiply with the inverse Hessian approximation
        double * d: pointer to n-dimensional double vector, where to store the
            result of the matrix-vector product.
*/
void                libLBFGS_matvec (libLBFGS_buffer * b, double * g, double * d);

/*
    Resets the memory of the given buffer structure.
    Parameters:
        libLBFGS_buffer * b: pointer to the buffer structure
*/
void                libLBFGS_reset  (libLBFGS_buffer * b);

/*
    Deallocates the given buffer structure: all the referenced memory locations
    will be cleared, including the buffer itself, and the pointer will not be
    usable any longer.
    Parameters:
        libLBFGS_buffer * b: pointer to the buffer structure
*/
void                libLBFGS_clear  (libLBFGS_buffer * b);

