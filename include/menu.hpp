#ifndef MENU_HPP
#define MENU_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>

#include "login_screen.hpp"
#include "register_screen.hpp"
#include "player_list_screen.hpp"
#include "remove_user_screen.hpp"
#include "menu_audio.hpp"

// Enum para decidir a tela atual
enum screen_type { SCREEN_LOGIN, SCREEN_REGISTER, SCREEN_LIST, SCREEN_REMOVE };

/* Classe que representa o menu principal de forma geral:
 * - Reune a implementação de todas as telas em uma única interface
 * - Direciona o evento à tela ativa correspondente
 * - Libera os recursos utilizados
*/ 
class menu {
public:
  // Construtor
  menu(const int SCREEN_W, const int SCREEN_H, registration &data);

  // Destrutor para liberação dos recursos (bitmaps, samples)
  ~menu();

  // Reune o comportamento de todas as telas em uma única interface
  void handle_event(const ALLEGRO_EVENT &event, bool &is_open);

  // Desenha a tela ativa
  void draw(const int SCREEN_W, const int SCREEN_H, const ALLEGRO_EVENT &event);

  // Verifica se o login foi concluído para parar o loop do registro
  bool is_login_done() const;

  // Retorna a struct player com os dados do usuário logado
  player get_logged_user();

  // Reseta todas as telas para reutilização do menu em uma mesma execução
  void reset();

private:
  // Indica qual tela está ativa 
  screen_type current;

  // Efeitos sonoros das caixas de texto e botões
  ALLEGRO_SAMPLE* sample_button; 
  ALLEGRO_SAMPLE* sample_key;

  // Bitmaps da imagem de fundo, do título e da coroa do leaderboard
  ALLEGRO_BITMAP* background_menu;
  ALLEGRO_BITMAP* crown;
  ALLEGRO_BITMAP* main_menu_title;

  // Bitmaps do ícone de áudio
  ALLEGRO_BITMAP *ico_on;
  ALLEGRO_BITMAP *ico_off;
  ALLEGRO_BITMAP *ico_on_press;
  ALLEGRO_BITMAP *ico_off_press;

  // Objeto que controla o áudio do menu
  menu_audio audio_ctrl;

  // Multiset com todos os jogadores existentes
  std::multiset<player> players;

  // Declaração das telas
  login_screen login_scr;
  register_screen register_scr;
  player_list_screen list_scr;
  remove_user_screen rm_scr;

  // Fonte utilizada no menu
  ALLEGRO_FONT *pixel_sans;
};

#endif // MENU_HPP
