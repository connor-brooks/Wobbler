#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>
#include <OpenGL/glu.h>
#include "main.h"
#include "init.h"
#include "libs/maximilian.h"
#include "synth.h"
#include "control.h"
#include "gui_container.h"
#include "utils.h"
#include "defs.h"

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

void render(User_pointers* user_ptrs)
{
  glClear(GL_COLOR_BUFFER_BIT);

  user_ptrs->gui_container->draw();

  //draw cursor (debug)
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2f(*user_ptrs->mouse_x, *user_ptrs->mouse_y);
  glEnd();

}

void quit(User_pointers* user_ptrs)
{
  SDL_DestroyWindow(user_ptrs->window);
  delete user_ptrs->sample_num;
  SDL_Quit();
}

void update(User_pointers* user_ptrs) {

    float* mouse_x = user_ptrs->mouse_x;
    float* mouse_y = user_ptrs->mouse_y;
    GUI_Container* gui_container = user_ptrs->gui_container;
    to_gl_coords(mouse_x, mouse_y, WIDTH, HEIGHT);
    gui_container->intersect(*mouse_x, *mouse_y);
}

int main(int argc, char* args[])
{

  bool should_quit = false;

  /* create needed struct */
  struct User_pointers user_pointers;
  user_pointers.sample_num = new int(0);
  Synth synth;
  user_pointers.synth = &synth;

  /* main init */
  init_sdl(&user_pointers);
  SDL_Event events;
  init_gl();
  init_audio(&user_pointers);
  SDL_PauseAudio(0);

  /* setup releative mouse pos */
  float mouse_x, mouse_y;
  user_pointers.mouse_x = &mouse_x;
  user_pointers.mouse_y = &mouse_y;
  to_gl_coords(&mouse_x, &mouse_y, WIDTH, HEIGHT);

  /* Assign button control */
  Control first, second, third;
  first.assign_control([&](float freq){synth.set_carrier_freq(freq);}, 
      0, 800);
  second.assign_control([&](float freq){synth.set_modulator_freq(freq);}, 
      0, 50);

  /* setup gui */
  GUI_Container gui_container;
  user_pointers.gui_container = &gui_container;
  gui_container.add(&first);
  gui_container.add(&second);
  gui_container.add(&third);

  /* main loop */
  while(!should_quit)
  {
    while(SDL_PollEvent(&events) != 0)
    {
      if(events.type == SDL_QUIT)
      {
        should_quit = true;
      }
    }

    update(&user_pointers);
    render(&user_pointers);
    SDL_GL_SwapWindow(user_pointers.window);
  }

  quit(&user_pointers);
  return 0;
}
