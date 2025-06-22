#include "slider.hpp"
#include <iostream>

    slider::slider(ALLEGRO_BITMAP** back_sprite, ALLEGRO_BITMAP** indicator_sprite, float x, float y, float variation_, bool show_number_, float disp_h_, float disp_v_, float scale_, float min_value_, float max_value_, float value_, bool is_int_): ui_object(x,y,al_get_bitmap_width(back_sprite[0]),al_get_bitmap_height(back_sprite[0])), is_pressed(0), variation(variation_), show_number(show_number_), disp_h(disp_h_), disp_v(disp_v_), scale(scale_), min_value(min_value_), max_value(max_value_), value(value_), is_int(is_int_), pos_indicator((value_-min_value_)/((max_value_-min_value_)/variation_)){
        for (int a=0; a<2; a++){
            back[a]=back_sprite[a];
            indicator[a]=indicator_sprite[a];
        }
    }

    void slider::update(bool mouse_is_down, bool mouse_just_released, int x_at_down, int y_at_down, int x_now){
       if(mouse_is_down&&(this->cointains_indicator(x_at_down,y_at_down)||this->cointains_back(x_at_down,y_at_down))){
            this->is_pressed=true;
        }
        if(is_pressed){
            pos_indicator=x_now-(x-variation/2);
            if(pos_indicator>variation){
                pos_indicator=variation;
            }else if(pos_indicator<0){
                pos_indicator=0;
            }
            value=min_value+pos_indicator*(max_value-min_value)/variation;
            if(is_int){
                value=(int)value;
                pos_indicator=(value-min_value)/((max_value-min_value)/variation);
            }
        }
        if(mouse_just_released){
            this->is_pressed=false;
        }
        //std::cout<<"m"<<mouse_just_released<<std::endl;
        //std::cout<<"p"<<is_pressed<<std::endl;
    };
    void slider::draw(){
        al_draw_scaled_rotated_bitmap(this->back[is_pressed],al_get_bitmap_width(back[is_pressed])/2,al_get_bitmap_height(back[is_pressed])/2,x,y,scale,scale,0,0);
        al_draw_scaled_rotated_bitmap(this->indicator[is_pressed],al_get_bitmap_width(indicator[is_pressed])/2,al_get_bitmap_height(indicator[is_pressed])/2,x-(variation/2-pos_indicator)*scale,y,scale,scale,0,0);
    };

    void slider::set_pressed(bool pressed){
        this->is_pressed=pressed;
    };

    bool slider::cointains_indicator(float mx, float my){
        bool is_within_x = (mx >= this->x - this->width/2) && (mx <= this->x + this->width/2);
        bool is_within_y = (my >= this->y - this->height/2) && (my <= this->y + this->height/2);
        return is_within_x && is_within_y;
    };
    
    bool slider::cointains_back(float mx, float my){
        bool is_within_x = (mx >= this->x - this->width/2) && (mx <= this->x + this->width/2);
        bool is_within_y = (my >= this->y - this->height/2) && (my <= this->y + this->height/2);
        return is_within_x && is_within_y;
    };

    void slider::set_bitmap_back(ALLEGRO_BITMAP* new_back_bitmap){
        this->back[is_pressed]=new_back_bitmap;
    };

    void slider::set_bitmap_indicator(ALLEGRO_BITMAP* new_indicator_bitmap){
        this->indicator[is_pressed]=new_indicator_bitmap;
    };

    float slider::get_value(){
        return this->value;
    };