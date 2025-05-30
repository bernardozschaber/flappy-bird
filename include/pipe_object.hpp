#include "game_object.hpp"
#ifndef PIPE_OBJECT_HPP
#define PIPE_OBJECT_HPP

class pipe_object : public game_object {
private:
    float vel_x;
    int vel_y;
    bool scored;
public:
    pipe_object(float a, float b, int c, int d, const char * e, float f);

    void Draw(float a);

    void Update(int a, int b);

    void Set_x_speed(int a);

    void Set_y_speed(int a);

    void Set_score(bool a);

};
#endif // PIPE_OBJECT_HPP