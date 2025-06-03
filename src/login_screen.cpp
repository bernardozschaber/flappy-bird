#include "login_screen.hpp"

login_screen::login_screen(int screen_w, int screen_h)
    : screen_width(screen_w), screen_height(screen_h),
      username_box(300, 200, 200, 30), password_box(300, 250, 200, 30),
      login_button(300, 300, 100, 30, "Login"),
      register_button(410, 300, 100, 30, "Registrar"),
      view_players_button(300, 350, 150, 30, "Ver Jogadores"),
      go_to_list(false) {
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
      // if (registration::verifica_login(nome, senha)) {
      //  Login válido (aqui você poderia seguir para a próxima fase do jogo)
      //} else {
      // Login inválido
      //}
    }
    if (register_button.was_clicked()) {
      register_button.reset_clicked();
      std::string nome = username_box.get_text();
      std::string senha = password_box.get_text();
      // registration::registra_jogador(nome, senha);
      //  Jogador registrado
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
  username_box.draw(font);
  password_box.draw(font);
  login_button.draw(font);
  register_button.draw(font);
  view_players_button.draw(font);

  // Desenha nome e recorde do maior pontuador no canto superior direito
  // jogador top = registration::get_maior_pontuador();
  // std::string texto = top.nome + " - " + std::to_string(top.recorde);
  // int text_w = al_get_text_width(font, texto.c_str());
  // int x = screen_width - text_w - 20;
  // int y = 20;
  // al_draw_text(font, al_map_rgb(255, 255, 0), x, y, 0, texto.c_str());
}

void login_screen::reset() {
  username_box.set_text("");
  password_box.set_text("");
  username_box.set_active(false);
  password_box.set_active(false);
  go_to_list = false;
}
