#include "ui_object.hpp"

ui_object::ui_object(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

bool ui_object::contains(int mx, int my) const {
  return (mx >= x && mx <= x + width && my >= y && my <= y + height);
}
