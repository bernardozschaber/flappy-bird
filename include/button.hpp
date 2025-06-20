#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui_object.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

// Classe que representa os botões da interface do menu: Herda da classe genêrica de objetos de UI
class button : public ui_object {
public:
  // Construtor
  button(int x, int y, int width, int height, const std::string &label, ALLEGRO_SAMPLE* button_s);

  // Processa clique do mouse
  void handle_event(const ALLEGRO_EVENT &ev) override;

  // Desenha o botão (fundo, borda e label)
  void draw(ALLEGRO_FONT *font) override;

  // Indica se foi clicado desde o último reset
  bool was_clicked() const;
  void reset_clicked();

  // Gets
  int get_x();
  int get_y();

  // Seta estado de clique
  void set_clicked(const bool set);

  // Seta o efeito sonoro (controlado pelo menu_audio)
  void set_sample(ALLEGRO_SAMPLE* s);

private:
  std::string label; // Texto presente no botão
  bool clicked; // Indica se o botão foi clicado
  ALLEGRO_SAMPLE* sample_button; // Efeito sonoro de clique do botão
};

#endif // BUTTON_HPP
