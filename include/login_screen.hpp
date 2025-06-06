#ifndef LOGIN_SCREEN_HPP
#define LOGIN_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"
#include "text_box.hpp"
#include <allegro5/allegro_font.h>

class login_screen {
public:
  login_screen(int screen_w, int screen_h, registration &data_ref);

  // Trata eventos (mouse/teclado) e repassa aos componentes
  void handle_event(const ALLEGRO_EVENT &ev);

  // Desenha todos os componentes na tela
  void draw(ALLEGRO_FONT *font);

  // Indica se deve trocar para a tela de listagem
  bool go_to_player_list() const;

  // Indica se deve trocar para a tela de registro
  bool go_to_register_screen() const;

  // Indica se o login foi finalizado
  bool login_done() const;

  std::string get_logged_user();

  // Reseta caixas e flags
  void reset();

private:
  int screen_width, screen_height;

  bool valid_login;
  bool done;

  std::string logged_user;

  // Componentes de UI
  text_box username_box;
  text_box password_box;
  button login_button;
  button register_button;
  button view_players_button;

  // registro de jogadores
  registration &data;

  bool go_to_list;
  bool go_to_register;
};

#endif // LOGIN_SCREEN_HPP
