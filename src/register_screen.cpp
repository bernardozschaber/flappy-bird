#include "register_screen.hpp"
#include <allegro5/allegro_primitives.h>

register_screen::register_screen(int screen_w, int screen_h,
                                 registration &data_ref)
    : screen_width(screen_w), screen_height(screen_h),
      username_box(300, 180, 200, 30, 20), password_box(300, 230, 200, 30, 20),
      confirm_box(300, 280, 200, 30, 20),
      confirm_button(300, 330, 100, 30, "Confirmar"),
      cancel_button(410, 330, 100, 30, "Cancelar"), reg_complete(false),
      go_to_login(false), senha_mismatch(false), data(data_ref) {
  password_box.set_mask(true);
  confirm_box.set_mask(true);
  username_box.set_active(false);
  password_box.set_active(false);
  confirm_box.set_active(false);
}

void register_screen::handle_event(const ALLEGRO_EVENT &ev) {
  // Clique do mouse: para definir foco ou ativar botões
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;

    // Define foco nos três text_box
    bool foco_user = username_box.contains(mx, my);
    bool foco_pass = password_box.contains(mx, my);
    bool foco_conf = confirm_box.contains(mx, my);

    username_box.set_active(foco_user);
    password_box.set_active(foco_pass);
    confirm_box.set_active(foco_conf);

    // Se clicou fora de todos, remove o foco
    if (!foco_user && !foco_pass && !foco_conf) {
      username_box.set_active(false);
      password_box.set_active(false);
      confirm_box.set_active(false);
    }

    // Encaminha evento de clique para botões
    confirm_button.handle_event(ev);
    cancel_button.handle_event(ev);

    // Ação do botão "Confirmar"
    if (confirm_button.was_clicked()) {
      confirm_button.reset_clicked();
      std::string nome = username_box.get_text();
      std::string senha = password_box.get_text();
      std::string conf = confirm_box.get_text();

      if (nome.empty() || senha.empty() || conf.empty()) {
        // Não permitir registro com campos vazios
        senha_mismatch = true;
      } else if (senha != conf) {
        // Senhas diferentes: erro
        senha_mismatch = true;
      } else {
        std::string aux = data.get_stats(nome);
        if (aux != "") {
          existing_user = true;
        } else {
          data.new_user(nome, senha, 0, 0);
          reg_complete = true;
        }
      }
    }

    // Ação do botão "Cancelar" → volta ao login
    if (cancel_button.was_clicked()) {
      cancel_button.reset_clicked();
      go_to_login = true;
    }
  }
  // Evento de teclado: apenas para text_box que estiver ativa
  else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (username_box.is_active_box()) {
      username_box.handle_event(ev);
    } else if (password_box.is_active_box()) {
      password_box.handle_event(ev);
    } else if (confirm_box.is_active_box()) {
      confirm_box.handle_event(ev);
    }
  }
}

void register_screen::draw(ALLEGRO_FONT *font) {
  // Desenha rótulos fixos acima de cada campo
  al_draw_text(font, al_map_rgb(255, 255, 255), 300, 160, 0, "Usuario:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 300, 210, 0, "Senha:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 300, 260, 0,
               "Confirmar Senha:");
  al_draw_text(font, al_map_rgb(128, 128, 128), 300, 285, 0,
               "(Máx. 20 caracteres)");

  // Desenha os text_box e botões
  username_box.draw(font);
  password_box.draw(font);
  confirm_box.draw(font);
  confirm_button.draw(font);
  cancel_button.draw(font);

  // Se houve erro de confirmação de senha ou campo vazio, exibe mensagem
  if (senha_mismatch) {
    std::string msg = "Senhas diferem ou campos vazios!";
    int text_w = al_get_text_width(font, msg.c_str());
    int x = (screen_width - text_w) / 2;
    int y = 380;
    al_draw_text(font, al_map_rgb(252, 23, 35), x, y, 0, msg.c_str());
  }
  if (existing_user) {
    std::string msg = "O usuário já existe!";
    int text_w = al_get_text_width(font, msg.c_str());
    int x = (screen_width - text_w) / 2;
    int y = 380;
    al_draw_text(font, al_map_rgb(252, 23, 35), x, y, 0, msg.c_str());
  }
}

void register_screen::reset() {
  username_box.set_text("");
  password_box.set_text("");
  confirm_box.set_text("");
  username_box.set_active(false);
  password_box.set_active(false);
  confirm_box.set_active(false);
  reg_complete = false;
  go_to_login = false;
  senha_mismatch = false;
  existing_user = false;
}
