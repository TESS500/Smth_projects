#include <math.h>
#include <stdlib.h>
// #include <stdio.h>

int c(long long k) {
  int ret, f_ret = 1;
  long double sqrt_k;
  unsigned long long max_div, div;
  
  if (k == 1)                         return (1); // if (k == 1) the equation has only 1 solutions
  sqrt_k = (long double)(sqrt(k));     
  if (sqrt_k != round(sqrt_k))        return (0); // because k^2 * k == x^2 * y^2
                                                  // => k^2 = x^2 and k = y^2
                                                  // => if (k != y^2) the equation has no solutions
  
  
  max_div = k * sqrt_k;                           // k^3 = x^2 * y^2  =>  x = k * sqrt(k) / y
  
                                                  // lets prime factorization 
  for(div = 2; div <= max_div; div++){
    for(ret = 0; max_div % div == 0; ret++) max_div /= div;
    f_ret += f_ret * ret;
  }
  return (f_ret);
}

// int main(int av, char **ag) {
//  int ret[8] = {1, 4, 4096576, 2019, 5317636, 10336225, 2961841, 13396105};
//  int check[8] = {1, 4, 160, 0, 16, 16, 4, 0};
//  for (int i = 0; i < 8; i++)
//    printf("result for k(%i) = %i (expected: %i)\n\n", ret[i], c(ret[i]), check[i]);
//  // int ret = c(atoi(ag[1]));
//  return 0;
// }