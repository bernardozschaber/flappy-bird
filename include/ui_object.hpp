#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class ui_object {
public:
  ui_object(float x, float y, int width, int height);

  virtual void handle_event(const ALLEGRO_EVENT &ev) = 0;

  virtual void draw(ALLEGRO_FONT *font) = 0;

  int get_x();

  void set_x(float x);

  int get_y();

  void set_y(float y);

  int get_width();

  int get_height();

  bool contains(int mx, int my) const;

protected:
  float x, y;
  int width, height;
};

#endif
