#include "game_object.hpp"

    game_object::game_object(float a, float b, int c, int d, const char* e) : position{a,b,c,d}, Bitmap(al_load_bitmap(e)){};
    
    void game_object::Draw(float scale){
        al_draw_scaled_rotated_bitmap(this->Bitmap, position.w/2, position.h/2, position.x, position.y, scale, scale, 0, 0);
    }

    abs_pos* game_object::Get_position(){
        return &(this->position);
    }

    bool game_object::is_colliding(game_object* position_two) {
        abs_pos* pos_one = this->Get_position();
        abs_pos* pos_two = position_two->Get_position();

        return (std::abs(pos_one->x - pos_two->x) * 2 < (al_get_bitmap_width(this->get_bitmap())-6 + al_get_bitmap_width(position_two->get_bitmap()))) && (std::abs(pos_one->y - pos_two->y) * 2 < (al_get_bitmap_height(this->get_bitmap()) + al_get_bitmap_height(position_two->get_bitmap())));
    }

    ALLEGRO_BITMAP* game_object::get_bitmap(){
        return this->Bitmap;
    }

    void game_object::set_bitmap(std::string sprite){
        this->Bitmap = al_load_bitmap(sprite.c_str());
    }