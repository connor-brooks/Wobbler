#include <iostream>
#include "console.h"
#include "defs.h"

void Console::operator()() {
  while(!*should_quit) {
    std::string word;
    std::cin >> word;
    callbacks[CONS_CALLB_DO_RAND](0);
  }
}

void Console::set_callback(int callback_num, std::function <void (float)> callback) {
  callbacks[callback_num] = callback;
}
void Console::set_should_quit(bool *ptr) {
  should_quit = ptr;
}
