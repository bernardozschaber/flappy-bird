#include "bird_object.hpp"
#include <iostream>

    bird_object::bird_object(float a, float b, int c, int d, ALLEGRO_BITMAP* e, int f, int g, int h) : 
    game_object(a, b, c, d, e), vel_x(0), vel_y(0), acel_x(0), acel_y(0), VEL_MAX(f), VEL_MIN(g), JUMP_VEL(h), angle(0){};

    void bird_object::Update(int SCREEN_W, int SCREEN_H){
        abs_pos* upd_pos = this->Get_position();
            upd_pos->x+=vel_x;
        if(upd_pos->y+vel_y>SCREEN_H+100){
            upd_pos->y=SCREEN_H+100;
        }else if(upd_pos->y+vel_y<0){
            upd_pos->y=0;
            vel_y=0;
        }else{
            upd_pos->y+=vel_y;
        }
        if(this->vel_y+acel_y<VEL_MAX){
            this->vel_y=VEL_MAX;
        }else if (this->vel_y+acel_y>VEL_MIN){
            this->vel_y=VEL_MIN;
        }else {
            this->vel_y+=acel_y;
        }
        if(this->vel_x+acel_x<VEL_MAX){
            this->vel_x=VEL_MAX;
        }else if (this->vel_x+acel_x>VEL_MIN){
            this->vel_x=VEL_MIN;
        }else {
            this->vel_x+=acel_x;
        }
    }

    void bird_object::Draw(float scale){
        abs_pos* drw_pos = this->Get_position();
        if (vel_y<0){
            angle=((-vel_y*(8.0/(18.0*VEL_MAX))*3.14)+angle)/2.0;
        }else if(vel_y>0){
            angle=((vel_y*(1.0/(2.0*VEL_MIN))*3.14)+angle)/2.0;
        } else {
            angle=0;
        }
        if(this->vel_x>=0){
        al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,scale,scale,angle,0);
        }else{
            al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,-scale,scale,-angle,0);
        }
    }

    void bird_object::Draw_spin(float SPIN_SPEED){
    abs_pos* drw_pos = this->Get_position();
    angle+=SPIN_SPEED;
    al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,1,1,angle,0);
    }

     void bird_object::Draw(float SPIN_SPEED, ALLEGRO_BITMAP* bitmap){
    abs_pos* drw_pos = this->Get_position();
    angle+=SPIN_SPEED;
    al_draw_scaled_rotated_bitmap(bitmap,drw_pos->w/2,drw_pos->h/2,drw_pos->x,drw_pos->y,1,1,angle,0);
    }
        
    void bird_object::Jump(){
        if (this->vel_y>0){
            this->vel_y=JUMP_VEL;
        }else{
            this->vel_y+=JUMP_VEL;
        }
    };

    void bird_object::Set_x_speed(float a){
        this->vel_x=a;
    };

    void bird_object::Set_x_acelleration(int a){
        this->acel_x=a;
    };

    void bird_object::Set_y_speed(float a){
        this->vel_y=a;
    };

    void bird_object::Set_y_acelleration(float a){
        this->acel_y=a;
    };