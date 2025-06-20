#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct absolute_position {
    float x;  //posição horizontal do ponto central do objeto
    float y;  //posição vertical do ponto central do objeto
    int w;    //comprimento (width)
    int h;    //altura (height)
} abs_pos;

class game_object {
    private:
        absolute_position position;
        ALLEGRO_BITMAP* Bitmap;

    public:
        //Construtor
        game_object(float a, float b, int c, int d, ALLEGRO_BITMAP* e);

        //Métodos padrão
        abs_pos* Get_position();
        ALLEGRO_BITMAP* get_bitmap();
        bool is_colliding(game_object* other_object);
        void set_bitmap(std::string sprite);
        void set_bitmap(ALLEGRO_BITMAP* sprite);
        void Draw(float scale);
};

#endif // GAME_OBJECT_HPP