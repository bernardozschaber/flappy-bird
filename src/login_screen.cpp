#include "login_screen.hpp"
#include <sstream>

login_screen::login_screen(int screen_w, int screen_h, registration &data_ref)
    : screen_width(screen_w), screen_height(screen_h),
      username_box(300, 200, 200, 30, 20), password_box(300, 250, 200, 30, 20),
      login_button(300, 300, 100, 30, "Login"),
      register_button(410, 300, 100, 30, "Registrar"),
      view_players_button(300, 350, 150, 30, "Ver Jogadores"),
      valid_login(true), go_to_list(false), go_to_register(false),
      done(false), data(data_ref) {
  password_box.set_mask(true);
  username_box.set_active(false);
  password_box.set_active(false);
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

    // Ações de cada botão
    if (login_button.was_clicked()) {
      login_button.reset_clicked();
      std::string nome = username_box.get_text();
      std::string senha = password_box.get_text();

      std::string aux = data.get_stats(nome);

      if (aux == "") {
        valid_login = false;
        username_box.set_text("");
        password_box.set_text("");
      } else {
        std::istringstream iss(aux);
        int aux_score;
        std::string aux_nome, aux_senha;
        iss >> aux_score;
        iss >> aux_nome;
        iss >> aux_senha;

        if (aux_senha != senha) {
          valid_login = false;
          username_box.set_text("");
          password_box.set_text("");
        } else {
          done = true;
          logged_user = aux_nome;
        }
      }
    }

    if (register_button.was_clicked()) {
      register_button.reset_clicked();
      go_to_register = true;
    }
    if (view_players_button.was_clicked()) {
      view_players_button.reset_clicked();
      go_to_list = true;
    }
  }
  // Se for evento de teclado
  else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (username_box.is_active_box()) {
      username_box.handle_event(ev);
    } else if (password_box.is_active_box()) {
      password_box.handle_event(ev);
    }
  }
}

void login_screen::draw(ALLEGRO_FONT *font) {
  al_draw_text(font, al_map_rgb(255, 255, 255), 300, 180, 0, "Usuário:");
  al_draw_text(font, al_map_rgb(255, 255, 255), 300, 230, 0, "Senha:");

  username_box.draw(font);
  password_box.draw(font);
  login_button.draw(font);
  register_button.draw(font);
  view_players_button.draw(font);

  if (!valid_login) {
    std::string erro = "usuário e/ou senha inválidos";
    int erro_w = al_get_text_width(font, erro.c_str());
    int x_erro = 300;
    int y_erro = 270;
    al_draw_text(font, al_map_rgb(252, 23, 35), x_erro, y_erro, 0,
                 erro.c_str());
  }

  // Desenha nome e recorde do maior pontuador no canto superior direito
  std::string top = data.get_max_user();
  int top_score = data.get_max_score();
  std::string texto = "Campeão: " + top + " - " + std::to_string(top_score);
  int text_w = al_get_text_width(font, texto.c_str());
  int x = screen_width - text_w - 20;
  int y = 20;
  al_draw_text(font, al_map_rgb(255, 255, 0), x, y, 0, texto.c_str());
}

bool login_screen::go_to_player_list() const { return go_to_list; }

bool login_screen::go_to_register_screen() const { return go_to_register; }

bool login_screen::login_done() const { return done; }

std::string login_screen::get_logged_user() { return logged_user; }

void login_screen::reset() {
  username_box.set_text("");
  password_box.set_text("");
  username_box.set_active(false);
  password_box.set_active(false);
  go_to_list = false;
  go_to_register = false;
  valid_login = true;
  done = false;
}
