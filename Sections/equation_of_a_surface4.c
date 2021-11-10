#include <math.h>
#include <stdlib.h>
#include <stdio.h>

  // x^2 * y^2 = k^3
  // x = +-(k * sqrt(k) / y)
  // ttt = k * sqrt(k)    =>    x = +-(ttt / y)  *y ≠ 0 

int c(long long k) {
	int ret = 0;
	long double tmp_x, tmp_k;
	unsigned long long ttt, max_div, y = 1;
  
	if (k == 1)
		return (1);
	tmp_k = (long double)(sqrt(k));
	if (tmp_k != round(tmp_k))
		return (0);
	ttt = k * tmp_k;
	max_div = sqrt(ttt);
	for (y = 1; y <= max_div; y++){
		tmp_x = (long double)ttt / (long double)y;
		if (tmp_x == round(tmp_x)){
			ret += 2;
			printf("x: %lld  y: %lld  ret: %i\n\n", (long long)tmp_x, y, ret);
		}
	}
	return (ret);
}

int main(int av, char **ag) {
	int ret[8] = {1, 4, 4096576, 2019, 5317636, 10336225, 2961841, 13396105};
	int check[8] = {1, 4, 160, 0, 16, 16, 4, 0};
	for (int i = 0; i < 8; i++)
		printf("result for k: (%i) = %i (need: %i)\n\n", ret[i], c(ret[i]), check[i]);
	// int ret = c(atoi(ag[1]));
	return 0;
}
