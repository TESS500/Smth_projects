#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// long long x = 1;

// long long next_square(){
// 	return (pow(++x, 2));
// }

int c(long long k) {
	int ret = 0;
	unsigned long long square = 1, x = 1, k3;
	long double ttt, tmp;

	k3 = k*k*k;
	while (square <= k3 / square){
		tmp = (long double)((long double)k3/(long double)square);
		if (tmp == roundf(tmp)){
			ttt = (long double)(sqrt(tmp));
			if (ttt == roundf(ttt)){
				if (pow(ttt, 2) == square)
					ret++;
				else
					ret += 2;
			}
		}
		square = pow(++x, 2);
		if (x == 240)
			x = x;
	}
	return (ret);
}

int main(int av, char **ag) {
	int ret = c(2961841);
	// int ret = c(atoi(ag[1]));
	// printf("%i\n", ret);
	return 0;
}