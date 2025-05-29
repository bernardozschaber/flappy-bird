#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct absolute_position{
    int x;
    int y;
    int w;
    int h;
} abs_pos;

class game_object{
private:
    absolute_position position;
    ALLEGRO_BITMAP* Bitmap;
public:
     game_object(int a, int b, int c, int d, char *e);

     void virtual Draw();

     void virtual Update();

     abs_pos* Get_position();
    
    ALLEGRO_BITMAP* get_bitmap();

    void set_bitmap(std::string sprite);
};

#endif // GAME_OBJECT_HPP