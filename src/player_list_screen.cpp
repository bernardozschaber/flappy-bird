#include "player_list_screen.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

player_list_screen::player_list_screen(int screen_w, int screen_h, ALLEGRO_SAMPLE* button_s, ALLEGRO_BITMAP* crown, const std::multiset<player> &set, registration& data_ref):
      screen_width(screen_w), screen_height(screen_h), current_page(0),
      players_per_page(14), // 14 por página mantém boa visibilidade
      next_button(630, 525, 120, 40, "Próximo", button_s),
      back_button(50, 525, 120, 40, "Voltar", button_s),
      main_menu_button(340, 525, 120, 40, "Menu", button_s), go_to_menu(false), players(set), data(data_ref), crown(crown) {
      // Preenche o vetor para menu_audio e testes
      buttons = { &back_button, &next_button, &main_menu_button };   
}

void player_list_screen::handle_event(const ALLEGRO_EVENT &ev) {
  // Processa eventos do mouse apenas
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;
    
    int max_pages = (players.size() - 1) / players_per_page;

    // Processa o botão de passar de página se não estiver na última
    if (current_page < max_pages){
    next_button.handle_event(ev);
    if (next_button.was_clicked()){
      next_button.reset_clicked();
      current_page++;
      }
    }

    // Processa o botão de voltar página se não estiver na primeira
    if (current_page > 0) {
    back_button.handle_event(ev);
    if (back_button.was_clicked()) {
      back_button.reset_clicked();
      current_page--;
      }
    }

    // Botão de voltar ao menu sempre ativo
    main_menu_button.handle_event(ev);
    if (main_menu_button.was_clicked()) {
      main_menu_button.reset_clicked();
      go_to_menu = true;
    }
  }
  // ESC volta para o login
  if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) go_to_menu = true;
}

void player_list_screen::draw(ALLEGRO_FONT *font) {
  // Posições de referência inicial de linha e coluna
  int line_h = al_get_font_line_height(font);
  int start_y = 50;
  int col1_x = 100;
  int col2_x = screen_width/2 - 50;
  int col3_x = screen_width - 220;

  // Desenha cabeçalho
  al_draw_text(font, al_map_rgb(255,255,0), col1_x, start_y, 0, "USUÁRIO");
  al_draw_text(font, al_map_rgb(255,255,0), col2_x, start_y, 0, "RECORDE");
  al_draw_text(font, al_map_rgb(255,255,0), col3_x, start_y, 0, "PARTIDAS JOGADAS");

  // Recorde máximo 
  int max_score = data.get_max_score();

  auto it = players.begin(); // Iterator para percorrer o multiset
  std::advance(it, current_page * players_per_page); // Move o iterator para a página atual

  // Exibe até 14 jogadores
  // it define parada para última página e i define parada para páginas completas com 14 jogadores
  for (int i = 0; i < players_per_page && it != players.end(); ++i, ++it) {
        int y = start_y + (i+1) * (line_h + 5);
        const auto& p = *it;
        al_draw_text(font, al_map_rgb(255,255,255), col1_x, y, 0, p.username.c_str());
        // Indicador de coroa caso possua o recorde
        if (p.score == max_score && crown) {
            int tw = al_get_text_width(font, p.username.c_str());
            al_draw_scaled_bitmap(crown,0,0, al_get_bitmap_width(crown), al_get_bitmap_height(crown), col1_x + tw + 8, y + 2, 16, 16, 0);
        }     

        al_draw_text(font, al_map_rgb(255,255,255), col2_x, y, 0, std::to_string(p.score).c_str());
        al_draw_text(font, al_map_rgb(255,255,255), col3_x, y, 0, std::to_string(p.games).c_str());
    }

  // Botões na base
  // Desenha o botão de página anterior
  if (current_page > 0) {
      back_button.draw(font);
  } else {
      // Botão desativado se estiver na primeira página
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

  // Desenha o botão de próxima página
  int max_page = (players.size() - 1) / players_per_page;
  if (current_page < max_page) {
      next_button.draw(font);
  } else {
      // Botão desativado se estiver na última página
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

  // Desenha botão para voltar para o menu (sempre ativo)
  main_menu_button.draw(font);

  // Indicação de página no topo
  int total_pages = max_page + 1;
  std::string page_text = "Página " + std::to_string(current_page+1) + " / " + std::to_string(total_pages);
  int pw = al_get_text_width(font, page_text.c_str());
  al_draw_text(font, al_map_rgb(100,100,100), (screen_width - pw)/2, start_y - (2*(line_h)), 0, page_text.c_str());
}

bool player_list_screen::go_to_main_menu() const { return go_to_menu; }

const std::vector<button*>& player_list_screen::get_buttons() const { return buttons; }

void player_list_screen::reset() {
  current_page = 0;
  go_to_menu = false;
}
