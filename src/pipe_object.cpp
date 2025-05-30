#include "game_object.hpp"
#include "pipe_object.hpp"


pipe_object::pipe_object(int a, int b, int c, int d, char *e, float f) : game_object(a, b, c, d, e), vel_x(f), vel_y(0), scored(false) {};
    
void pipe_object::Draw(float scale){
    abs_pos* drw_pos = this->Get_position();
    al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,scale,scale,0,0);
};
    
void pipe_object::Update(int a , int b){
    this->Get_position()->x += vel_x;
    this->Get_position()->y += vel_y;
};

void pipe_object::Set_x_speed(int a){
    this->vel_x = a;
};

void pipe_object::Set_y_speed(int a){
    this->vel_y = a;
};

void pipe_object::Set_score(bool a){
    this->scored = a;
};