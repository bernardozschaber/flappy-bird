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
#include "game_loop.hpp"

/// Enum para decidir a tela atual
enum screen_type { SCREEN_LOGIN, SCREEN_REGISTER, SCREEN_LIST, SCREEN_REMOVE };

/** 
 * @class menu
 * @brief Classe que representa o menu principal de forma geral
 *
 * - Reune a implementação de todas as telas em uma única interface
 * - Direciona o evento à tela ativa correspondente
 * - Libera os recursos utilizados
 */ 
class menu {
public:
  /**
  * @brief Construtor que inicializa o menu
  * @param SCREEN_W Largura da tela
  * @param SCREEN_H Altura da tela
  * @param data Referência ao objeto que manipula os arquivos
  */
  menu(const int SCREEN_W, const int SCREEN_H, registration &data);

  /// Destrutor para liberação dos recursos (bitmaps, samples)
  ~menu();

  /**
  * @brief Reune o comportamento de todas as telas em uma única interface
  * @param event Evento passado às telas
  * @param is_open Booleano para indicar se o programa deve continuar rodando
  * @param state Ponteiro para alterar o estado do main e iniciar o jogo
  */
  void handle_event(const ALLEGRO_EVENT &event, bool &is_open, states* state);

  /**
  * @brief Desenha a tela ativa
  * @param SCREEN_W Largura da tela
  * @param SCREEN_H Altura da tela
  * @param event Evento que pode indicar se a tela deve ser desenhada
  */
  void draw(const int SCREEN_W, const int SCREEN_H, const ALLEGRO_EVENT &event);

  /**
  * @brief Verifica se o login foi concluído para parar o loop do registro
  * @return Booleano que indica o estado do login
  */
  bool is_login_done() const;

  /**
  * @brief Retorna a struct player com os dados do usuário logado
  * @return Dados do jogador logado
  */
  player get_logged_user();

  /**
  * @brief Atualiza o multiset de players para listagem
  * @param new_players Novo multiset
  */
  void set_players(const std::multiset<player> new_players);

  /// Reseta todas as telas para reutilização do menu em uma mesma execução
  void reset();

private:
  /// Indica qual tela está ativa 
  screen_type current;

  /// @name Efeitos sonoros das caixas de texto e botões
  /// @{
  ALLEGRO_SAMPLE* sample_button; 
  ALLEGRO_SAMPLE* sample_key;
  /// @}

  /// @name Bitmaps da imagem de fundo, do título e da coroa do leaderboard
  /// @{
  ALLEGRO_BITMAP* background_menu;
  ALLEGRO_BITMAP* crown;
  ALLEGRO_BITMAP* main_menu_title;
  /// @}

  /// @name Bitmaps do ícone de áudio
  /// @{
  ALLEGRO_BITMAP *ico_on;
  ALLEGRO_BITMAP *ico_off;
  ALLEGRO_BITMAP *ico_on_press;
  ALLEGRO_BITMAP *ico_off_press;
  /// @}

  /// Objeto que controla o áudio do menu
  menu_audio audio_ctrl;

  /// Multiset com todos os jogadores existentes
  std::multiset<player> players;

  /// @name Declaração das telas
  /// @{
  login_screen login_scr;
  register_screen register_scr;
  player_list_screen list_scr;
  remove_user_screen rm_scr;
  /// @}

  /// Fonte utilizada no menu
  ALLEGRO_FONT *pixel_sans;
};

#endif // MENU_HPP
