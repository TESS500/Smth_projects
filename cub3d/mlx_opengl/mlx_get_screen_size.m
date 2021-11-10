#import <AppKit/NSScreen.h>

#include "mlx.h"

void	mlx_get_screen_size(int *width, int *height)
{
	NSRect disp = [[NSScreen mainScreen]frame];
	*width = (int)disp.size.width;
	*height = (int)disp.size.height;
}
