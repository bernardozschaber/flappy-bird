#include "game_object.hpp"
#include "bird_object.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>


    bird_object::bird_object(int a, int b, int c, int d, char* e, int f, int g, int h) : 
    game_object(a, b, c, d, e), vel_x(0), vel_y(0), acel_x(0), acel_y(0), VEL_MAX(f), VEL_MIN(g), JUMP_VEL(h), angle(0){};

    void bird_object::Update(int SCREEN_W, int SCREEN_H){
        abs_pos* upd_pos = this->Get_position();
            upd_pos->x+=vel_x;
        if(upd_pos->y+vel_y>SCREEN_H+100){
            upd_pos->y=SCREEN_H+100;
        }else if(upd_pos->y+vel_y<-100){
            upd_pos->y=-100;
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

    void bird_object::Draw(){
        abs_pos* drw_pos = this->Get_position();
        if (vel_y<0){
            angle=((-vel_y*(8.0/(18.0*VEL_MAX))*3.14)+angle)/2.0;
        }else if(vel_y>0){
            angle=((vel_y*(1.0/(2.0*VEL_MIN))*3.14)+angle)/2.0;
        }
        al_draw_scaled_rotated_bitmap(this->get_bitmap(),drw_pos->x+(drw_pos->w/2),drw_pos->y+(drw_pos->h/2),drw_pos->x,drw_pos->y,0.15,0.15,angle,0);
    }
        
    void bird_object::Jump(){
        if (this->vel_y>0){
            this->vel_y=JUMP_VEL;
        }else{
            this->vel_y+=JUMP_VEL;
        }
    };

    void bird_object::Set_x_speed(int a){
        this->vel_x=a;
    };

    void bird_object::Set_x_acelleration(int a){
        this->acel_x=a;
    };

    void bird_object::Set_y_speed(int a){
        this->vel_y=a;
    };

    void bird_object::Set_y_acelleration(int a){
        this->acel_y=a;
    };