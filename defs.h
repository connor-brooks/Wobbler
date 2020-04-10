#ifndef DEFS_H
#define DEFS_H
#include <SDL2/SDL.h>

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;
const int BUFFER = 2048 /2;
const int WIDTH = 680;
const int HEIGHT = 480;
class Synth;
class GUI_Container;

struct User_pointers {
  int* sample_num;
  Synth* synth;
  GUI_Container* gui_container;
  float* mouse_x, *mouse_y;
  SDL_Window* window;
  SDL_GLContext context;
};

struct Voice_settings {
  int carrier_wave;
  int mod_wave;
  float detune_amt;
  float modulator_ratio;
  struct {
    float attack;
    float release;
  } adsr;

  float cutoff;
  float lfo_freq;
};

enum Voice_state {
  VSTATE_PRETRIG,
  VSTATE_KEYDOWN,
  VSTATE_KEYUP,
  VSTATE_DEAD
};

enum Wave_type {
  WAVE_SINE,
  WAVE_SQUARE,
  WAVE_TRI,
  WAVE_SAW
};

#endif
