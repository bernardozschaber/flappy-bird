#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct absolute_position{
    float x;
    float y;
    int w;
    int h;
} abs_pos;

class game_object{
private:
    absolute_position position;
    ALLEGRO_BITMAP* Bitmap;
public:
     game_object(float a, float b, int c, int d, const char *e);

     void virtual Draw(float a);

     void virtual Update(int a, int b){};

     abs_pos* Get_position();
    
    ALLEGRO_BITMAP* get_bitmap();

    bool is_colliding(game_object* object);

    void set_bitmap(std::string sprite);

    virtual void Jump() {};
    
    void virtual Set_x_speed(int a){};

    void virtual Set_x_acelleration(int a){};

    void virtual Set_y_speed(int a){};

    void virtual Set_y_acelleration(int a){};

    void virtual Set_score(bool a){};

    void virtual Draw_spin(float SPIN_SPEED){};
};

#endif // GAME_OBJECT_HPP