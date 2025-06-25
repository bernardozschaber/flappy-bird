#ifndef IMAGE_H
#define IMAGE_H
#include "ui_object.hpp"

/**
 * @class image
 * @brief Classe que representa uma imagem no jogo
 * 
 * Esta classe é usada exatamente como uma imagem, não possui interações mas pode se mover.
 */
class image {
    private:
        ALLEGRO_BITMAP* bitmap; ///< Bitmap(sprite) da imagem
        float vel_x;            ///< Velocidade horizontal da imagem
        float vel_y;            ///< Velocidade vertical da imagem
        float acel_x;           ///< Aceleração horizontal da imagem
        float acel_y;           ///< Aceleração vertical da imagem
        float x, y;             ///< Posição X e Y da imagem
        int width, height;      ///< Largura e altura da imagem
    
    public:
        /**
         * @brief Construtor da classe image
         * @param sprite Bitmap(sprite) da imagem
         * @param x Posição X da imagem
         * @param y Posição Y da imagem
         * @details Este construtor inicializa velocidade e aceleração como 0, e largura e altura como as dimensões do bitmap.
         */
        image(ALLEGRO_BITMAP* sprite, float x, float y) : image(sprite, x, y, 0, 0, 0, 0) { };

        /**
         * @brief Construtor da classe image
         * @param sprite Bitmap(sprite) da imagem
         * @param x Posição X da imagem
         * @param y Posição Y da imagem
         * @param vx Velocidade horizontal da imagem
         * @param vy Velocidade vertical da imagem
         * @param ax Aceleração horizontal da imagem
         * @param ay Aceleração vertical da imagem
         * @details Este construtor inicializa a largura e altura como as dimensões do bitmap.
         */
        image(ALLEGRO_BITMAP* sprite, float x, float y, float vx, float vy, float ax, float ay);

        /**
         * @brief Desenha a imagem na tela
         */
        void Draw();

        /**
         * @brief Desenha a imagem na tela com escala
         * @param scale Fator de escala para desenhar a imagem
         */
        void Draw(float scale);

        /**
         * @brief Atualiza a posição da imagem com base na velocidade e aceleração
         */
        void Update();

        /**
         * @brief Retorna a posição X da imagem
         * @return Coordenada X de posição imagem
         */
        float get_x();

        /**
         * @brief Retorna a posição Y da imagem
         * @return Coordenada Y de posição imagem
         */
        float get_y();

        /**
         * @brief Retorna a velocidade horizontal da imagem
         * @return Velocidade X da imagem
         */
        float get_velocity_x();

        /**
         * @brief Retorna a velocidade vertical da imagem
         * @return Velocidade Y da imagem
         */
        float get_velocity_y();

        /**
         * @brief Seta a posição X da imagem
         * @param new_x Nova posição X a ser definida
         */
        void set_position_x(float new_x);

        /**
         * @brief Seta a posição Y da imagem
         * @param new_y Nova posição Y a ser definida
         */
        void set_position_y(float new_y);

        /**
         * @brief Seta a velocidade da imagem
         * @param new_vel_x Nova velocidade horizontal a ser definida
         * @param new_vel_y Nova velocidade vertical a ser definida
         */
        void set_velocity(float new_vel_x, float new_vel_y);

        /**
         * @brief Seta a aceleração da imagem
         * @param new_accel_x Nova aceleração horizontal a ser definida
         * @param new_accel_y Nova aceleração vertical a ser definida
         */
        void set_acceleration(float new_accel_x, float new_accel_y);
        
        /**
         * @brief Troca o bitmap(sprite) da imagem
         * @param new_sprite Novo bitmap a ser usado
         */
        void set_bitmap(ALLEGRO_BITMAP* new_sprite);
};

#endif