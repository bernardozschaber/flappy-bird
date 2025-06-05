#include "player_list_screen.hpp"
#include <allegro5/allegro_font.h>

player_list_screen::player_list_screen(int screen_w, int screen_h,
                                       std::string file_name)
    : screen_width(screen_w), screen_height(screen_h), current_page(0),
      players_per_page(15), // 15 por página mantém boa visibilidade
      next_button(650, 550, 100, 30, "Próximo"),
      back_button(50, 550, 100, 30, "Voltar"),
      main_menu_button(350, 550, 100, 30, "Menu"), go_to_menu(false),
      data(file_name) {
  players = data.get_all();
}

void player_list_screen::handle_event(const ALLEGRO_EVENT &ev) {
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;

    next_button.handle_event(ev);
    back_button.handle_event(ev);
    main_menu_button.handle_event(ev);

    if (back_button.was_clicked()) {
      back_button.reset_clicked();
      if (current_page > 0) {
        current_page--;
      }
    }
    if (next_button.was_clicked()) {
      next_button.reset_clicked();
      int max_pages = (players.size() - 1) / players_per_page;
      if (current_page < max_pages) {
        current_page++;
      }
    }
    if (main_menu_button.was_clicked()) {
      main_menu_button.reset_clicked();
      go_to_menu = true;
    }
  }
}

void player_list_screen::draw(ALLEGRO_FONT *font) {
  int line_h = al_get_font_line_height(font);
  int start_y = 50;
  int start_x = 100;

  for (int i = 0; i < players_per_page; ++i) {
    int idx = current_page * players_per_page + i;
    if (idx >= static_cast<int>(players.size()))
      break;
    player p = players[idx];
    std::string line = p.username + " - " + std::to_string(p.score);
    int y = start_y + i * (line_h + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), start_x, y, 0, line.c_str());
  }

  back_button.draw(font);
  next_button.draw(font);
  main_menu_button.draw(font);

  // Exibe indicador de página
  int total_pages = (players.size() + players_per_page - 1) / players_per_page;
  if (total_pages == 0)
    total_pages = 1;
  std::string page_text = "Página " + std::to_string(current_page + 1) + " / " +
                          std::to_string(total_pages);
  int text_w = al_get_text_width(font, page_text.c_str());
  al_draw_text(font, al_map_rgb(200, 200, 200), (screen_width - text_w) / 2, 20,
               0, page_text.c_str());
}

void player_list_screen::reset() {
  current_page = 0;
  go_to_menu = false;
}
