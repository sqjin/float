#include "spm.h"
#include "matmult.h"


SEXP R_matmult_spm(SEXP x, SEXP y)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(y);
  
  if (NCOLS(x) != NROWS(y))
    error("non-conformable arguments");
  
  PROTECT(ret = newmat(m, n));
  
  matmult(false, false, 1.0f, NROWS(x), NCOLS(x), DATA(x), NROWS(y), NCOLS(y), DATA(y), DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
