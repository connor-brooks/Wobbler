#include <SDL2/SDL.h>
#include "keyboard.h"
Keyboard::Keyboard()
{
  keydown_callback = NULL;
  keyup_callback = NULL;
}

void Keyboard::handle_keys(SDL_Event e) {
  char down_key = e.text.text[0];
  char up_key = e.key.keysym.sym;
  char key = down_key == 0 ? up_key : down_key;
  int midi_note = 0;
  printf("Key %c\n", key);
  switch(key) {
    case 'a':
      midi_note = 36;
      break;
    case 'w':
      midi_note = 37;
      break;
    case 's':
      midi_note = 38;
      break;
    case 'e':
      midi_note = 39;
      break;
    case 'd':
      midi_note = 40;
      break;
    case 'f':
      midi_note = 41;
      break;
    case 't':
      midi_note =42;
      break;
    case 'g':
      midi_note = 43;
      break;
    case 'y':
      midi_note = 44;
      break;
    case 'h':
      midi_note = 45;
      break;
    case 'u':
      midi_note = 46;
      break;
    case 'j':
      midi_note = 47;
      break;

    default:
      break;
  }
  if(e.type == SDL_TEXTINPUT) {
    if(midi_note != 0) {
      keydown_callback(midi_note);
    }
    //    switch(key) {
    //      case 'a':
    //        keydown_callback(36);
    //        break;
    //      case 'w':
    //        keydown_callback(37);
    //        break;
    //      case 's':
    //        keydown_callback(38);
    //        break;
    //      case 'e':
    //        keydown_callback(39);
    //        break;
    //      case 'd':
    //        keydown_callback(40);
    //        break;
    //      case 'f':
    //        keydown_callback(41);
    //        break;
    //      case 't':
    //        keydown_callback(42);
    //        break;
    //      case 'g':
    //        keydown_callback(43);
    //        break;
    //      case 'y':
    //        keydown_callback(44);
    //        break;
    //      case 'h':
    //        keydown_callback(45);
    //        break;
    //      case 'u':
    //        keydown_callback(46);
    //        break;
    //      case 'j':
    //        keydown_callback(47);
    //        break;
    //
    //      default:
    //        break;
    //    }
  }
  if(e.type == SDL_KEYUP) {
    if(midi_note != 0) {
      keyup_callback(midi_note);
    }
  }
}
void Keyboard::set_keydown_callback(std::function<void (int)> callb)
{
  keydown_callback = callb;
}
void Keyboard::set_keyup_callback(std::function<void (int)> callb) {
  keyup_callback = callb;
}
