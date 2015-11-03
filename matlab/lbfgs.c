#include "mex.h"
#include "../libLBFGS.h"

#define IS_REAL_SPARSE_MAT(P) (mxGetNumberOfDimensions(P) == 2 && \
    mxIsSparse(P) && mxIsDouble(P))
#define IS_REAL_DENSE_MAT(P) (mxGetNumberOfDimensions(P) == 2 && \
    !mxIsSparse(P) && mxIsDouble(P))
#define IS_REAL_DENSE_VEC(P) ((mxGetNumberOfDimensions(P) == 1 || \
    (mxGetNumberOfDimensions(P) == 2 && (mxGetN(P) == 1 || mxGetM(P) == 1))) && \
    !mxIsSparse(P) && mxIsDouble(P))
#define IS_INT32_DENSE_VEC(P) ((mxGetNumberOfDimensions(P) == 1 || \
    (mxGetNumberOfDimensions(P) == 2 && (mxGetN(P) == 1 || mxGetM(P) == 1))) && \
    !mxIsSparse(P) && mxIsInt32(P))
#define IS_REAL_SCALAR(P) (IS_REAL_DENSE_VEC(P) && mxGetNumberOfElements(P) == 1)
#define IS_INT32_SCALAR(P) (IS_INT32_DENSE_VEC(P) && mxGetNumberOfElements(P) == 1)

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  int n, mem, curridx, currmem, dir_dims[2];
  double * dir, * s, * y, * ys, H, * g, * alpha;

  if (nrhs != 6) {
    mexErrMsgTxt("LBFGS: you should provide exactly 6 arguments.");
    return;
  }
  if (nlhs > 1) {
    mexErrMsgTxt("LBFGS: too many output arguments.");
    return;
  }
  if (!IS_REAL_DENSE_MAT(prhs[0])) {
    mexErrMsgTxt("LBFGS: 1st argument must be a double, dense matrix.");
    return;
  }
  if (!IS_REAL_DENSE_MAT(prhs[1])) {
    mexErrMsgTxt("LBFGS: 2nd argument must be a double, dense matrix.");
    return;
  }
  if (!IS_REAL_DENSE_VEC(prhs[2])) {
    mexErrMsgTxt("LBFGS: 3rd argument must be a double, dense vector.");
    return;
  }
  if (!IS_REAL_DENSE_VEC(prhs[3])) {
    mexErrMsgTxt("LBFGS: 4th argument must be a double, dense vector.");
    return;
  }
  if (!IS_INT32_SCALAR(prhs[4])) {
    mexErrMsgTxt("LBFGS: 5th argument must be a 32-bit integer.");
    return;
  }
  if (!IS_INT32_SCALAR(prhs[5])) {
    mexErrMsgTxt("LBFGS: 6th argument must be a 32-bit integer.");
    return;
  }

  s = mxGetPr(prhs[0]);
  y = mxGetPr(prhs[1]);
  ys = mxGetPr(prhs[2]);
  g = mxGetPr(prhs[3]);
  curridx = (int)mxGetScalar(prhs[4])-1;
	currmem = (int)mxGetScalar(prhs[5]);

  n = mxGetDimensions(prhs[0])[0];
  mem = mxGetDimensions(prhs[0])[1];
  dir_dims[0] = n;
  dir_dims[1] = 1;

	alpha = mxCalloc(mem, sizeof(double));

  dir_dims[0] = n;
  dir_dims[1] = 1;
  plhs[0] = mxCreateNumericArray(2, dir_dims, mxDOUBLE_CLASS, mxREAL);
  dir = mxGetPr(plhs[0]);

  /* added these */
  libLBFGS_buffer b;
  b.n = n;
  b.mem = mem;
  b.currmem = currmem;
  b.curridx = curridx;
  b.s_n_m = s;
  b.y_n_m = y;
  b.ys_m = ys;
  b.alpha_m = alpha;
  libLBFGS_matvec(&b, g, dir);
  /***************/

	mxFree(alpha);
}
