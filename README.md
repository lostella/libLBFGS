# libLBFGS

[![Build Status](https://travis-ci.org/lostella/libLBFGS.svg)](https://travis-ci.org/lostella/libLBFGS)

`libLBFGS` is a small piece of C code implementing all that is needed to compute
limited-memory BFGS (also known as L-BFGS) directions when minimizing smooth functions.

It implements the necessary functions to allocate a FIFO buffer, for some pairs of vectors to be stored;
to cyclically push and pull pairs `(s, y)` of vectors into the buffer; to compute matrix vector
products with the resulting approximate inverse Hessian matrix.

For more information about the L-BFGS method, see:

* J. Nocedal, "Updating quasi-Newton matrices with limited storage," in *Mathematics of Computation*, vol. 35, issue 151, pp. 773-782 (1980). [Available here](http://www.ams.org/journals/mcom/1980-35-151/S0025-5718-1980-0572855-7/)
* D. Liu, J. Nocedal, "On the limited memory BFGS method for large scale optimization," in *Mathematical Programming*, vol. 45, pp. 503-528 (1989). [Available here](http://link.springer.com/article/10.1007%2FBF01589116)

## How to use it (Linux/Unix/MacOS X)

To compile the library simply type `make`. This will produce `libLBFGS.o`, that you
will need to statically link to your project. The following routines are exported in `libLBFGS.h`:

* `libLBFGS_buffer * libLBFGS_init (int n, int mem);`  
    Initialize a libLBFGS_buffer structure.  
    **Parameters**  
     `int n`: dimension of the vectors to handle  
     `int mem`: memory of the buffer  
    **Return value**  
     `libLBFGS_buffer * b`: pointer to the buffer structure  

* `int libLBFGS_push (libLBFGS_buffer * b, double * s, double * y);`  
    Pushes a new pair (s, y) into the buffer, and discards the oldest one if necessary.  
    **Parameters**  
     `libLBFGS_buffer * b`: pointer to the buffer structure  
     `double * s`: pointer to n-dimensional double vector, containing the difference between to points x and x'  
     `double * y`: pointer to n-dimensional double vector, containing the difference between the two gradients at x and x'  
    **Return value**  
     `int status`: some integer status code  

* `void libLBFGS_matvec (libLBFGS_buffer * b, double * g, double * d);`  
    Performs a MATVEC operation between the inverse Hessian approximation stored so far and a given vector.  
    **Parameters**  
     `libLBFGS_buffer * b`: pointer to the buffer structure  
     `double * g`: pointer to n-dimensional double vector, containing the vector to multiply with the inverse Hessian approximation  
     `double * d`: pointer to n-dimensional double vector, where to store the result of the matrix-vector product.  

* `void libLBFGS_reset (libLBFGS_buffer * b);`  
    Resets the memory of the given buffer structure.  
    **Parameters**  
     `libLBFGS_buffer * b`: pointer to the buffer structure  

* `void libLBFGS_clear (libLBFGS_buffer * b);`  
    Deallocates the given buffer structure: all the referenced memory locations will be cleared, including the buffer itself, and the pointer will no longer be usable.  
    **Parameters**  
     `libLBFGS_buffer * b`: pointer to the buffer structure
