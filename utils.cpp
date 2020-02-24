#include <iostream>
#include <SDL2/SDL.h>
#include "defs.h"
void to_gl_coords(float* x, float* y, int wi_width, int wi_height){
  int cur_x, cur_y;
  SDL_GetMouseState(&cur_x, &cur_y);
  float c_x = (float) cur_x / (float) WIDTH;
  float c_y = (float) cur_y / (float) HEIGHT;
  c_x = (c_x * 2) - 1;
  c_y = -((c_y * 2) - 1);
  printf("mouse x %f y %f\n", c_x, c_y);
  *x = c_x;
  *y = c_y;
}
