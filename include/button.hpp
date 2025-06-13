#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui_object.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

class button : public ui_object {
public:
  button(int x, int y, int width, int height, const std::string &label, ALLEGRO_SAMPLE* button_s);

  // Processa clique do mouse
  void handle_event(const ALLEGRO_EVENT &ev) override;

  // Desenha botão (fundo, borda e label)
  void draw(ALLEGRO_FONT *font) override;

  // Indica se foi clicado desde o último reset
  bool was_clicked() const;
  void reset_clicked();

  // Gets
  int get_x();
  int get_y();

  // Seta estado de clique
  void set_clicked(const bool set);

private:
  std::string label;
  bool clicked;
  ALLEGRO_SAMPLE* sample_button;
};

#endif // BUTTON_HPP
