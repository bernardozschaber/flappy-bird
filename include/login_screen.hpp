#ifndef LOGIN_SCREEN_HPP
#define LOGIN_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"
#include "text_box.hpp"
#include <allegro5/allegro_font.h>

/** 
 * @class login_screen
 * @brief Tela que lida com todo o processo de login (Menu Principal)
 *
 * - Serve como hub para trocar para as outras telas do menu principal
 * - Processa e valida tentativas de login
 * - Armazena informações do usuário logado
 */
class login_screen {
public:
  /**
  * @brief Construtor que inicializa a tela de login
  * @param screen_w Largura da tela
  * @param screen_h Altura da tela
  * @param data_ref Referência ao objeto que manipula os arquivos
  * @param key_s Efeito sonoro das caixas de texto
  * @param button_s Efeito sonoro dos botões
  */
  login_screen(int screen_w, int screen_h, registration &data_ref, ALLEGRO_SAMPLE* key_s, ALLEGRO_SAMPLE* button_s);

  /**
  * @brief Trata eventos (mouse/teclado) e repassa aos componentes
  * @param ev Evento a ser repassado
  */
  void handle_event(const ALLEGRO_EVENT &ev);

  /**
  * @brief Desenha todos os componentes na tela
  * @param font Fonte utilizada e repassada para os componentes
  */
  void draw(ALLEGRO_FONT *font);

  /**
  * @brief Indica se deve trocar para a tela de listagem
  * @return Booleano que indica a troca
  */
  bool go_to_player_list() const;

  /**
  * @brief Indica se deve trocar para a tela de registro
  * @return Booleano que indica a troca
  */
  bool go_to_register_screen() const;

  /**
  * @brief Indica se deve trocar para a tela de remoção
  * @return Booleano que indica a troca
  */
  bool go_to_remove_screen() const; 

  /**
  * @brief Indica se o login foi concluído
  * @return Booleano que indica o estado do login
  */
  bool login_done() const;

  /**
  * @brief Get dos dados do usuário que está logado
  * @return Struct com os dados do jogador logado
  */
  player get_logged_user();

  /**
  * @brief Get do vetor com ponteiros para as caixas de texto para testes e manipulação de áudio
  * @return Vetor com os ponteiros
  */
  const std::vector<text_box*>& get_text_boxes() const;

  /**
  * @brief Get do vetor com ponteiros para os botões para testes e manipulação de áudio
  * @return Vetor com os ponteiros
  */
  const std::vector<button*>&  get_buttons() const;

  /// Reseta caixas e flags
  void reset();

private:
  /// @name Tamanho da tela
  /// @{
  int screen_width;
  int screen_height;
  /// @}

  /// @name Flags internas
  /// @{
  bool valid_login; ///< Mensagem de erro em tentativa de login inválida
  bool empty_field; ///< Mensagem de erro de campos vazios
  bool done; ///< Indica conclusão do login
  bool go_to_list; ///< Indica se deve trocar para a tela de listagem
  bool go_to_register; ///< Indica se deve trocar para a tela de registro
  bool go_to_remove; ///< Indica se deve trocar para a tela de remoção
  /// @}

  /// Usuário que estã logado
  player logged_user;

  /// @name Componentes de UI
  /// @{
  text_box username_box;
  text_box password_box;
  button login_button;
  button register_button;
  button view_players_button;
  button remove_user_button;
  /// @}

  /// Referência ao objeto que manipula o arquivo de usuários
  registration &data;

  /// @name Vetores com os elementos de UI para manipulação de audio e testes
  /// @{
  std::vector<text_box*> text_boxes;
  std::vector<button*>  buttons;
  /// @}
};

#endif // LOGIN_SCREEN_HPP
