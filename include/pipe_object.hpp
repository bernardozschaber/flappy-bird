#include "game_object.hpp"
#ifndef PIPE_OBJECT_HPP
#define PIPE_OBJECT_HPP

class pipe_object : public game_object {
private:
    int vel_x;
    int vel_y;
    bool scored;
public:
    pipe_object(int a, int b, int c, int d, std::string e, int f);

    void Draw(float a,float b, float c);

    void Update(){};

    void Set_x_speed(int a);

    void Set_y_speed(int a);

    void Set_score(bool a);

};
#endif // PIPE_OBJECT_HPP