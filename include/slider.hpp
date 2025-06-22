#ifndef SLIDER_HPP
#define SLIDER_HPP
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "ui_object.hpp"

class slider: public ui_object{
    private:
        ALLEGRO_BITMAP* back[2];
        ALLEGRO_BITMAP* indicator[2];
        bool is_pressed;
        float pos_indicator;
        float variation;
        bool show_number;
        float disp_h;
        float disp_v;
        float scale;
        float min_value;
        float max_value;
        float value;
        bool is_int;

    public:
        slider(ALLEGRO_BITMAP** back_sprite, ALLEGRO_BITMAP** indicator_sprite, float x, float y, float variation_, bool show_number_, float disp_h_, float disp_v_, float scale_, float min_value_, float max_value_, float value_, bool is_int_);
        void draw();
        void update(bool mouse_is_down, bool mouse_just_released, int x_at_down, int y_at_down, int x_now);
        void set_pressed(bool is_pressed);
        bool cointains_indicator(float x, float y);
        bool cointains_back(float x, float y);
        void set_bitmap_back(ALLEGRO_BITMAP* new_back_bitmap);
        void set_bitmap_indicator(ALLEGRO_BITMAP* new_indicator_bitmap);
        float get_value();
        void handle_event(const ALLEGRO_EVENT &ev)override {return;}
        void draw(ALLEGRO_FONT *font)override{return;}

};
#endif