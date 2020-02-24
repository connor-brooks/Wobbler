#include <iostream>
#include <SDL2/SDL_opengl.h>
#include "control.h"
    void Control::setVerts() {
      // Create verts
      verts[0][0] = xPos;
      verts[0][1] = yPos;

      verts[1][0] = xPos + width;
      verts[1][1] = yPos;

      verts[2][0] = xPos + width;
      verts[2][1] = yPos + height;

      verts[3][0] = xPos;
      verts[3][1] = yPos + height;
    }
Control::Control()
    {
      printf("Control init\n");
      xPos = -0.9;
      yPos = -0.9;
      width = 0.2;
      height = 1.6;
      setVerts();
    }

    void Control::set_pos(float x, float y)
    {
      xPos = x;
      yPos = y;
      setVerts();
    }

    void Control::set_size(float w, float h)
    {
      width = w;
      height = h;
      setVerts();
    }

    float Control::get_x() {
      return xPos;
    }

    float Control::get_y() {
      return yPos;
    }

    float Control::get_width() {
      return width;
    }

    void Control::draw()
    {
      glBegin(GL_QUADS);
      glVertex2f(verts[0][0], verts[0][1]);
      glVertex2f(verts[1][0], verts[1][1]);
      glVertex2f(verts[2][0], verts[2][1]);
      glVertex2f(verts[3][0], verts[3][1]);
      glEnd();
    }

