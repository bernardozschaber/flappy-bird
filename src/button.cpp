#include "button.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

button::button(int x, int y, int width, int height, const std::string &label, ALLEGRO_SAMPLE* sample_button)
    : ui_object(x, y, width, height), label(label), clicked(false), sample_button(sample_button) {}

void button::handle_event(const ALLEGRO_EVENT &ev) {
  if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
    int mx = ev.mouse.x;
    int my = ev.mouse.y;
    if (contains(mx, my)) {
      clicked = true;
      if (sample_button) {
        al_play_sample(sample_button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
      }
    }
  }
}

void button::draw(ALLEGRO_FONT *font) {
  // Desenha fundo do botão (cinza-escuro) e borda branca
  al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(50, 50, 50));
  al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255), 2);

  // Centraliza a label no botão
  int text_w = al_get_text_width(font, label.c_str());
  int text_h = al_get_font_line_height(font);
  int text_x = x + (width - text_w) / 2;
  int text_y = y + (height - text_h) / 2;
  al_draw_text(font, al_map_rgb(255, 255, 255), text_x, text_y, 0,
               label.c_str());
}

int button::get_x(){
  return x;
}

int button::get_y(){
  return y;
}
