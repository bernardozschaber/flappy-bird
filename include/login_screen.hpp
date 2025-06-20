#ifndef LOGIN_SCREEN_HPP
#define LOGIN_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"
#include "text_box.hpp"
#include <allegro5/allegro_font.h>

/*
  * - Serve como hub para trocar para as outras telas do menu principal
  * - Processa e valida tentativas de login
  * - Armazena informações do usuário logado
*/
class login_screen {
public:
  // Construtor
  login_screen(int screen_w, int screen_h, registration &data_ref, ALLEGRO_SAMPLE* key_s, ALLEGRO_SAMPLE* button_s);

  // Trata eventos (mouse/teclado) e repassa aos componentes
  void handle_event(const ALLEGRO_EVENT &ev);

  // Desenha todos os componentes na tela
  void draw(ALLEGRO_FONT *font);

  // Indica se deve trocar para a tela de listagem
  bool go_to_player_list() const;

  // Indica se deve trocar para a tela de registro
  bool go_to_register_screen() const;

  // Indica se deve trocar para a tela de remoção de usuário
  bool go_to_remove_screen() const;

  // Indica se o login foi finalizado
  bool login_done() const;

  // Retorna as informações do usuário que está logado
  player get_logged_user();

  // Getters de vetores dos elementos de UI para manipulação de audio
  const std::vector<text_box*>& get_text_boxes() const;
  const std::vector<button*>&  get_buttons() const;

  // Reseta caixas e flags
  void reset();

private:
  // Tamanho da tela
  int screen_width, screen_height;

  // Flags internas
  bool valid_login; // Mensagem de erro em tentativa de login inválida
  bool empty_field; // Mensagem de erro de campos vazios
  bool done; // Indica conclusão do login
  bool go_to_list; // Indica se deve trocar para a tela de listagem
  bool go_to_register; // Indica se deve trocar para a tela de registro
  bool go_to_remove; // Indica se deve trocar para a tela de remoção

  // Usuário que estã logado
  player logged_user;

  // Componentes de UI
  text_box username_box;
  text_box password_box;
  button login_button;
  button register_button;
  button view_players_button;
  button remove_user_button;

  // Referência ao objeto que manipula o arquivo de usuários
  registration &data;

  // Vetores com os elementos de UI para manipulação de audio
  std::vector<text_box*> text_boxes;
  std::vector<button*>  buttons;
};

#endif // LOGIN_SCREEN_HPP
