#include "moving_button.hpp"

moving_button::moving_button(float x, float y, ALLEGRO_BITMAP* Bitmap) 
: sprite(Bitmap), ui_object(x,y,al_get_bitmap_width(Bitmap),al_get_bitmap_height(Bitmap)){};

void moving_button::set_velocity(float vx, float vy) {
    this->vel_x = vx;
    this->vel_y = vy;
}

void moving_button::set_acceleration(float ax, float ay) {
    this->acel_x = ax;
    this->acel_y = ay;
}

bool moving_button::contains_click(float mouse_x, float mouse_y) {
    return contains(mouse_x, mouse_y);
}

void moving_button::set_bitmap(ALLEGRO_BITMAP* bitmap) {
        this->sprite = bitmap;
        this->width = al_get_bitmap_width(bitmap);
        this->height = al_get_bitmap_height(bitmap);
}

void moving_button::draw() {
    if (is_being_pressed) {
        al_draw_scaled_rotated_bitmap(this->sprite,width/2,height/2,x,y,0.8,0.8,0,0);
    } else {
        al_draw_scaled_rotated_bitmap(this->sprite,width/2,height/2,x,y,1,1,0,0);
    }
}

