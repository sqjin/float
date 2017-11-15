// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#ifndef SPM_XPOSE_H_
#define SPM_XPOSE_H_


#include "slapack.h"

// uplo: triangle to copy FROM, i.e. uplo=UPLO_L means copy lower to upper
static inline void float_symmetrize(const int uplo, const int n, float *restrict x)
{
  const int blocksize = 8;
  
  if (uplo == UPLO_L)
  {
    // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
    for (int j=0; j<n; j+=blocksize)
    {
      for (int i=j+1; i<n; i+=blocksize)
      {
        for (int col=j; col<j+blocksize && col<n; ++col)
        {
          for (int row=i; row<i+blocksize && row<n; ++row)
            x[col + n*row] = x[row + n*col];
        }
      }
    }
  }
  else
  {
    for (int j=0; j<n; j+=blocksize)
    {
      for (int i=j+1; i<n; i+=blocksize)
      {
        for (int col=j; col<j+blocksize && col<n; ++col)
        {
          for (int row=i; row<i+blocksize && row<n; ++row)
          x[row + n*col] = x[col + n*row];
        }
      }
    }
  }
}


#endif
