#include "../../include/miniRT.h"
#include <math.h>


int32_t brightness(int32_t color, double scale)
{
  uint8_t r = (color >> 24) & 0xFF;
  uint8_t g = (color >> 16) & 0xFF;
  uint8_t b = (color >> 8) & 0xFF;
  uint8_t a = color & 0xFF;

  r *= scale;
  g *= scale;
  b *= scale;
  return ((r << 24) | (g << 16) | (b << 8) | a);
}

double remap(double a, double b, double t)
{
	return ((t-a)/(b-a));
}
