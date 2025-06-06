#ifndef REGISTER_SCREEN_HPP
#define REGISTER_SCREEN_HPP

#include "button.hpp"
#include "registration.hpp"
#include "text_box.hpp"
#include <allegro5/allegro_font.h>

class register_screen {
public:
  register_screen(int screen_w, int screen_h, registration &data_ref);

  // Trata eventos (mouse/teclado) e repassa para componentes
  void handle_event(const ALLEGRO_EVENT &ev);

  // Desenha todos os componentes na tela (incluindo indicação de erro)
  void draw(ALLEGRO_FONT *font);

  // Indica se o registro foi concluído com sucesso (para voltar ao login)
  bool registration_complete() const { return reg_complete; }

  // Indica se o usuário clicou em "Cancelar" para voltar ao login
  bool go_to_login_screen() const { return go_to_login; }

  // Reseta campos e flags para nova exibição
  void reset();

private:
  int screen_width, screen_height;

  registration &data;

  // Campos de texto
  text_box username_box;
  text_box password_box;
  text_box confirm_box;

  // Botões
  button confirm_button;
  button cancel_button;

  // Flags internas
  bool reg_complete;      // true após cadastro bem-sucedido
  bool go_to_login;       // true se cancelou ou terminou
  bool password_mismatch; // true para exibir mensagem de erro de senhas
                          // diferentes
  bool existing_user; // true para exibir mensagem de erro de usuário existente
};

#endif // REGISTER_SCREEN_HPP
