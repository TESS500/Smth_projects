#include <stdlib.h>
#include <stdio.h>

typedef struct { unsigned *pixels; unsigned width, height; } Image;
typedef struct { unsigned *values; unsigned size; } unsigned_array;

// void	check_map(Image im, int x, int y, int steps, unsigned col, int *check)
// {
// 	if (steps == 0)										return;
// 	printf("x: %d y: %d\n", x, y);
// 	if (im.pixels[im.width * y + x] != col)	{*check+=1;	return; }
// 	check_map(im, x + 1, y, steps - 1, col, check);
// 	check_map(im, x, y + 1, steps - 1, col, check);
// 	check_map(im, x - 1, y, steps - 1, col, check);
// 	check_map(im, x, y - 1, steps - 1, col, check);
// }

// //=-------------------------

// unsigned_array central_pixels(Image image, unsigned colour)
// {
// 	int max_dist, x, y, check, mem = 1;
// 	unsigned *values = malloc(sizeof(unsigned) * 100);
// 	unsigned_array ret = {values, 0};
// 	if (image.width == image.height) max_dist = (image.height+1)/2 - 1;
// 	else max_dist = image.width > image.height ? (image.height+1)/2 - 1 : (image.width+1)/2 - 1;
// 	while (max_dist >= 0 && !ret.size){
// 		for (y = max_dist; y < image.height - max_dist; y++){
// 			for (x = max_dist; x < image.width - max_dist; x++){
// 				check = 0;
// 				check_map(image, x , y, max_dist + 1, colour, &check);
// 				printf("\n-----------\n");
// 				if (!check){
// 					ret.values[ret.size++] = image.width * y + x;
// 					printf("value: %u, max: %d", ret.values[ret.size - 1], max_dist);
// 				}
// 			}
// 		}
// 		max_dist--;
// 	}
// 	for (int i = 0; i < ret.size; i++)
// 		printf("value: %u\n", ret.values[i]);
// 	return (ret);
// }

void	check_map(Image im, int x, int y, int steps, unsigned col, int *check)
{
	if (steps == 0 || *check)							return;
	printf("y: %d x: %d\n", y, x);
	if (im.pixels[im.width * y + x] != col)	{*check+=1;	return; }
	check_map(im, x + 1, y, steps - 1, col, check);
	check_map(im, x, y + 1, steps - 1, col, check);
	check_map(im, x - 1, y, steps - 1, col, check);
	check_map(im, x, y - 1, steps - 1, col, check);
}

unsigned_array central_pixels(Image image, unsigned colour)
{
	int max_dist, x, y, check;
	unsigned *values = malloc(sizeof(unsigned) * 100), len = image.height * image.width;
	unsigned_array ret = {values, 0};
	if (image.width == image.height) max_dist = (image.height+1)/2 - 1;
	else max_dist = image.width > image.height ? (image.height+1)/2 - 1 : (image.width+1)/2 - 1;
	while (max_dist >= 0 && !ret.size){
		for (y = max_dist; y < (int)(image.height - max_dist); y++){
			for (x = max_dist; x < (int)(image.width - max_dist); x++){
				check = 0;
				check_map(image, x , y, max_dist + 1, colour, &check);
				if (!check){
					ret.values[ret.size++] = image.width * y + x;
					printf("value: %u, max: %d", ret.values[ret.size - 1], max_dist);
				}
			}
		}
		max_dist--;
	}
	return (ret);
}

int main(){
	unsigned image_data[] = {1,1,4,4,4,4,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,2,2,2,2,2,2,
							1,1,1,1,1,3,2,2,2,2,
							1,1,1,1,1,3,3,3,2,2,
							1,1,1,1,1,1,3,3,3,3};
	Image image = { image_data, 10, 6 };
	central_pixels(image, 1);
	int i = 0;
}