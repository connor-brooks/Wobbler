#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>

class Command {
  private:
    std::string command_name;
    int arg_count;
    std::function<void (float)> callback;
  public:
    Command(std::string cmd_name, int argc, std::function<void (float)> callb);
    void exec(float val);
    std::string get_name();
    int get_argc();
};
#endif
