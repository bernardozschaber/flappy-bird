#ifndef BIRD_OBJECT_HPP
#define BIRD_OBJECT_HPP
#include "game_object.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

class bird_object : public game_object{
    private:
        int vel_x;    
        float vel_y;
        int acel_x;
        float acel_y;
        int VEL_MAX;
        int VEL_MIN;
        int JUMP_VEL;
        float angle;

    public:
        //Construtor
        bird_object(float a, float b, int c, int d, ALLEGRO_BITMAP * e, int f, int g, int h);

        //Override
        void Draw(float a);
        void Draw(float a, ALLEGRO_BITMAP* bitmap);
        void Update(int SCREEN_W, int SCREEN_H);
        void Jump();
        void Set_x_speed(float a);
        void Set_x_acelleration(int a);
        void Set_y_speed(float a);
        void Set_y_acelleration(float a);
        void Draw_spin(float SPIN_SPEED);
        float get_vel(){
            return this->vel_x;
        }
        float get_acel(){
            return this->acel_x;
        }
};

#endif // BIRD_OBJECT_HPP