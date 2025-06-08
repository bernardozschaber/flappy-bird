#ifndef IMAGE_H
#define IMAGE_H
#include "ui_object.hpp"

class image {
    private:
        ALLEGRO_BITMAP* bitmap;
        float vel_x;
        float vel_y;
        float acel_x;
        float acel_y;
        float x, y;
        int width, height;
    
    public:
        //Construtores
        image(ALLEGRO_BITMAP* sprite, float x, float y) : image(sprite, x, y, 0, 0, 0, 0) { };
        image(ALLEGRO_BITMAP* sprite, float x, float y, float vx, float vy, float ax, float ay);

        //Métodos
        void Draw();
        void Draw(float scale);
        void Update();

        //Getters
        float get_x();                              // retorna a posição X
        float get_y();                              // retorna a posição Y
        float get_velocity_x();                     // retorna a velocidade X
        float get_velocity_y();                     // retorna a velocidade Y

        //Setters
        void set_x(float new_x);                        // seta a posição X
        void set_y(float new_y);                        // seta a posição Y
        void set_velocity_x(float new_vel_x);           // seta a velocidade X
        void set_velocity_y(float new_vel_y);           // seta a velocidade Y
        void set_acceleration_x(float new_accel_x);     // seta a aceleração X
        void set_acceleration_y(float new_accel_y);     // seta a aceleração Y
        void set_bitmap(ALLEGRO_BITMAP* new_sprite);    // seta um novo sprite
};

#endif