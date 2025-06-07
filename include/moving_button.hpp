#ifndef MOVING_BUTTON_HPP
#define MOVING_BUTTON_HPP
#include "ui_object.hpp"

class moving_button : public ui_object {
    float vel_x = 0;
    float vel_y = 0;
    float acel_x = 0;
    float acel_y = 0;
    bool is_being_pressed = false;
    ALLEGRO_BITMAP* sprite;

    public:
    // Construtor
    moving_button(float x, float y, ALLEGRO_BITMAP* Bitmap);

    // Método para desenhar o botão
    void draw();

    void set_velocity(float vx, float vy);

    void set_acceleration(float ax, float ay);
    
    void set_bitmap(ALLEGRO_BITMAP* bitmap);            // Seta o bitmap para o parâmetro

    bool contains_click(float mouse_x, float mouse_y);  // Retorna true se as posições passadas de parâmetro estão dentro do botão

    void set_pressed(bool pressed);                     // Seta a variável is_being_pressed para o parâmetro

    bool is_pressed();                                  // Retorna is_being_pressed

    // Overrides inúteis só pra não ser abstrata (problema futuro)
    void handle_event(const ALLEGRO_EVENT &ev);

    void draw(ALLEGRO_FONT *font);
};

#endif