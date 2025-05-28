#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game_object.hpp"
#include <string>


    game_object::game_object(int a, int b, int c, int d, std::string e) : position{a,b,c,d}, sprite(e){};
    
    void game_object::Draw(){
        ALLEGRO_BITMAP* BITMAP = al_load_bitmap(sprite.c_str());
        al_draw_scaled_rotated_bitmap(BITMAP,position.x+(position.w/2),position.y+(position.h/2),position.x,position.y,position.w,position.h,0,0);
    }

    void game_object::Update(){};

    abs_pos* game_object::Get_position(){
        return &(this->position);
    }

    std::string game_object::get_sprite(){
        return this->sprite;
    }
