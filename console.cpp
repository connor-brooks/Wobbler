#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include "console.h"
#include "defs.h"
#include "command.h"

Console::Console() {
}

void Console::operator()() {
  while(!*should_quit) {
    std::string cmd;
    std::cin >> cmd;
    parse(cmd);
  }
}

void Console::set_should_quit(bool *ptr) {
  should_quit = ptr;
}

void Console::parse(std::string cmd) {
  std::string tmp;
  std::stringstream stream(cmd);
  std::vector<std::string> *argv = new std::vector<std::string>;
  int argc;
  while(getline(stream, tmp, ' ')){
    argv->push_back(tmp);
  }
  argc = argv->size();
  exec(argc, argv);
}

void Console::add_command(std::string command_name, int arg_count, std::function <void (float)> callback) {
  Command* tmp = new Command(command_name, arg_count, callback);
  commands.push_back(tmp);
}

void Console::exec(int argc, std::vector<std::string> *argv) {
  int command_count = commands.size();
  std::string test = commands.at(0)->get_name();
  for(int i = 0; i < command_count; i++) {
    if(commands.at(i)->get_name().compare(argv->at(0)) == 0){
      commands.at(i)->exec(0);
    }
  }
  delete argv;
}
