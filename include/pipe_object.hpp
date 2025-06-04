#include "game_object.hpp"
#ifndef PIPE_OBJECT_HPP
#define PIPE_OBJECT_HPP

class pipe_object : public game_object {
    private:
        static float vel_x;
        int vel_y;
        bool scored;

    public:
        //Construtor
        pipe_object(float pos_x, float pos_y, int width, int height, const char *sprite_dir);

        //Override
        void Draw(float a);
        void Update(int a, int b);
        void Set_x_speed(float a);
        void Set_y_speed(float a);
        void Set_score(bool a);
        float Get_x_speed();

};
#endif // PIPE_OBJECT_HPP