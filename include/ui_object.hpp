#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class ui_object {
public:
  ui_object(int x, int y, int width, int height);

  virtual void handle_event(const ALLEGRO_EVENT &ev) = 0;

  virtual void draw(ALLEGRO_FONT *font) = 0;

  bool contains(int mx, int my) const;

protected:
  int x, y;
  int width, height;
};

#endif
