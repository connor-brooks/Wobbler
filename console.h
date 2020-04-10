#include <iostream>
#include "defs.h"
class Console {
  private:
    std::function<void (float)> callbacks[2];
    bool *should_quit;
  public:
    void set_callback(int callback_num, std::function <void (float)> callback);

    void set_should_quit(bool *ptr);
    void operator()();

};

