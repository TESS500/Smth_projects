#include <stdlib.h>
#include <stdio.h>

typedef struct { unsigned *pixels; unsigned width, height; } Image;
typedef struct { unsigned *values; unsigned size; } unsigned_array;


int	check_map(int **radius, unsigned_array *ret, Image im, unsigned x, unsigned y, unsigned col, int max)
{
	int i, j, k = 1, a, b , r;
	if (im.pixels[im.width * y + x] != col)	return(1);
	while (k <= max){  // FULL
		printf ("\n\n// FULL CHECK\n\n");
		j = y;
		for (i = x-k; i <= x+k; i++){
			if (i <= x && i != x-k) j--;
			else if (i > x) j++;
			if (im.pixels[im.width * j + i] != col) {
				r = 0;
				while (radius[k - 1][r] != -1 && radius[k - 1][r] != im.width * y + x) r++;
				radius[k - 1][r] = im.width * y + x;
				return (1); }
		}
		for(i = x+k-1;i > x-k; i--){
			if (i >= x && i != x+k) j++;
			else if (i < x) j--;
			if (im.pixels[im.width * j + i] != col) {
				r = 0;
				while (radius[k - 1][r] != -1 && radius[k - 1][r] != im.width * y + x) r++;
				radius[k - 1][r] = im.width * y + x;
				return (1); }
		}
		k++;
	}
	r = 0;
	while (radius[k - 1][r] != -1 && radius[k - 1][r] != im.width * y + x) r++;
	radius[k - 1][r] = im.width * y + x;
	return (0);	
}

unsigned_array central_pixels(Image image, unsigned colour)
{
	int max_dist, **rad;
	unsigned *values = malloc(sizeof(unsigned) * 100), x, y;
	unsigned_array ret = {values, 0};
	if (image.width == image.height) max_dist = (image.height+1)/2 - 1;
	else max_dist = image.width > image.height ? (image.height+1)/2 - 1 : (image.width+1)/2 - 1;
	//--------------------
	rad = (int**)malloc(sizeof(int*) * (max_dist + 1));
	for (int i = 0; i <= max_dist; i++)
		rad[i] = (int*)malloc(sizeof(int) * image.height * image.width);
	for (y = 0; y <= max_dist; y++)
		for (x = 0; x < image.height * image.width; x++)
			rad[y][x] = -1;
	for (y = 0; y < max_dist; y++){
		for (x = 0; x < image.height * image.width; x++)
			printf("%d ", rad[y][x]);
		printf ("\n");
	}
	while (max_dist >= 0 && !ret.size){
		y = max_dist;
		for (x = max_dist; x < image.width - max_dist; x++)				
			check_map(rad, &ret, image, x , y, colour, max_dist);
		x--;
		for (y = max_dist; y < image.height - max_dist; y++)
			check_map(rad, &ret, image, x , y, colour, max_dist);
		y--;
		for (x = image.width - max_dist; x > max_dist; x--)				
			check_map(rad, &ret, image, x , y, colour, max_dist);
		for (y = image.height - max_dist; y > max_dist; y--)
			check_map(rad, &ret, image, x , y, colour, max_dist);
		if (rad[max_dist][0] > -1) {
			for (unsigned i = 0; rad[max_dist][i] != -1; i++) {
				ret.values[ret.size++] = rad[max_dist][i];
				printf("value: %u, max: %d", ret.values[ret.size - 1], max_dist);
			}
		}
		max_dist--;
	}	
	printf("Max: %d Values:  ", max_dist);
	for (int m = 0; m < ret.size; m++)
		printf("%u ", ret.values[m]);
	printf("\n");
	return (ret);
}

int main(){
	unsigned image_data[] = {1,1,4,4,4,4,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,1,3,2,2,2,2,
							1,1,1,1,1,3,3,3,2,2,
							1,1,1,1,1,1,3,3,3,3};
	unsigned image_data2[] = {1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1};
	Image image = { image_data, 10, 6 };
	central_pixels(image, 5);
	int i = 0;
}