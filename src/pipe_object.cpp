#include "game_object.hpp"
#include "pipe_object.hpp"

pipe_object::pipe_object(float a, float b, int c, int d, ALLEGRO_BITMAP *Bitmap, bool is_golden) : game_object(a, b, c, d, Bitmap), vel_y(0), scored(false), golden(is_golden) {};
    
void pipe_object::Draw(float scale){
    abs_pos* drw_pos = this->Get_position();
    al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,scale,scale,0,0);
};
    
void pipe_object::Update(int a , int b){
    this->Get_position()->x += vel_x;
    this->Get_position()->y += vel_y;
};

void pipe_object::Set_x_speed(float a){
    vel_x = a;
};

void pipe_object::Set_y_speed(float a){
    this->vel_y = a;
};

void pipe_object::Set_score(bool a){
    this->scored = a;
};

bool pipe_object::is_scored(){
    return scored;
}

bool pipe_object::is_golden() {
    return golden;
}

float pipe_object::Get_x_speed(){
    return vel_x;
};
