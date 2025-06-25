#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

#include "image.hpp"
#include "moving_button.hpp"
#include "slider.hpp"

// -----------------------------------------------------------------------------
// AllegroInit
// Inicializa subsistemas de Allegro antes de qualquer teste.
// -----------------------------------------------------------------------------
struct AllegroInit {
    AllegroInit() {
        al_init();
        al_init_image_addon();
    }
} _allegro_init;

// -----------------------------------------------------------------------------
// TEST_CASES
// -----------------------------------------------------------------------------

TEST_CASE("image: criação e métodos") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(50, 50);
    image img(bitmap, 100, 100);  // Objeto de testes

    // Testa criação
    CHECK(img.get_x() == 100);
    CHECK(img.get_y() == 100);
    CHECK(img.get_velocity_x() == 0);
    CHECK(img.get_velocity_y() == 0);

    // Testa setters
    img.set_position_x(150);
    img.set_position_y(200);
    img.set_velocity(10, -5);
    img.set_acceleration(1, 1);

    CHECK(img.get_x() == 150);
    CHECK(img.get_y() == 200);
    CHECK(img.get_velocity_x() == 10);
    CHECK(img.get_velocity_y() == -5);

    // Update
    img.Update();
    CHECK(img.get_x() == 160);          // Verifica nova posição X
    CHECK(img.get_y() == 195);          // Verifica nova posição Y
    CHECK(img.get_velocity_x() == 11);  // Verifica nova velocidade X
    CHECK(img.get_velocity_y() == -4);  // Verifica nova velocidade Y
    img.Update();
    CHECK(img.get_x() == 171);          // Verifica nova posição X após segundo update
    CHECK(img.get_y() == 191);          // Verifica nova posição Y após segundo update
    CHECK(img.get_velocity_x() == 12);  // Verifica nova velocidade X após segundo update
    CHECK(img.get_velocity_y() == -3);  // Verifica nova velocidade Y após segundo update

    // Limpeza
    al_destroy_bitmap(bitmap);
}

TEST_CASE("moving_button: criação e métodos") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(50, 50);
    moving_button btn(100, 100, bitmap);  // Objeto de testes

    // Testa criação
    CHECK(btn.get_x() == 100);
    CHECK(btn.get_y() == 100);
    CHECK(btn.get_velocity_x() == 0);
    CHECK(btn.get_velocity_y() == 0);
    CHECK(btn.get_acel() == 0);

    // Testa setters
    btn.set_velocity(5, -3);
    btn.set_acceleration(0.5, 0.5);

    CHECK(btn.get_velocity_x() == 5);
    CHECK(btn.get_velocity_y() == -3);
    CHECK(btn.get_acel() == 0.5);

    // Clique
    CHECK(btn.contains_click(75, 75) == true);      // Clique dentro do botão
    CHECK(btn.contains_click(120, 100) == true);    // Clique dentro do botão
    CHECK(btn.contains_click(100, 175) == false);   // Clique fora do botão
    CHECK(btn.contains_click(75, 100) == true);     // Clique na borda do botão

    // Update
    btn.Update();
    CHECK(btn.get_x() == 105);              // Verifica nova posição X
    CHECK(btn.get_y() == 97);               // Verifica nova posição Y
    CHECK(btn.get_velocity_x() == 5.5);     // Verifica nova velocidade X
    CHECK(btn.get_velocity_y() == -2.5);    // Verifica nova velocidade Y
    btn.Update();
    CHECK(btn.get_x() == 110.5);            // Verifica nova posição X após segundo update
    CHECK(btn.get_y() == 94.5);             // Verifica nova posição Y após segundo update
    CHECK(btn.get_velocity_x() == 6);       // Verifica nova velocidade X após segundo update
    CHECK(btn.get_velocity_y() == -2);      // Verifica nova velocidade Y após segundo update

    // Limpeza
    al_destroy_bitmap(bitmap);
}

TEST_CASE("slider: criação e métodos") {
    // Criação de bitmaps padrão para inicialização
    ALLEGRO_BITMAP* back_bitmap = al_create_bitmap(200, 20);
    ALLEGRO_BITMAP* indicator_bitmap = al_create_bitmap(10, 20);
    ALLEGRO_BITMAP* show_bitmap = al_create_bitmap(50, 20);

    slider sld(&back_bitmap, &indicator_bitmap, show_bitmap, 100, 100, 1.0, true, 0.0, 0.0, 1.0, -50.00, 50.0, 0, true);

    // Testa criação
    CHECK(sld.get_x() == 100);
    CHECK(sld.get_y() == 100);
    CHECK(sld.get_width() == 200);
    CHECK(sld.get_height() == 20);
    CHECK(sld.get_value() == 0);

    // Teste de valor
    sld.update(true, false, 100, 100, 100);
    CHECK(sld.get_value() == 0);  // Valor inicial deve ser 0
    sld.update(true, false, 100, 100, 150);
    CHECK(sld.get_value() == 50);  // Valor deve ser 50 após mover o indicador para a direita
    sld.update(false, true, 150, 40, 150);
    CHECK(sld.get_value() == 50);  // Valor deve permanecer 50 após soltar o mouse

    sld.update(true, false, 50, 110, 50);
    CHECK(sld.get_value() == -50);  // Valor deve ser -50 após clique
    sld.update(true, false, 50, 110, 100);
    CHECK(sld.get_value() == 0);  // Valor deve ser 0 após mover o indicador de volta para a posição inicial
    sld.update(false, true, 100, 110, 100);
    CHECK(sld.get_value() == 0);  // Valor deve permanecer 0 após soltar o mouse

    sld.update(true, false, 200, 100, 200);
    CHECK(sld.get_value() == 50);  // Valor deve ser 50 após clique
    sld.update(true, false, 200, 100, 250);
    CHECK(sld.get_value() == 50);  // Valor deve permanecer 50 após mover o indicador além do máximo
    sld.update(false, true, 250, 100, 250);
    CHECK(sld.get_value() == 50);  // Valor deve permanecer 50 após soltar o mouse

    sld.update(true, false, 200, 100, 200);
    CHECK(sld.get_value() == 50);  // Valor deve ser 50 após clique
    sld.update(true, false, 200, 100, -70);
    CHECK(sld.get_value() == -50);  // Valor deve ser -50 após mover o indicador para a esquerda
    sld.update(false, true, -70, 100, -70);
    CHECK(sld.get_value() == -50);  // Valor deve permanecer -50 após soltar o mouse

    sld.update(true, false, 100, 50, 100);
    CHECK(sld.get_value() == -50);  // Nada deve acontecer com um clique fora do slider
    sld.update(true, false, 100, 50, 150);
    CHECK(sld.get_value() == -50);  // Nada deve acontecer com um clique fora do slider
    sld.update(false, true, 150, 50, 150);
    CHECK(sld.get_value() == -50);  // Valor deve permanecer -50 após soltar o mouse fora do slider

    // Limpeza
    al_destroy_bitmap(back_bitmap);
    al_destroy_bitmap(indicator_bitmap);
    al_destroy_bitmap(show_bitmap);
}