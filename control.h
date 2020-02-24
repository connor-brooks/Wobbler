#ifndef CONTROL_H
#define CONTROL_H
class Control {
    float xPos, yPos;
    float width, height;
    float max_height;
    float verts[4][2];
    void setVerts();
    float amount;
    void update(float mouse_y);
    float* to_control_ptr;
    float to_control_min, to_control_max;
  public:
    Control();
    void set_pos(float x, float y);
    void set_size(float w, float h);
    float get_x();
    float get_y();
    float get_width();
    void draw();
    bool intersect(float x, float y);
    void assign_control(float* ptr, float min, float max);
};
#endif
