#ifndef GUI_CONTAINER
#define GUI_CONTAINER
#include <iostream>
#include <vector>
#include "control.h"
class GUI_Container {
  private:
    float x_pos, y_pos;
    float padding;
    std::vector<Control*> controls;
    void place_control(Control* item);
  public:
    GUI_Container();
    void add(Control* item);
    void draw();
    void intersect(float x, float y);
};
#endif
