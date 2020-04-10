#include <iostream>
#include "console.h"
#include "defs.h"
#include "command.h"

Console::Console() {
}

void Console::operator()() {
  while(!*should_quit) {
    std::string cmd;
    std::cin >> cmd;
    //    parse(cmd);
    //callbacks[CONS_CALLB_DO_RAND](0);
    commands.at(0)->exec(0);
  }
}


void Console::set_should_quit(bool *ptr) {
  should_quit = ptr;
}

void Console::parse(std::string cmd) {

}
void Console::add_command(std::string command_name, int arg_count, std::function <void (float)> callback) {
  Command* tmp = new Command(command_name, arg_count, callback);
  commands.push_back(tmp);
}
