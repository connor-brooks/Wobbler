#ifndef CONTROL_H
#define CONTROL_H
class Control {
    float xPos, yPos;
    float width, height;
    float verts[4][2];
    void setVerts();
  public:
    Control();
    void set_pos(float x, float y);
    void set_size(float w, float h);
    float get_x();
    float get_y();
    float get_width();
    void draw();
};
#endif
