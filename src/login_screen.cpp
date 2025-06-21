#include "login_screen.hpp"

login_screen::login_screen(int screen_w, int screen_h, registration &data_ref, ALLEGRO_SAMPLE* key_s, ALLEGRO_SAMPLE* button_s)
    : screen_width(screen_w), screen_height(screen_h),
      username_box(275, 200, 250, 40, 18, key_s), password_box(275, 270, 250, 40, 18, key_s),
      login_button(270, 340, 120, 40, "Login", button_s),
      register_button(410, 340, 120, 40, "Registrar", button_s),
      view_players_button(210, 400, 180, 40, "Ver Jogadores", button_s),
      remove_user_button(410, 400, 180, 40, "Remover Usuário", button_s),
      valid_login(true), go_to_list(false), go_to_register(false), go_to_remove(false), done(false), data(data_ref), empty_field(false) {
  password_box.set_mask(true);
  username_box.set_active(false);
  password_box.set_active(false);
  // Preenche os vetores para menu_audio e testes:
  text_boxes = { &username_box, &password_box };
  buttons = {&login_button,&register_button,&view_players_button,&remove_user_button};
}

void login_screen::handle_event(const ALLEGRO_EVENT &ev) {
  // Se for clique do mouse
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;

    // Define foco em username_box ou password_box
    bool foco_user = username_box.contains(mx, my);
    bool foco_pass = password_box.contains(mx, my);
    username_box.set_active(foco_user);
    password_box.set_active(foco_pass);

    // Se clicar fora dos dois, desativa ambos
    if (!foco_user && !foco_pass) {
      username_box.set_active(false);
      password_box.set_active(false);
    }

    // Encaminha clique para botões
    login_button.handle_event(ev);
    register_button.handle_event(ev);
    view_players_button.handle_event(ev);
    remove_user_button.handle_event(ev);

    // Ação do botão de login
    if (login_button.was_clicked()) {
      login_button.reset_clicked();
      std::string nome = username_box.get_text();
      std::string senha = password_box.get_text();
      if (nome == "" || senha == ""){
        empty_field = true;
        valid_login = true; // Evita sobrepor mensagens de erro
      } else {
      player aux = data.get_player(nome);
      empty_field = false; // Evita sobrepor mensagens de erro
      if (aux.username == "") {
        // Usuário não existe
        valid_login = false;
        username_box.set_text("");
        password_box.set_text("");
      } else {
        if (aux.get_password() != senha) {
          // Senha incorreta
          valid_login = false;
          username_box.set_text("");
          password_box.set_text("");
        } else {
          // Login realizado com sucesso
          done = true;
          logged_user = aux;
        }
      }
    }
  }

    // Botões para trocar de telas
    if (register_button.was_clicked()) {
      register_button.reset_clicked();
      go_to_register = true;
    }
    if (view_players_button.was_clicked()) {
      view_players_button.reset_clicked();
      go_to_list = true;
    }
    if (remove_user_button.was_clicked()) {
      remove_user_button.reset_clicked();
      go_to_remove = true;
    }
  }

  // Atalhos de ENTER e TAB
  if (ev.type == ALLEGRO_EVENT_KEY_UP) {
    switch (ev.keyboard.keycode) {
    case ALLEGRO_KEY_TAB:
      // alterna foco entre username_box <-> password_box
      if (username_box.is_active_box()) {
          username_box.set_active(false);
          password_box.set_active(true);
      } else {
          password_box.set_active(false);
          username_box.set_active(true);
      }
      break;
    case ALLEGRO_KEY_ENTER: // Equivalente ao botão de confirmar
      if (username_box.is_active_box() || password_box.is_active_box()) {
          login_button.reset_clicked();
          std::string nome = username_box.get_text();
          std::string senha = password_box.get_text();
          if (nome == "" || senha == ""){
            empty_field = true;
            valid_login = true; // Evita sobrepor mensagens de erro
          } else {
          player aux = data.get_player(nome);
          empty_field = false; // Evita sobrepor mensagens de erro
          if (aux.username == "") {
            // Usuário não existe
            valid_login = false;
            username_box.set_text("");
            password_box.set_text("");
          } else {
            if (aux.get_password() != senha) {
              // Senha incorreta
              valid_login = false;
              username_box.set_text("");
              password_box.set_text("");
            } else {
              // Login realizado com sucesso
              done = true;
              logged_user = aux;
            }
          }
        }
      }   
      break;
    default: break;
  }
}

  // Se for evento de teclado, direciona apenas para caixa de texto ativa
  if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (username_box.is_active_box()) {
      username_box.handle_event(ev);
    } else if (password_box.is_active_box()) {
      password_box.handle_event(ev);
    }
  }
}

void login_screen::draw(ALLEGRO_FONT *font) {
  // Desenha título das caixas de texto
  al_draw_text(font, al_map_rgb(255, 255, 255), 275, 170, 0, "Usuário:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 275, 240, 0, "Senha:");

  // Desenha botões e caixas de texto
  username_box.draw(font);
  password_box.draw(font);
  login_button.draw(font);
  register_button.draw(font);
  view_players_button.draw(font);
  remove_user_button.draw(font);

  // Desenha mensagens de erro de login
  if (empty_field) {
    std::string erro = "Há campos vazios!";
    int erro_w = al_get_text_width(font, erro.c_str());
    int x_erro = 275;
    int y_erro = 310;
    al_draw_text(font, al_map_rgb(252, 23, 35), x_erro, y_erro, 0,
                 erro.c_str());
  }
  if (!valid_login) {
    std::string erro = "usuário e/ou senha inválidos";
    int erro_w = al_get_text_width(font, erro.c_str());
    int x_erro = 275;
    int y_erro = 310;
    al_draw_text(font, al_map_rgb(252, 23, 35), x_erro, y_erro, 0,
                 erro.c_str());
  }

  // Desenha o recorde no topo
  data.update_champion();
  int top_score = data.get_max_score();
  std::string texto = "Recorde: " + std::to_string(top_score);
  int text_w = al_get_text_width(font, texto.c_str());
  int x = screen_width - text_w - 45;
  int y = 40;
  al_draw_text(font, al_map_rgb(255, 255, 0), x, y, 0, texto.c_str());
}

bool login_screen::go_to_player_list() const { return go_to_list; }

bool login_screen::go_to_register_screen() const { return go_to_register; }

bool login_screen::go_to_remove_screen() const { return go_to_remove; }

bool login_screen::login_done() const { return done; }

player login_screen::get_logged_user() { return logged_user; }

const std::vector<text_box*>& login_screen::get_text_boxes() const { return text_boxes; }
const std::vector<button*>&  login_screen::get_buttons() const { return buttons; }

void login_screen::reset() {
  username_box.set_text("");
  password_box.set_text("");
  username_box.set_active(false);
  password_box.set_active(false);
  go_to_list = false;
  go_to_register = false;
  go_to_remove = false;
  valid_login = true;
  done = false;
  empty_field = false;
}
