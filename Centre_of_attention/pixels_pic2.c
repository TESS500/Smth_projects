#include <stdlib.h>
#include <stdio.h>

typedef struct { unsigned *pixels; unsigned width, height; } Image;
typedef struct { unsigned *values; unsigned size; } unsigned_array;

int	check_map(unsigned_array ret, Image im, int x, int y, unsigned col, int max)
{
	int i, j;
	printf("y: %d x: %d\n", y, x);
	if (im.pixels[im.width * y + x] != col)	return(1);
	// for (int l = 0; l < ret.size; l++){
	// 	if (ret.values[l] == im.width * y + x-1){  // Right Corner
	// 		printf ("\n\n// Right Corner\n\n");
	// 		i = x;
	// 		for (j = y-max; j <= y+max; j++){
	// 			if (j <= y && j != y-max) i++;
	// 			else if (j > y) i--;
	// 			if (im.pixels[im.width * j + i] != col) return (1);
	// 		}
	// 		return (0);
	// 	}
	// 	else if (ret.values[l] == im.width * y + x+1){ // Left Corner
	// 		printf ("\n\n// Left Corner\n\n");
	// 		i = x;
	// 		for (j = y-max; j <= y+max; j++){
	// 			if (j <= y && j != y-max) i--;
	// 			else if (j > y) i++;
	// 			if (im.pixels[im.width * j + i] != col) return (1);
	// 		}
	// 		return (0);
	// 	}
	// 	else if(ret.values[l] == im.width * (y+1) + x){ // Up Corner
	// 		printf ("\n\n// Up Corner\n\n");
	// 		j = y;
	// 		for (i = x-max; i <= x+max; i++){
	// 			if (i <= x && i != x-max) j--;
	// 			else if (i > x) j++;
	// 			if (im.pixels[im.width * j + i] != col) return (1);
	// 		}
	// 		return (0);
	// 	}
	// 	else if (ret.values[l] == im.width * (y-1) + x){ //Down Corner
	// 		printf ("\n\n// Down Corner\n\n");
	// 		j = y;
	// 		for (i = x-max; i <= x+max; i++){
	// 			if (i <= x && i != x-max) j++;
	// 			else if (i > x) j--;
	// 			if (im.pixels[im.width * j + i] != col) return (1);
	// 		}
	// 		return (0);
	// 	}
	// }
	while (max){   // FULL
		printf ("\n\n// FULL CHECK\n\n");
		j = y;
		for (i = x-max; i <= x+max; i++){ if (i <= x && i != x-max) j--; else if (i > x) j++; if (im.pixels[im.width * j + i] != col) return (1); }
		for(i = x+max-1;i > x-max; i--){ if (i >= x && i != x+max) j++; else if (i < x) j--; if (im.pixels[im.width * j + i] != col) return (1); }
		max--;
	}
	return (0);
		
}

unsigned_array central_pixels(Image image, unsigned colour)
{
	int max_dist, x, y;
	unsigned *values = malloc(sizeof(unsigned) * 100);
	unsigned_array ret = {values, 0};
	if (image.width == image.height) max_dist = (image.height+1)/2 - 1;
	else max_dist = image.width > image.height ? (image.height+1)/2 - 1 : (image.width+1)/2 - 1;
	while (max_dist >= 0 && !ret.size){
		for (y = max_dist; y < (int)(image.height - max_dist); y++){
			for (x = max_dist; x < (int)(image.width - max_dist); x++){				
				if (!check_map(ret, image, x , y, colour, max_dist)){
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
	unsigned image_data2[] = {1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1,
							1,1,1,1,1,1,1,1,1,1};
	Image image = { image_data, 10, 6 };
	central_pixels(image, 1);
	int i = 0;
}