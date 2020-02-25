#ifndef MAIN_H
#define MAIN_H
#include "defs.h"
void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes);
void update(User_pointers* user_ptrs);
void render(User_pointers* user_ptrs);
void quit(User_pointers* user_ptrs);
#endif
