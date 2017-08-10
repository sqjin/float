#ifndef SPM_NORM_H_
#define SPM_NORM_H_


// Don't want to write a slange wrapper; don't make the user compile fortran
// if at all possible

void slassq_(const int *const restrict n, const float *const restrict x,
  const int *const restrict incx, float *const restrict scale,
  float *const restrict sumsq);


// norm = maximum absolute column sum
static inline float norm_macs(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  
  for (int j=0; j<n; j++)
  {
    float tmp = 0.0f;
    for (int i=0; i<m; i++)
      tmp += fabsf(x[i + m*j]);
    
    if (tmp > norm)
      norm = tmp;
  }
  
  return norm;
}

// maximum absolute row sum
static inline float norm_mars(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  float *tmp = malloc(m*sizeof(*tmp));
  if (tmp == NULL)
    error("OOM");
  
  memset(tmp, 0.0f, m*sizeof(*tmp));
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      tmp[i] += fabsf(x[i + m*j]);
  }
  
  for (int i=0; i<m; i++)
  {
    if (tmp[i] > norm)
      norm = tmp[i];
  }
  
  free(tmp);
  return norm;
}

// euclidean norm
static inline float norm_euc(const int m, const int n, const float *const restrict x)
{
  float scale = 0.0f;
  float sumsq = 1.0f;
  for (int j=0; j<n; j++)
    slassq_(&m, x + m*j, &(int){1}, &scale, &sumsq);
  
  return scale * sqrtf(sumsq);
}

// max modulus
static inline float norm_maxmod(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (x[i + m*j] > norm)
        norm = x[i + m*j];
    }
  }
  
  return norm;
}


#endif