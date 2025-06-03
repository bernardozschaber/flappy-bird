#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui_object.hpp"
#include <string>

class button : public ui_object {
public:
  button(int x, int y, int width, int height, const std::string &label);

  // Processa clique do mouse
  void handle_event(const ALLEGRO_EVENT &ev) override;

  // Desenha botão (fundo, borda e label)
  void draw(ALLEGRO_FONT *font) override;

  // Indica se foi clicado desde o último reset
  bool was_clicked() const { return clicked; }
  void reset_clicked() { clicked = false; }

private:
  std::string label;
  bool clicked;
};

#endif // BUTTON_HPP
