#ifndef DEFS_H
#define DEFS_H
#include <SDL2/SDL.h>
#include "synth.h"
#include "gui_container.h"

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;
const int BUFFER = 2048;
const int WIDTH = 680;
const int HEIGHT = 480;

struct User_pointers {
  int* sample_num;
  Synth* synth;
  GUI_Container* gui_container;
  float* mouse_x, *mouse_y;
  SDL_Window* window;
  SDL_GLContext context;
};

#endif
