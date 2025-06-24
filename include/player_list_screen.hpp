#ifndef PLAYER_LIST_SCREEN_HPP
#define PLAYER_LIST_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"

/** 
 * @class player_list_screen
 * @brief Lista todos os jogadores em ordem decrescente de score e indica os jogadores com o recorde máximo
 */ 
class player_list_screen {
public:
  /**
  * @brief Construtor que inicializa a tela de listagem
  * @param screen_w Largura da tela
  * @param screen_h Altura da tela
  * @param button_s Efeito sonoro dos botões
  * @param crown Sprite de coroa para indicar quem tem o maior score
  * @param set Multiset com todos os jogadores a serem listados
  * @param data_ref Referência ao objeto que manipula os arquivos
  */
  player_list_screen(int screen_w, int screen_h, ALLEGRO_SAMPLE* button_s, ALLEGRO_BITMAP* crown, const std::multiset<player> &set, registration& data_ref);

  /**
  * @brief Avança/Retorna páginas ou volta ao menu
  * @param ev Evento a ser repassado aos botões
  */
  void handle_event(const ALLEGRO_EVENT &ev);

  /**
  * @brief Desenha os jogadores listados e os botões
  * @param font Fonte utilizada
  */
  void draw(ALLEGRO_FONT *font);

  /**
  * @brief Indica se deve voltar ao menu
  * @return Booleano que indica a volta
  */
  bool go_to_main_menu() const;

  /**
  * @brief Get do vetor de elementos de UI para manipulação de audio e testes
  * @return Vetor com os ponteiros para os elementos
  */
  const std::vector<button*>&  get_buttons() const;

  /**
  * @brief Indica a página atual
  * @return Valor da página atual
  */
  int get_current_page() const;

  /// Reseta estado (página, flag)
  void reset();

private:
  /// @name Atributos básicos da tela de listagem
  /// @{
  int screen_width, screen_height; ///< Tamanho
  int current_page; ///< Página atual (começa em 0)
  int players_per_page; ///< Quantos usuários impressos por página
  /// @}

  /// @name Declaração dos botões com composição de classes
  /// @{
  button next_button;
  button back_button;
  button main_menu_button;
  /// @}

  /// Multiset com todos os jogadores recebido do objeto do tipo registration
  const std::multiset<player> &players;

  /// Imagem da coroa que indica jogadores com o maior score
  ALLEGRO_BITMAP* crown;

  /// Vetor de elementos de UI para manipulação de audio
  std::vector<button*>  buttons;

  /// Referência ao objeto que manipula os arquivos
  registration& data;

  /// Indica se deve voltar para o menu principal
  bool go_to_menu;
};

#endif // PLAYER_LIST_SCREEN_HPP
