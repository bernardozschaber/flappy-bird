#include "menu_audio.hpp"
#include <allegro5/allegro_primitives.h>

menu_audio::menu_audio(ALLEGRO_BITMAP* b_on,ALLEGRO_BITMAP* b_off,ALLEGRO_BITMAP* b_on_pr,ALLEGRO_BITMAP* b_off_pr,ALLEGRO_SAMPLE* key_s,ALLEGRO_SAMPLE* click_s,int x, int y, int w, int h):
  x(x), y(y), width(w), height(h),
  bmp_on(b_on), bmp_off(b_off),
  bmp_on_pr(b_on_pr), bmp_off_pr(b_off_pr),
  key_sample(key_s), click_sample(click_s),
  muted(false), pressed(false) {}

void menu_audio::set_sources(const std::vector<text_box*>& tboxes,const std::vector<button*>& btns) {
    text_boxes = tboxes;
    buttons = btns;
    update_sources();
}

void menu_audio::set_position(int nx, int ny) {
    x = nx; y = ny;
}

void menu_audio::update_sources() {
    // define ou retira os samples conforme muted
    for (auto* tb : text_boxes) {
        tb->set_sample(muted ? nullptr : key_sample);
    }
    for (auto* btn: buttons) {
        btn->set_sample(muted ? nullptr : click_sample);
    }
}

void menu_audio::handle_event(const ALLEGRO_EVENT& ev) {
    // Processa cliques do mouse
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
        if (ev.mouse.x >= x && ev.mouse.x < x + width && ev.mouse.y >= y && ev.mouse.y < y + height) {
            pressed = true;
        }
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == 1) {
        bool over = (ev.mouse.x >= x && ev.mouse.x < x + width && ev.mouse.y >= y && ev.mouse.y < y + height);
        if (pressed && over) {
            muted = !muted;
            update_sources();
        }
        pressed = false;
    }
}

void menu_audio::draw() {
    // Define qual bitmap a ser impresso baseado em estar pressionado/mutado
    ALLEGRO_BITMAP* bmp = muted ? (pressed ? bmp_off_pr : bmp_off) : (pressed ? bmp_on_pr  : bmp_on);
    al_draw_scaled_bitmap(bmp,0,0,al_get_bitmap_width(bmp), al_get_bitmap_height(bmp),x, y,width, height,0);
}
