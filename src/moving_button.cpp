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

float moving_button::get_velocity_y(){
    return vel_y;
}

float moving_button::get_velocity_x(){
    return vel_x;
}

bool moving_button::contains_click(float mouse_x, float mouse_y) {
    bool is_within_x = (mouse_x >= this->x - this->width/2) && (mouse_x <= this->x + this->width/2);
    bool is_within_y = (mouse_y >= this->y - this->height/2) && (mouse_y <= this->y + this->height/2);
    return is_within_x && is_within_y;
}

void moving_button::set_bitmap(ALLEGRO_BITMAP* bitmap) {
        this->sprite = bitmap;
        this->width = al_get_bitmap_width(bitmap);
        this->height = al_get_bitmap_height(bitmap);
}

void moving_button::draw() {
    // al_draw_scaled_rotated_bitmap(this->sprite,width/2,height/2,x,y,0.8,0.8,0,0);
    al_draw_tinted_scaled_rotated_bitmap(this->sprite, al_map_rgba_f(1, 1, 1, transparacy), width/2, height/2, x, y, 1, 1, 0, 0);
}

void moving_button::draw(float scale) {
    // al_draw_scaled_rotated_bitmap(this->sprite,width/2,height/2,x,y,0.8,0.8,0,0);
    al_draw_tinted_scaled_rotated_bitmap(this->sprite, al_map_rgba_f(1, 1, 1, transparacy), width/2, height/2, x, y, scale, scale, 0, 0);
} 

bool moving_button::is_pressed() {
    return this->is_being_pressed;
}

void moving_button::Update(){
    this->x+=this->vel_x;
    this->y+=this->vel_y;
    this->vel_x+=acel_x;
    this->vel_y+=acel_y;
}

void moving_button::set_transparacy(float trns) {
    this->transparacy=trns;
}

void moving_button::set_pressed(bool pressed) {
    this->is_being_pressed = pressed;
}

float moving_button::get_acel(){
    return acel_y;
};

void moving_button::handle_event(const ALLEGRO_EVENT &ev) {
    return;
}

void moving_button::draw(ALLEGRO_FONT* font) {
    return;
}
