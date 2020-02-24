#ifndef MAIN_H
#define MAIN_H
#include "defs.h"
void init_sdl(User_pointers* user_ptrs);
void init_audio(User_pointers* user_ptrs);
void audio_callback();
void init_gl();
void render(User_pointers* user_ptrs);
void quit(User_pointers* user_ptrs);
#endif
