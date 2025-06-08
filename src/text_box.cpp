#include "text_box.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

text_box::text_box(int x, int y, int width, int height, int max_length, ALLEGRO_SAMPLE* sample_key)
    : ui_object(x, y, width, height), text(""), is_active(false), masked(false),
      max_length(max_length), sample_key(sample_key) {}

void text_box::handle_event(const ALLEGRO_EVENT &ev) {
  // Só processa teclado se estiver ativo (focado)
  if (!is_active)
    return;

  if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
      if (!text.empty()) {
        text.pop_back();
        if (sample_key) {
          al_play_sample(sample_key, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
        }
      }
    } else {
      // Adiciona caractere imprimível (ASCII simples)
      if (ev.keyboard.unichar > 32 && ev.keyboard.unichar < 127) {
        if (static_cast<int>(text.size()) < max_length) {
          text.push_back(static_cast<char>(ev.keyboard.unichar));
          if (sample_key) {
            al_play_sample(sample_key, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
          }
        }
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

void text_box::set_mask(bool mask_enabled) { masked = mask_enabled; }
void text_box::set_active(bool active) { is_active = active; }
bool text_box::is_active_box() const { return is_active; }
std::string text_box::get_text() const { return text; }
void text_box::set_text(const std::string &t) { text = t; }
