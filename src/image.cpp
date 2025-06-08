#include "image.hpp"

image::image(ALLEGRO_BITMAP* sprite, float x, float y, float vx, float vy, float ax, float ay) {
    this->vel_x = vx;
    this->vel_y = vy;
    this-> acel_x = ax;
    this-> acel_y = ay;
    this->bitmap = sprite;
    this->x = x;
    this->y = y;
    this->width = al_get_bitmap_width(sprite);
    this->height = al_get_bitmap_height(sprite);
}

float image::get_x() {
    return this->x;
}

float image::get_y() {
    return this->y;
}

float image::get_velocity_x() {
    return this->vel_x;
}

float image::get_velocity_y() {
    return this->vel_y;
}

void image::set_x(float new_x) {
    this->x = new_x;
}

void image::set_y(float new_y) {
    this->y = new_y;
}

void image::set_velocity_x(float new_velocity_x) {
    this->vel_x = new_velocity_x;
}

void image::set_velocity_y(float new_velocity_y) {
    this->vel_y = new_velocity_y;
}

void image::set_acceleration_x(float new_acceleration_x) {
    this->acel_x = new_acceleration_x;
}

void image::set_acceleration_y(float new_acceleration_y) {
    this->acel_y = new_acceleration_y;
}

void image::set_bitmap(ALLEGRO_BITMAP* new_sprite) {
    this->bitmap = new_sprite;
}

void image::Draw() {
    al_draw_tinted_scaled_rotated_bitmap(this->bitmap, al_map_rgba_f(1, 1, 1, 1), width/2, height/2, x, y, 1, 1, 0, 0);
}

void image::Update() {
    this->x += this->vel_x;
    this->y += this->vel_y;
    this->vel_x += this->acel_x;
    this->vel_y += this->acel_y;
}