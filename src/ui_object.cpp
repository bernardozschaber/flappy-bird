#include "ui_object.hpp"

ui_object::ui_object(float x, float y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

bool ui_object::contains(int mx, int my) const {
  return (mx >= x && mx <= x + width && my >= y && my <= y + height);
}

int ui_object::get_x(){
  return x;
}

int ui_object::get_y(){
  return y;
}

int ui_object::get_width(){
  return width;
}

int ui_object::get_height(){
  return height;
}

void ui_object::set_y(float posy){
  this->y=posy;
}

void ui_object::set_x(float posx){
  this->x=posx;
}
