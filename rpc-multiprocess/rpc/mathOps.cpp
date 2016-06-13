#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 10

int pow_rpc(double a, double *v, int v_sz)
{
  for(int i = 0; i < v_sz; i++)
  {
    v[i] = pow(v[i], a);
  }
  
  return 0;
}

int exp_rpc(double *v, int v_sz)
{
  for(int i = 0; i < v_sz; i++)
  {
    v[i] = exp(v[i]);
  }

  return 0;
}

int log_rpc(double *v, int v_sz)
{
  for(int i = 0; i < v_sz; i++)
  {
    v[i] = log(v[i]);
  }

  return 0;
}

int main(int argc, const char* argv[])
{
  double *v = (double *) malloc(n * sizeof(double));
  for(int i = 0; i < n; i++)
  {
    v[i] = i;
  }

  pow_rpc(2.0, v, n);

  for(int i = 0; i < n; i++)
  {
    printf("%lf\n", v[i]);
  }
  
  exp_rpc(v, n);

  for(int i = 0; i < n; i++)
  {
    printf("%lf\n", v[i]);
  }
  
  log_rpc(v, n);

  for(int i = 0; i < n; i++)
  {
    printf("%lf\n", v[i]);
  }
  
  printf("Hello, World!\n");
}
