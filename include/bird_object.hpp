#ifndef BIRD_OBJECT_HPP
#define BIRD_OBJECT_HPP
#include "game_object.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

class bird_object : public game_object{
private:
    int vel_x;    
    int vel_y;
    int acel_x;
    int acel_y;
    int VEL_MAX;
    int VEL_MIN;
    int JUMP_VEL;
    float angle;
public:
    bird_object(float a, float b, int c, int d, const char * e, int f, int g, int h);
    void Jump();
    void Set_x_speed(int a);
    void Set_x_acelleration(int a);
    void Set_y_speed(int a);
    void Set_y_acelleration(int a);
    void Draw(float a);
    void Update(const int SCREEN_W,const int SCREEN_H);
    void Draw_spin(float SPIN_SPEED);
};

#endif // BIRD_OBJECT_HPP