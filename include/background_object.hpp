// NOT YET TESTED, DON'T USE

#ifndef BACKGROUND_OBJECT_HPP
#define BACKGROUND_OBJECT_HPP

#include "game_object.hpp"

class background_object : public game_object {
    private:
        static float standard_x_speed;

    public:
        //Construtor
        background_object(float pos_x, float pos_y, int width, int height, ALLEGRO_BITMAP *Bitmap);

        //Overrides
        void Draw(float scale);
        void Update(const int SCREEN_W, const int SCREEN_H, const float multiplier);
        float Get_standard_speed();                             // Retorna a velocidade padrão de movimento
        void Set_standard_speed(float new_std_speed);           // Seta uma nova velocidade padrão de movimento
};

#endif // BACKGROUND_OBJECT_HPP