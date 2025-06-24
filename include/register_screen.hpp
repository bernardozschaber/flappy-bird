#ifndef REGISTER_SCREEN_HPP
#define REGISTER_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"
#include "text_box.hpp"
#include <allegro5/allegro_font.h>

/** 
 * @class register_screen
 * @brief Tela que lida com todo o processo de registro de novos usuários
 *
 * - Processa e valida tentativas de registro
 * - Atualiza novos usuários no arquivo em caso de registros válidos
 */
class register_screen {
public:
  /**
  * @brief Construtor que inicializa a tela de registro
  * @param screen_w Largura da tela
  * @param screen_h Altura da tela
  * @param data_ref Referência ao objeto que manipula os arquivos
  * @param set Multiset com todos os jogadores atuais para atualizar em caso de novo usuário
  * @param key_s Efeito sonoro das caixas de texto
  * @param button_s Efeito sonoro dos botões
  */
  register_screen(int screen_w, int screen_h, registration &data_ref, std::multiset<player> &set, ALLEGRO_SAMPLE* key_s, ALLEGRO_SAMPLE* button_s);

  /**
  * @brief Trata eventos (mouse/teclado) e repassa para componentes
  * @param ev Evento tratado
  */
  void handle_event(const ALLEGRO_EVENT &ev);

  /**
  * @brief Desenha os componentes da tela
  * @param font Fonte utilizada
  */
  void draw(ALLEGRO_FONT *font);

  /**
  * @brief Indica se o registro foi concluído com sucesso (para voltar ao login)
  * @return Indica o estado do registro
  */
  bool registration_complete() const;

  /**
  * @brief Indica se deve voltar à tela de login
  * @return Booleano que indica o estado da volta
  */
  bool go_to_login_screen() const;

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

  /// Reseta campos e flags para nova exibição
  void reset();

private:
  /// @name Tamanho da tela
  /// @{
  int screen_width; 
  int screen_height;
  /// @}

  /// Referência ao objeto que manipula os arquivos
  registration &data;

  /// Multiset com todos os jogadores registrados
  std::multiset<player> &players;

  /// @name Campos de texto
  /// @{
  text_box username_box;
  text_box password_box;
  text_box confirm_box;
  /// @}
  
  /// @name Botões
  /// @{
  button confirm_button;
  button cancel_button;
  /// @}

  /// @name Vetores dos elementos de UI para manipulação de audio e testes
  /// @{
  std::vector<text_box*> text_boxes;
  std::vector<button*>  buttons;
  /// @}

  /// @name Flags internas
  /// @{
  bool reg_complete; ///< true após cadastro bem-sucedido
  bool go_to_login; ///< true se cancelou ou terminou
  bool password_mismatch; ///< true para exibir mensagem de erro de senhas diferentes
  bool empty_field; ///< true para exibir erro de campo vazio
  bool existing_user; ///< true para exibir mensagem de erro de usuário existente
  /// @}
};

#endif // REGISTER_SCREEN_HPP
