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
  std::vector<std::string> *argv = new std::vector<std::string>;
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
  commands.push_back(tmp);
}

void Console::exec(int argc, std::vector<std::string> *argv) {
  int command_count = commands.size();
  bool found = false;
  float arg;
  Command* tmp_cmd;
  std::string* input_cmd;

  /* For now, we only need one arg for all commands*/
  arg = (argc > 1)? stof(argv->at(1)) :  0.0f;
  input_cmd = &argv->at(0);

  /* check command exists, check right arg count, execute command */
  for(int i = 0; i < command_count; i++) {
    tmp_cmd = commands.at(i);
    if(tmp_cmd->get_name().compare(*input_cmd) == 0){
      {
        found = true;
        if(tmp_cmd->get_argc() > argc - 1)
          std::cout << "Error, not enough arguments" << std::endl;
        else
          tmp_cmd->exec(arg);
      }
    }
  }
  if (!found) {
    std::cout << "Error: \"" << *input_cmd <<"\" not found." << std::endl;
    print_help();
  }

  delete argv;
}
void Console::print_help() {
  int command_count = commands.size();
  Command* tmp_cmd;
  std::cout << "Available commands: " << std::endl;
  for(int i = 0; i < command_count; i++) {
    tmp_cmd = commands.at(i);
    std::cout << tmp_cmd->get_name() << " ";
    if(tmp_cmd->get_argc() > 0)
      std::cout << "[arg]";
    std::cout << std::endl;
  }

}
