#ifndef BIRD_OBJECT_HPP
#define BIRD_OBJECT_HPP
#include "game_object.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

/**
 * @class bird_object
 * @brief Classe que representa o pássaro do jogo: Herda da classe genérica de objetos do jogo
 */
class bird_object : public game_object{
    private:
        int vel_x;      ///< Velocidade horizontal do pássaro
        float vel_y;    ///< Velocidade vertical do pássaro
        int acel_x;     ///< Aceleração horizontal do pássaro
        float acel_y;   ///< Aceleração vertical do pássaro
        int VEL_MAX;    ///< Velocidade máxima do pássaro (negativa/para baixo)
        int VEL_MIN;    ///< Velocidade mínima do pássaro (positiva/para cima)
        int JUMP_VEL;   ///< Velocidade (ou força, intuitivamente) do pulo do pássaro
        float angle;    ///< Ângulo de rotação do pássaro

    public:
        /**
         * @brief Construtor da classe bird_object
         * @param x Posição X do pássaro
         * @param y Posição Y do pássaro
         * @param w Largura do pássaro
         * @param h Altura do pássaro
         * @param bitmap Bitmap(sprite) do pássaro
         * @param max_vel Velocidade máxima do pássaro (negativa/para baixo)
         * @param min_vel Velocidade mínima do pássaro (positiva/para cima)
         * @param jump_vel Velocidade (ou força, intuitivamente) do pulo do pássaro
         */
        bird_object(float x, float y, int w, int h, ALLEGRO_BITMAP * bitmap, int max_vel, int min_vel, int jump_vel);

        //Override
        /**
         * @brief Desenha o pássaro na tela
         * @param scale Escala de desenho do pássaro
         */
        void Draw(float scale);

        /**
         * @brief Desenha o pássaro na tela
         * @param scale Escala de desenho do pássaro
         * @param bitmap Bitmap(sprite) do pássaro
         */
        void Draw(float scale, ALLEGRO_BITMAP* bitmap);

        /**
         * @brief Atualiza a posição e velocidade do pássaro
         * @param SCREEN_W Largura da tela
         * @param SCREEN_H Altura da tela
         */
        void Update(int SCREEN_W, int SCREEN_H);

        /**
         * @brief Faz o pássaro pular
         */
        void Jump();

        /**
         * @brief Seta a velocidade horizontal do pássaro
         * @param new_x_speed Nova velocidade horizontal a ser definida
         */
        void Set_x_speed(float new_x_speed);

        /**
         * @brief Seta a aceleração horizontal do pássaro
         * @param new_x_accel Nova aceleração horizontal a ser definida
         */
        void Set_x_acelleration(int new_x_accel);

        /**
         * @brief Seta a velocidade vertical do pássaro
         * @param new_y_speed Nova velocidade vertical a ser definida
         */
        void Set_y_speed(float new_y_speed);

        /**
         * @brief Seta a aceleração vertical do pássaro
         * @param new_y_accel Nova aceleração vertical a ser definida
         */
        void Set_y_acelleration(float new_y_accel);

        /**
         * @brief Desenha o pássaro girando em torno de seu centro
         * @param SPIN_SPEED Velocidade de rotação do pássaro
         */
        void Draw_spin(float SPIN_SPEED);

        /**
         * @brief Retorna a velocidade horizontal do pássaro
         * @return Velocidade horizontal do pássaro
         */
        float get_vel() {
            return this->vel_x;
        }

        /**
         * @brief Retorna a aceleração horizontal do pássaro
         * @return Aceleração horizontal do pássaro
         */
        float get_acel() {
            return this->acel_x;
        }
};

#endif // BIRD_OBJECT_HPP