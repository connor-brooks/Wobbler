#include <iostream>
#include <SDL2/SDL.h>
#ifndef KEYBOARD_H
#define KEYBOARD_H
const float C5 = 523.25;
const float C5s = 554.37;
const float D5 = 587.33;
const float D5s  = 622.25;
const float E5  = 659.25;
const float F5  = 698.46;
const float F5s = 739.99;
const float G5  = 783.99;
const float G5s  = 830.61;
const float A5   = 880.00;
const float A5s  = 932.33;
const float B5   = 987.77;

class Keyboard {
  public:
    Keyboard();
    void handle_keys(SDL_Event e);
  void set_keydown_callback(std::function<void (int)> callb);
  void set_keyup_callback(std::function<void (int)> callb);

  private:
  std::function<void (int)> keydown_callback;
  std::function<void (int)> keyup_callback;

};
void handle_keys(SDL_Event e);
#endif
