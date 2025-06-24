#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <fstream>

#include "game_object.hpp"
#include "background_object.hpp"
#include "pipe_object.hpp"
#include "bird_object.hpp"

// -----------------------------------------------------------------------------
// AllegroInit
// Inicializa subsistemas de Allegro antes de qualquer teste.
// -----------------------------------------------------------------------------
struct AllegroInit {
    AllegroInit() {
        al_init();
        al_install_keyboard();
        al_install_mouse();
        al_install_audio();
        al_init_acodec_addon();
        al_reserve_samples(4);
    }
} _allegro_init;

// -----------------------------------------------------------------------------
// TEST_CASES
// -----------------------------------------------------------------------------

TEST_CASE("game_object: criação e métodos") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(50, 50);
    game_object obj(100, 100, 50, 50, bitmap);              // Objeto de testes

    // Testa criação
    CHECK(obj.Get_position()->x == 100);
    CHECK(obj.Get_position()->y == 100);
    CHECK(obj.Get_position()->w == 50);
    CHECK(obj.Get_position()->h == 50);
    CHECK(obj.get_bitmap() == bitmap);

    // Testa mudança de bitmap
    ALLEGRO_BITMAP* new_bitmap = al_create_bitmap(60, 60);
    obj.set_bitmap(new_bitmap);
    CHECK(obj.get_bitmap() == new_bitmap);

    // Testa colisão com outro objeto
    game_object other_obj_1(120, 120, 40, 30, bitmap);      // Deve colidir com obj
    CHECK(obj.is_colliding(&other_obj_1));
    game_object other_obj_2(100, -100, 60, 60, bitmap);     // Não deve colidir com obj
    CHECK_FALSE(obj.is_colliding(&other_obj_2));
    game_object other_obj_3(150, 100, 50, 50, bitmap);      // Tangencia obj mas não colide
    CHECK_FALSE(obj.is_colliding(&other_obj_3));

    // Limpeza
    al_destroy_bitmap(bitmap);
    al_destroy_bitmap(new_bitmap);
}

TEST_CASE("background_object: criação e métodos") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap1 = al_create_bitmap(100, 60);
    ALLEGRO_BITMAP* bitmap2 = al_create_bitmap(80, 40);
    background_object bg_obj_1(400, 300, 100, 60, bitmap1);     // Objeto de testes 1
    background_object bg_obj_2(200, 150, 80, 40, bitmap2);      // Objeto de testes 2

    // Testa criação
    CHECK(bg_obj_1.Get_position()->x == 400);
    CHECK(bg_obj_1.Get_position()->y == 300);
    CHECK(bg_obj_1.Get_position()->w == 100);
    CHECK(bg_obj_1.Get_position()->h == 60);
    CHECK(bg_obj_1.get_bitmap() == bitmap1);

    // Teste de velocidade padrão estática
    bg_obj_1.Set_standard_speed(-10);
    CHECK(bg_obj_1.Get_standard_speed() == -10);
    CHECK(bg_obj_2.Get_standard_speed() == -10);
    bg_obj_2.Set_standard_speed(-20);
    CHECK(bg_obj_1.Get_standard_speed() == -20);
    CHECK(bg_obj_2.Get_standard_speed() == -20);

    // Testa atualização de posição
    bg_obj_1.Update(2.0);
    bg_obj_2.Update(0.5);
    CHECK(bg_obj_1.Get_position()->x == 360);
    CHECK(bg_obj_2.Get_position()->x == 190);

    // Limpeza
    al_destroy_bitmap(bitmap1);
    al_destroy_bitmap(bitmap2);
}

TEST_CASE("bird_object: criação e atualização") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(50, 50);
    bird_object bird(200, 200, 50, 50, bitmap, 5.0, 10.0, 15.0); // Objeto de testes

    // Testa criação
    CHECK(bird.Get_position()->x == 200);
    CHECK(bird.Get_position()->y == 200);
    CHECK(bird.Get_position()->w == 50);
    CHECK(bird.Get_position()->h == 50);
    CHECK(bird.get_bitmap() == bitmap);
    CHECK(bird.get_vel() == 0);
    CHECK(bird.get_acel() == 0);

    // Testa atualização de posição
    bird.Update(800, 600);
    CHECK(bird.Get_position()->y < 600); // Verifica se a posição Y não ultrapassa o limite inferior

    // Testa salto
    bird.Jump();
    CHECK(bird.Get_position()->y < 200); // Verifica se a posição Y sobe após o salto

    // Limpeza
    al_destroy_bitmap(bitmap);
}

TEST_CASE("pipe_object: criação e atualização") {
    // Criação de um bitmap padrão para inicialização
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(60, 120);
    pipe_object pipe(300, 400, 60, 120, bitmap); // Objeto de testes

    // Testa criação
    CHECK(pipe.Get_position()->x == 300);
    CHECK(pipe.Get_position()->y == 400);
    CHECK(pipe.Get_position()->w == 60);
    CHECK(pipe.Get_position()->h == 120);
    CHECK(pipe.get_bitmap() == bitmap);

    // Testa atualização de posição
    pipe.Update(800, 600);
    CHECK(pipe.Get_position()->x < 300); // Verifica se a posição X diminui após atualização

    // Limpeza
    al_destroy_bitmap(bitmap);
}