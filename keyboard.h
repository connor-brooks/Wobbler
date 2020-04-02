#include <iostream>
#include <SDL2/SDL.h>
#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
  public:
    Keyboard();
    void handle_keys(SDL_Event e);
    void set_keydown_callback(std::function<void (int)> callb);
    void set_keyup_callback(std::function<void (int)> callb);

  private:
    std::function<void (int)> keydown_callback;
    std::function<void (int)> keyup_callback;
    float octave;

};
void handle_keys(SDL_Event e);
#endif
