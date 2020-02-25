#include <SDL2/SDL.h>
#include "keyboard.h"
Keyboard::Keyboard()
{
  keydown_callback = NULL;
  keyup_callback = NULL;
}

void Keyboard::handle_keys(SDL_Event e) {
  if(e.type == SDL_TEXTINPUT) 
    keydown_callback(123);
  if(e.type == SDL_KEYUP) 
    keyup_callback(123);
}
  void Keyboard::set_keydown_callback(std::function<void (int)> callb)
{
  keydown_callback = callb;
}
  void Keyboard::set_keyup_callback(std::function<void (int)> callb) {
  keyup_callback = callb;
  }
