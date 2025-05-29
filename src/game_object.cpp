#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game_object.hpp"
#include <string>


    game_object::game_object(int a, int b, int c, int d, char* e) : position{a,b,c,d}, Bitmap(al_load_bitmap(e)){};
    
    void game_object::Draw(){
        al_draw_scaled_rotated_bitmap(this->Bitmap,position.x+(position.w/2),position.y+(position.h/2),position.x,position.y,position.w,position.h,0,0);
    }

    void game_object::Update(){};

    abs_pos* game_object::Get_position(){
        return &(this->position);
    }

    ALLEGRO_BITMAP* game_object::get_bitmap(){
        return this->Bitmap;
    }

    void game_object::set_bitmap(std::string sprite){
        this->Bitmap = al_load_bitmap(sprite.c_str());
    }