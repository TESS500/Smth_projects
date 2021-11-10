#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int c(long long k) {
	int ret = 0;
	long long square = 1, x = 1, sq = 1, y = 1;
	long double tmp, tmp_k;

	if (k == 1)
		return (1);
	tmp_k = (long double)k;
	while (square <= tmp_k){
		tmp = (long double)(tmp_k / (long double)square);
		if (tmp == roundf(tmp)){
			tmp = (long double)k / tmp;
			if (tmp == roundf(tmp))
				ret += 2;
		}
		square = pow(++x, 2);
	}
	return (ret);
}

int main(int av, char **ag) {
	int ret[8] = {1, 4, 4096576, 2019, 5317636, 10336225, 2961841, 13396105};
	int check[8] = {1, 4, 160, 0, 16, 16, 4, 0};
	for (int i = 0; i < 8; i++){
		printf("result for k: (%i) = %i (need: %i)\n\n", ret[i], c(ret[i]), check[i]);
	}
	// int ret = c(atoi(ag[1]));
	return 0;
}