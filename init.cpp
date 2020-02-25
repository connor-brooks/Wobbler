#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "main.h"
#include "init.h"
#include "defs.h"
void init_sdl(User_pointers* user_ptrs) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_Window* window = SDL_CreateWindow("WobWob",SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);

  user_ptrs->window = window;
  user_ptrs->context = context;
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
