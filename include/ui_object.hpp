#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// Classe abstrata genêrica de objetos de interface
class ui_object {
public:
  // Construtor
  ui_object(float x, float y, int width, int height);

  // Método que lida com eventos do Allegro
  virtual void handle_event(const ALLEGRO_EVENT &ev) = 0;

  // Desenha o objeto  
  virtual void draw(ALLEGRO_FONT *font) = 0;

  // Gets
  int get_x();
  int get_y();
  int get_width();
  int get_height();

  // Sets
  void set_x(float x);
  void set_y(float y);

  // Verifica se o mouse está em cima do objeto
  bool contains(int mx, int my) const;

protected:
  // Atributos básicos de tamanho e posição
  float x, y;
  int width, height;
};

#endif // UIOBJECT_HPP
