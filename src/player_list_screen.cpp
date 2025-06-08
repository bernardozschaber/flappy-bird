#include "player_list_screen.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

player_list_screen::player_list_screen(int screen_w, int screen_h, ALLEGRO_SAMPLE* button_s, const std::vector<player> &vect)
    : screen_width(screen_w), screen_height(screen_h), current_page(0),
      players_per_page(14), // 14 por página mantém boa visibilidade
      next_button(650, 540, 120, 40, "Próximo", button_s),
      back_button(50, 540, 120, 40, "Voltar", button_s),
      main_menu_button(340, 540, 120, 40, "Menu", button_s), go_to_menu(false), players(vect) {}

void player_list_screen::handle_event(const ALLEGRO_EVENT &ev) {
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;
    
    int max_pages = (players.size() - 1) / players_per_page;
    if (current_page < max_pages){
    next_button.handle_event(ev);
    if (next_button.was_clicked()){
      next_button.reset_clicked();
      current_page++;
      }
    }

    if (current_page > 0) {
    back_button.handle_event(ev);
    if (back_button.was_clicked()) {
      back_button.reset_clicked();
      current_page--;
      }
    }

    main_menu_button.handle_event(ev);
    if (main_menu_button.was_clicked()) {
      main_menu_button.reset_clicked();
      go_to_menu = true;
    }
  }
}

void player_list_screen::draw(ALLEGRO_FONT *font) {

  int line_h = al_get_font_line_height(font);
  int start_y = 50;
  int col1_x = 100;
  int col2_x = screen_width/2 - 50;
  int col3_x = screen_width - 200;

  // Cabeçalho
  al_draw_text(font, al_map_rgb(200,200,0), col1_x, start_y, 0, "USUÁRIO");
  al_draw_text(font, al_map_rgb(200,200,0), col2_x, start_y, 0, "RECORDE");
  al_draw_text(font, al_map_rgb(200,200,0), col3_x, start_y, 0, "PARTIDAS JOGADAS");

  // Linhas de dados (14 por página)
  for (int i = 0; i < players_per_page; ++i) {
    int idx = current_page * players_per_page + i;
      if (idx >= (int)players.size()) break; //Condição de parada na última página
      const auto& p = players[idx];
      int y = start_y + (i+1) * (line_h + 5);
      al_draw_text(font, al_map_rgb(255,255,255), col1_x, y, 0, p.username.c_str());
      al_draw_text(font, al_map_rgb(255,255,255), col2_x, y, 0, std::to_string(p.score).c_str());
      al_draw_text(font, al_map_rgb(255,255,255), col3_x, y, 0, std::to_string(p.games).c_str());
  }

  // Botões na base
  // Back
  if (current_page > 0) {
      back_button.draw(font);
  } else {
      // desenha desativado
      al_draw_filled_rectangle(back_button.get_x(), back_button.get_y(),
                                back_button.get_x() + back_button.get_width(),
                                back_button.get_y() + back_button.get_height(),
                                al_map_rgb(80,80,80));
      al_draw_rectangle(back_button.get_x(), back_button.get_y(),
                        back_button.get_x() + back_button.get_width(),
                        back_button.get_y() + back_button.get_height(),
                        al_map_rgb(150,150,150), 2);
      int tw = al_get_text_width(font, "Voltar");
      al_draw_text(font, al_map_rgb(150,150,150),
                    back_button.get_x() + (back_button.get_width() - tw)/2,
                    back_button.get_y() + (back_button.get_height() - line_h)/2,
                    0, "Voltar");
  }

  // Next
  int max_page = (players.size() - 1) / players_per_page;
  if (current_page < max_page) {
      next_button.draw(font);
  } else {
      al_draw_filled_rectangle(next_button.get_x(), next_button.get_y(),
                                next_button.get_x() + next_button.get_width(),
                                next_button.get_y() + next_button.get_height(),
                                al_map_rgb(80,80,80));
      al_draw_rectangle(next_button.get_x(), next_button.get_y(),
                        next_button.get_x() + next_button.get_width(),
                        next_button.get_y() + next_button.get_height(),
                        al_map_rgb(150,150,150), 2);
      int tw = al_get_text_width(font, "Próximo");
      al_draw_text(font, al_map_rgb(150,150,150),
                    next_button.get_x() + (next_button.get_width() - tw)/2,
                    next_button.get_y() + (next_button.get_height() - line_h)/2,
                    0, "Próximo");
  }

  // Menu (sempre ativo)
  main_menu_button.draw(font);

  // Indicação de página no topo
  int total_pages = max_page + 1;
  std::string page_text = "Página " + std::to_string(current_page+1) + " / " + std::to_string(total_pages);
  int pw = al_get_text_width(font, page_text.c_str());
  al_draw_text(font, al_map_rgb(128,128,128), (screen_width - pw)/2, start_y - (line_h+5), 0, page_text.c_str());
}

bool player_list_screen::go_to_main_menu() const { return go_to_menu; }

void player_list_screen::reset() {
  current_page = 0;
  go_to_menu = false;
}
