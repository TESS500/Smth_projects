#include <stdlib.h>
#include <stdio.h>

typedef struct { unsigned *pixels; unsigned width, height; } Image;
typedef struct { unsigned *values; unsigned size; } unsigned_array;

void print_rad(int **rad, unsigned max, Image im)
{
	int i, j;
	for (i = 0; i <= max; i++) {
		if (rad[i][0] == 0)
			printf("%d\n", rad[i][0]);
		else
			for (j = 0; j < im.height * im.width; j++)
				printf("%d ", rad[i][j]);
			printf("\n"); }
	printf("\n\n\n");
}

int	check_map(int **radius, Image im, unsigned x, unsigned y, unsigned col, unsigned max)
{
	unsigned i, j, k = 1, r;
	if (im.pixels[im.width * y + x] != col)	return(1);
	while (k <= max){
		j = y;
		for (i = x-k; i <= x+k; i++){
			if (i <= x && i != x-k) j--;
			else if (i > x) j++;
			if (im.pixels[im.width * j + i] != col) {
				r = 1;
				if (radius[k - 1][0] == 0){
					free (radius[k - 1]);
					radius[k - 1] = (int*)malloc(sizeof(int) * im.height * im.width);
					radius[k - 1][0] = -1;
						for (int p = 1; p < im.height * im.width; p++)
							radius[k - 1][p] = -1;
				}
				while (radius[k - 1][r] != -1 && radius[k - 1][r] != (int)(im.width * y + x)) r++;
				radius[k - 1][r] = im.width * y + x;
				print_rad(radius, max, im);
				return (1); }
		}
		for(i = x+k-1;i > x-k; i--){
			if (i >= x && i != x+k) j++;
			else if (i < x) j--;
			if (im.pixels[im.width * j + i] != col) {
				r = 1;
				if (radius[k - 1][0] == 0){
					free (radius[k - 1]);
					radius[k - 1] = (int*)malloc(sizeof(int) * im.height * im.width);
					radius[k - 1][0] = -1;
						for (int p = 1; p < im.height * im.width; p++)
							radius[k - 1][p] = -1;
				}
				while (radius[k - 1][r] != -1 && radius[k - 1][r] != (int)(im.width * y + x)) r++;
				radius[k - 1][r] = im.width * y + x;
				print_rad(radius, max, im);
				return (1); }
		}
		k++;
	}
	r = 1;
	if (radius[k - 1][0] == 0){
		free (radius[k - 1]);
		radius[k - 1] = (int*)malloc(sizeof(int) * im.height * im.width);
		radius[k - 1][0] = -1;
			for (int p = 1; p < im.height * im.width; p++)
				radius[k - 1][p] = -1;
	}
	while (radius[k - 1][r] != -1 && radius[k - 1][r] != (int)(im.width * y + x)) r++;
	radius[k - 1][r] = im.width * y + x;
	print_rad(radius, max, im);
	return (0);	
}

unsigned_array central_pixels(Image image, unsigned colour)
{
	int **rad;
	unsigned *values = malloc(sizeof(unsigned) * 100), x, y, max_dist;
	unsigned_array ret = {values, 0};
	if (image.width == image.height) max_dist = (image.height+1)/2 - 1;
	else max_dist = image.width > image.height ? (image.height+1)/2 - 1 : (image.width+1)/2 - 1;
	//--------------------
	int mm = max_dist;
	rad = (int**)malloc(sizeof(int*) * (max_dist + 1));
	for (int i = 0; i <= max_dist; i++) {
		rad[i] = (int*)malloc(sizeof(int) * 1); rad[i][0] = 0; }
	while (max_dist != -1 && !ret.size){
		y = max_dist;
		for (x = max_dist; x < image.width - max_dist; x++)				
			check_map(rad, image, x , y, colour, max_dist);
   		x--;
		for (y = max_dist; y < image.height - max_dist; y++)
			check_map(rad, image, x , y, colour, max_dist);
    	y--;
		for (x = image.width - max_dist; x > max_dist; x--)				
			check_map(rad, image, x , y, colour, max_dist);
		for (y = image.height - max_dist; y > max_dist; y--)
			check_map(rad, image, x , y, colour, max_dist);
		if (rad[max_dist][0] == -1)
			for (unsigned i = 1; rad[max_dist][i] != -1; i++)
				ret.values[ret.size++] = rad[max_dist][i];
		max_dist--;
	}
	for (int i = 0; i < ret.size; i++)
		printf("%d ", ret.values[i]);
	return (ret);
}

int main(){
	unsigned image_data[] = {1,1,4,4,4,4,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,1,3,2,2,2,2,
							1,1,1,1,1,3,3,3,2,2,
							1,1,1,1,1,1,3,3,3,3};
	// unsigned image_data2[] = {1,1,1,1,1,1,1,1,1,1,
	// 						1,1,1,1,1,1,1,1,1,1,
	// 						1,1,1,1,1,1,1,1,1,1,
	// 						1,1,1,1,1,1,1,1,1,1,
	// 						1,1,1,1,1,1,1,1,1,1,
	// 						1,1,1,1,1,1,1,1,1,1};
	Image image = { image_data, 10, 6 };
	central_pixels(image, 2);
	int i = 0;
}