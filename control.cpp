#include <iostream>
#include <SDL2/SDL_opengl.h>
#include "control.h"
#include <math.h>
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
  //printf("Control init\n");
  xPos = -0.9;
  yPos = -0.9;
  width = 0.13;
  height = 1.6;
  max_height = 1.6;
  setVerts();
  to_control_funct = NULL;
  to_control_min = 0.0f;
  to_control_max = 1.0f;
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

bool Control::intersect(float x, float y) {
  if(x >= verts[0][0] && x <= verts[2][0])
    update(y);
  return true;
}

void Control::set_amt(float amt) {
  if(!(amt > 1.0) && !(amt <0.0)){
    height = max_height * amt;
    setVerts();
    if(to_control_funct != NULL)
      to_control_funct(amt * to_control_max);
  }
}

void Control::update(float mouse_y) {
  float amount = (mouse_y - yPos) / max_height;
  set_amt(amount);
}

void Control::assign_control(std::function<void (float)> func, float min, float max)
{
  to_control_funct = func;
  to_control_min = min;
  to_control_max = max;
}
