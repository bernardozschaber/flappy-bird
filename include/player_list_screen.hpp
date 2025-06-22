#ifndef PLAYER_LIST_SCREEN_HPP
#define PLAYER_LIST_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"

// Lista todos os jogadores em ordem decrescente de score e indica os jogadores com o recorde máximo
class player_list_screen {
public:
  // Construtor
  player_list_screen(int screen_w, int screen_h, ALLEGRO_SAMPLE* button_s, ALLEGRO_BITMAP* crown, const std::multiset<player> &set, registration& data_ref);

  // Trata eventos (mouse) e avança/página ou retorna ao menu
  void handle_event(const ALLEGRO_EVENT &ev);

  // Desenha jogadores da página atual e os botões
  void draw(ALLEGRO_FONT *font);

  // Indica se deve voltar ao menu principal
  bool go_to_main_menu() const;

  // Getter do vetore de elementos de UI para manipulação de audio
  const std::vector<button*>&  get_buttons() const;

  // Indica qual a página atual
  int get_current_page() const;

  // Reseta estado (página, flag)
  void reset();

private:
  // Atributos básicos da tela de listagem
  int screen_width, screen_height; // Tamanho
  int current_page; // Página atual (começa em 0)
  int players_per_page; // Quantos usuários impressos por página

  // Declaração dos botões com composição de classes
  button next_button;
  button back_button;
  button main_menu_button;

  // Multiset com todos os jogadores recebido do objeto do tipo registration
  const std::multiset<player> &players;

  // Imagem da coroa que indica jogadores com o maior score
  ALLEGRO_BITMAP* crown;

  // Vetor de elementos de UI para manipulação de audio
  std::vector<button*>  buttons;

  // Referência ao objeto que manipula os arquivos
  registration& data;

  // Indica se deve voltar para o menu principal
  bool go_to_menu;
};

#endif // PLAYER_LIST_SCREEN_HPP
