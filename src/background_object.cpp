#include "background_object.hpp"

float background_object::standard_x_speed = 0;

background_object::background_object(float pos_x, float pos_y, int width, int height, ALLEGRO_BITMAP* Bitmap) : game_object(pos_x, pos_y, width, height, Bitmap) {};

void background_object::Draw(float scale) {
    abs_pos* drawing_position = this->Get_position();
    al_draw_scaled_rotated_bitmap(this->get_bitmap(), drawing_position->w/2, drawing_position->h/2, drawing_position->x, drawing_position->y, scale, scale, 0, 0);
}

void background_object::Update(const int SCREEN_W, const int SCREEN_H, const float multiplier) {
    this->Get_position()->x += background_object::standard_x_speed * multiplier;
}

float background_object::Get_standard_speed() {
    return background_object::standard_x_speed;
}

void background_object::Set_standard_speed(float new_std_speed) {
    background_object::standard_x_speed = new_std_speed;
}