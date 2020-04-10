#include <iostream>
#include "command.h"

Command::Command(std::string cmd_name, int argc, std::function<void (float)> callb) {
  command_name = cmd_name;
  arg_count = argc;
  callback = callb;
}
void Command::exec(float val) {
  callback(val);
}

std::string Command::get_name() {
  return command_name;
}

int Command::get_argc() {
  return arg_count;
}
