#include <math.h>
#include <stdlib.h>
#include <stdio.h>

long long x = 2;
long long y = 2;

long long next_square_y(){
	y++;
	return (pow((y-1), 2));
}

long long next_square_x(){
	x++;
	return (pow((x-1), 2));
}

// k = cbrt(square * x^2);

int c(long long k) {
	int ret = 0;
	unsigned long long square = 1, square_x = 1;

	while (square <= k*k*k/square){
		while (square_x <= k*k*k/square){
			if (k == cbrt(square * square_x)){
				if (square == square_x)
					ret++;
				else
					ret += 2;
			}
			square_x = next_square_x();
		}
		x = y;
		square_x = next_square_x();
		square = next_square_y();
	}
	return (ret);
}

int main(int av, char **ag) {
	// int ret = c(4096576);
	int ret = c(atoi(ag[1]));
	printf("%i\n", ret);
	return 0;
}