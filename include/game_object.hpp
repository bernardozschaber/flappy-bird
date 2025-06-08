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

        //Métodos virtuais
        virtual void Draw(float scale);
        virtual void Update(int screen_w, int screen_h) {};
        virtual void Jump() {};
        virtual void Set_x_speed(float new_x_speed) {};
        virtual void Set_x_acelleration(int new_x_acceleration) {};
        virtual void Set_y_speed(float new_y_speed) {};
        virtual void Set_y_acelleration(int new_y_acceleration) {};
        virtual void Set_score(bool new_score) {};
        virtual void Draw_spin(float spin_speed) {};
        virtual float Get_x_speed() {return 0;}
        virtual bool is_scored() {return false;}
};

#endif // GAME_OBJECT_HPP