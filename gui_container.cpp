#include <iostream>
#include "gui_container.h"
#include "control.h"
GUI_Container::GUI_Container() {
      printf("container init\n");
      x_pos = -0.9;
      y_pos = -0.9;
      padding = 0.1;
    }

    void GUI_Container::place_control(Control* item) {
      float last_x = controls.back()->get_x();
      float last_y = controls.back()->get_y();
      float last_width = controls.back()->get_width();
      item->set_pos(last_x + last_width + padding,
          last_y);
    }
    void GUI_Container::add(Control* item) {
      /* if added control is first one in container,
       * stick it to the left */
      if(controls.size() == 0) item->set_pos(x_pos, y_pos);
      /* otherwise place it, taking into account width and padding */
      else place_control(item);
      controls.push_back(item);
    }

    void GUI_Container::draw() {
      int control_count = controls.size();
      if(control_count == 0)
        return;
      for(int i = 0; i < control_count; i++) {
        printf("Control %d\n", i);
        controls.at(i)->draw();
      }
    }

