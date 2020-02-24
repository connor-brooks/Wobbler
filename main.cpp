#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>
#include <OpenGL/glu.h>
#include "libs/maximilian.h"
#include "synth.h"
#include "control.h"
#include "gui_container.h"

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;
const int BUFFER = 2048;
const int WIDTH = 680;
const int HEIGHT = 480;

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

struct User_pointers {
  int* sample_num;
  Synth* synth;
  GUI_Container* gui_cont;
  float* mouse_x, *mouse_y;
};


void init_sdl();
void init_audio(User_pointers* user_ptrs);
void audio_callback();
void init_gl();
void render(User_pointers* user_ptrs);
void quit();

SDL_Window* window = NULL;
SDL_GLContext context;


void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
  /* Extract relevent data from user pointer */
  User_pointers* user_pointers = (User_pointers*) user_data;
  int* sample_num = user_pointers->sample_num;
  Synth* synth = user_pointers->synth;

  Sint16 *buffer = (Sint16*) raw_buffer;
  int length = bytes / 2;

  for(int i = 0; i < length; i++, sample_num++)
  {
    buffer[i] = synth->tick();
  }
}

void init_sdl() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  window = SDL_CreateWindow("WobWob",SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  context = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);


  TTF_Init();
}

void init_audio(User_pointers* user_ptrs)
{
  SDL_AudioSpec spec_want;
  SDL_AudioSpec spec_have; //for error checking, l8r

  spec_want.freq = SAMPLE_RATE;
  spec_want.format = AUDIO_S16SYS;
  spec_want.channels = 1;
  spec_want.samples = BUFFER;
  spec_want.callback = audio_callback;
  //spec_want.userdata = &sample_num;
  spec_want.userdata = user_ptrs;

  SDL_OpenAudio(&spec_want, &spec_have);
}

void init_gl()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.f, 0.f, 0.f, 1.f);
}


void render(User_pointers* user_ptrs)
{
  glClear(GL_COLOR_BUFFER_BIT);

  user_ptrs->gui_cont->draw();

  //draw cursor
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2f(*user_ptrs->mouse_x, *user_ptrs->mouse_y);
  glEnd();

}

void quit()
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char* args[])
{

  struct User_pointers user_pointers;
  user_pointers.sample_num = new int(0);
  user_pointers.synth = new Synth();
  user_pointers.gui_cont = new GUI_Container();

  Control first, second, third;
  user_pointers.gui_cont->add(&first);
  user_pointers.gui_cont->add(&second);
  user_pointers.gui_cont->add(&third);

  float mouse_x, mouse_y;
  user_pointers.mouse_x = &mouse_x;
  user_pointers.mouse_y = &mouse_y;
  to_gl_coords(&mouse_x, &mouse_y, WIDTH, HEIGHT);

  bool should_quit = false;

  init_sdl();
  SDL_Event events;

  init_gl();
  init_audio(&user_pointers);

  SDL_PauseAudio(0);


  while(!should_quit)
  {
    to_gl_coords(&mouse_x, &mouse_y, WIDTH, HEIGHT);
    while(SDL_PollEvent(&events) != 0)
    {
      if(events.type == SDL_QUIT)
      {
        should_quit = true;
      }

      /* debug */
      user_pointers.synth->set_carrier_freq(mouse_x * 400);
      user_pointers.synth->set_modulator_freq(mouse_y * 30);
    }

    render(&user_pointers);
    SDL_GL_SwapWindow(window);
  }
  quit();
  return 0;
}
