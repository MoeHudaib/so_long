#include "fdf.h"

int	get_color(int z, int z_min, int z_max)
{
	if (z_max == z_min)
		return 0xFFFFFF; // flat map fallback

	// Normalize z to 0–255
	int normalized = 255 * (z - z_min) / (z_max - z_min);

	int red = normalized;
	int green = 255 - abs(128 - normalized) * 2;
	int blue = 255 - normalized;

	return (red << 16) | (green << 8) | blue;
}
