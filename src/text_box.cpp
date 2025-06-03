#include "text_box.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

text_box::text_box(int x, int y, int width, int height)
    : ui_object(x, y, width, height), text(""), is_active(false),
      masked(false) {}

void text_box::handle_event(const ALLEGRO_EVENT &ev) {
  // Só processa teclado se estiver ativo (focado)
  if (!is_active)
    return;

  if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
      if (!text.empty()) {
        text.pop_back();
      }
    } else {
      // Adiciona caractere imprimível (ASCII simples)
      if (ev.keyboard.unichar > 0 && ev.keyboard.unichar < 128) {
        text.push_back(static_cast<char>(ev.keyboard.unichar));
      }
    }
  }
}

void text_box::draw(ALLEGRO_FONT *font) {
  // Desenha retângulo de base (fundo escuro) + borda branca
  al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(30, 30, 30));
  al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255), 2);

  // Prepara texto a exibir (mascarado ou não)
  std::string display_text = text;
  if (masked) {
    display_text = std::string(text.size(), '*');
  }

  // Centraliza o texto dentro da caixa
  int text_w = al_get_text_width(font, display_text.c_str());
  int text_h = al_get_font_line_height(font);
  int text_x = x + (width - text_w) / 2;
  int text_y = y + (height - text_h) / 2;
  al_draw_text(font, al_map_rgb(255, 255, 255), text_x, text_y, 0,
               display_text.c_str());

  // Se ativo, desenha contorno em amarelo para indicar foco
  if (is_active) {
    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 0), 2);
  }
}
