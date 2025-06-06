#ifndef PLAYER_LIST_SCREEN_HPP
#define PLAYER_LIST_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"

class player_list_screen {
public:
  player_list_screen(int screen_w, int screen_h, registration &data_ref);

  // Trata eventos (mouse) e avança/página ou retorna ao menu
  void handle_event(const ALLEGRO_EVENT &ev);

  // Desenha jogadores da página atual e os botões
  void draw(ALLEGRO_FONT *font);

  // Indica se deve voltar ao menu principal
  bool go_to_main_menu() const;

  // Reseta estado (página, flag)
  void reset();

private:
  int screen_width, screen_height;
  int current_page;
  int players_per_page;

  button next_button;
  button back_button;
  button main_menu_button;

  registration &data;
  std::vector<player> players;

  bool go_to_menu;
};

#endif // PLAYER_LIST_SCREEN_HPP
