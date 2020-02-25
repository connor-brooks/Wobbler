#include <SDL2/SDL.h>
#include "keyboard.h"
Keyboard::Keyboard()
{
  keydown_callback = NULL;
  keyup_callback = NULL;
}

void Keyboard::handle_keys(SDL_Event e) {
  if(e.type == SDL_TEXTINPUT) {
    char key = e.text.text[0];
    switch(key) {
      case 'a':
        keydown_callback(36);
        break;
      case 'w':
        keydown_callback(37);
        break;
      case 's':
        keydown_callback(38);
        break;
      case 'e':
        keydown_callback(39);
        break;
      case 'd':
        keydown_callback(40);
        break;
      case 'f':
        keydown_callback(41);
        break;
      case 't':
        keydown_callback(42);
        break;
      case 'g':
        keydown_callback(43);
        break;
      case 'y':
        keydown_callback(44);
        break;
      case 'h':
        keydown_callback(45);
        break;
      case 'u':
        keydown_callback(46);
        break;
      case 'j':
        keydown_callback(47);
        break;

      default:
        break;
    }
  }
  if(e.type == SDL_KEYUP)
    keyup_callback(60);
}
void Keyboard::set_keydown_callback(std::function<void (int)> callb)
{
  keydown_callback = callb;
}
void Keyboard::set_keyup_callback(std::function<void (int)> callb) {
  keyup_callback = callb;
}
