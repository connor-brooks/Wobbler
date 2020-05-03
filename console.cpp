#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "console.h"
#include "defs.h"
#include "command.h"

Console::Console() {
}

void Console::operator()() {
  while(!*should_quit) {
    std::string cmd;
    std::cout << "Wobbler> ";
    getline(std::cin, cmd);
    parse(cmd);
  }
}

void Console::set_should_quit(bool *ptr) {
  should_quit = ptr;
}

void Console::parse(std::string cmd) {
  std::string tmp;
  std::stringstream stream(cmd);
  auto *argv = new std::vector<std::string>;
  int argc;

  /* Split to vector */
  while(getline(stream, tmp, ' ')){
    argv->push_back(tmp);
  }
  argc = argv->size();
  if (argc > 0)
    exec(argc, argv);
}

void Console::add_command(std::string command_name, int arg_count, std::function <void (float)> callback) {
  Command* tmp = new Command(command_name, arg_count, callback);
  commands.insert(std::pair<std::string, Command*> (command_name, tmp));
}

void Console::exec(int argc, std::vector<std::string> *argv) {
  float arg;
  Command* tmp_cmd;
  std::string* input_cmd;

  /* For now, we only need one arg for all commands*/
  arg = (argc > 1)? stof(argv->at(1)) :  0.0f;
  input_cmd = &argv->at(0);

  if(commands.count(*input_cmd) > 0) {
    tmp_cmd = commands.at(*input_cmd);
    if(tmp_cmd->get_argc() > argc - 1)
      std::cout << "Error, not enough arguments" << std::endl;
    else
      tmp_cmd->exec(arg);
  }
  else {
    std::cout << "Error: \"" << *input_cmd <<"\" not found." << std::endl;
  }
  delete argv;
}

void Console::print_help() {
  std::cout << "Available commands: " << std::endl;
  for(auto& tmp_cmd: commands) {
    std::cout << tmp_cmd.second->get_name() << " ";
    if(tmp_cmd.second->get_argc() > 0)
      std::cout << "[arg]";
    std::cout << std::endl;
  }
}
