#include "register_screen.hpp"
#include <allegro5/allegro_primitives.h>

register_screen::register_screen(int screen_w, int screen_h, registration &data_ref, std::multiset<player> &set, ALLEGRO_SAMPLE* key_s, ALLEGRO_SAMPLE* button_s):
      screen_width(screen_w), screen_height(screen_h),
      username_box(275, 200, 250, 40, 18, key_s), password_box(275, 270, 250, 40, 18, key_s), confirm_box(275, 340, 250, 40, 18, key_s),
      confirm_button(275, 400, 120, 40, "Confirmar", button_s), cancel_button(415, 400, 120, 40, "Cancelar", button_s),
      reg_complete(false), players(set), go_to_login(false), password_mismatch(false), existing_user(false), data(data_ref), empty_field(false) {
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
        empty_field = true;
        password_mismatch = false;
        existing_user = false; //evitar textos de erro se sobrepor
      } else if (senha != conf) {
        password_mismatch = true;
        empty_field = false;
        existing_user = false;
        username_box.set_text("");
        password_box.set_text("");
        confirm_box.set_text("");
      } else {
        std::string aux = data.get_stats(nome);
        if (aux != "") {
          existing_user = true;
          empty_field = false;
          password_mismatch = false; //evitar textos de erro se sobrepor
          username_box.set_text("");
          password_box.set_text("");
          confirm_box.set_text("");
        } else {
          data.new_user(nome, senha, 0, 0);
          players.clear();
          players = data.get_all();
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

  // Atalhos de Enter e TAB
  if (ev.type == ALLEGRO_EVENT_KEY_UP) {
    switch (ev.keyboard.keycode) {
      case ALLEGRO_KEY_TAB:
          // ciclo de foco: user -> pass -> confirm -> user
          if (username_box.is_active_box()) {
              username_box.set_active(false);
              password_box.set_active(true);
          } else if (password_box.is_active_box()) {
              password_box.set_active(false);
              confirm_box.set_active(true);
          } else {
              confirm_box.set_active(false);
              username_box.set_active(true);
          }
          break;
      case ALLEGRO_KEY_ENTER:
          if (username_box.is_active_box() || password_box.is_active_box() || confirm_box.is_active_box()) {
            confirm_button.reset_clicked();
            std::string nome = username_box.get_text();
            std::string senha = password_box.get_text();
            std::string conf = confirm_box.get_text();

            if (nome.empty() || senha.empty() || conf.empty()) {
              // Não permitir registro com campos vazios
              empty_field = true;
              password_mismatch = false;
              existing_user = false; //evitar textos de erro se sobrepor
            } else if (senha != conf) {
              password_mismatch = true;
              empty_field = false;
              existing_user = false;
              username_box.set_text("");
              password_box.set_text("");
              confirm_box.set_text("");
            } else {
              std::string aux = data.get_stats(nome);
              if (aux != "") {
                existing_user = true;
                empty_field = false;
                password_mismatch = false; //evitar textos de erro se sobrepor
                username_box.set_text("");
                password_box.set_text("");
                confirm_box.set_text("");
              } else {
                data.new_user(nome, senha, 0, 0);
                players.clear();
                players = data.get_all();
                reg_complete = true;
              }
            }
          } 
          break;
      case ALLEGRO_KEY_ESCAPE:
          go_to_login = true;  // volta ao login
          break;
      default: break;
    }
  } 

  // Evento de teclado: apenas para text_box que estiver ativa
  if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
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
  al_draw_text(font, al_map_rgb(255, 255, 255), 275, 170, 0, "Usuário:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 275, 240, 0, "Senha:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 275, 310, 0,
               "Confirmar Senha:");
  std::string max_char_text = "(Máx. 18 caracteres)";
  int max_text_w = al_get_text_width(font, max_char_text.c_str());
  int x_max = (screen_width - max_text_w) / 2;
  al_draw_text(font, al_map_rgb(128, 128, 128), x_max, 520, 0, max_char_text.c_str());

  // Desenha os text_box e botões
  username_box.draw(font);
  password_box.draw(font);
  confirm_box.draw(font);
  confirm_button.draw(font);
  cancel_button.draw(font);

  // Mensagens de erro de registro
  if (password_mismatch) {
    std::string msg = "As senhas diferem!";
    int text_w = al_get_text_width(font, msg.c_str());
    int x = (screen_width - text_w) / 2;
    int y = 450;
    al_draw_text(font, al_map_rgb(252, 23, 35), x, y, 0, msg.c_str());
  }
  if (existing_user) {
    std::string msg = "O usuário já existe!";
    int text_w = al_get_text_width(font, msg.c_str());
    int x = (screen_width - text_w) / 2;
    int y = 450;
    al_draw_text(font, al_map_rgb(252, 23, 35), x, y, 0, msg.c_str());
  }
  if (empty_field) {
    std::string msg = "Há campos vazios!";
    int text_w = al_get_text_width(font, msg.c_str());
    int x = (screen_width - text_w) / 2;
    int y = 450;
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
  password_mismatch = false;
  existing_user = false;
  empty_field = false;
}
