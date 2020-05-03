#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <vector>
#include <map>
#include "defs.h"
#include "command.h"


class Console {
  private:
    bool *should_quit;
    void parse(std::string cmd);
    std::map<std::string, Command*> commands;

  public:
    Console();

    void set_should_quit(bool *ptr);
    void operator()();
    void add_command(std::string command_name, int arg_count, std::function <void (float)> callback);
    void exec(int argc, std::vector<std::string> *argv);
    void print_help();

};
#endif
