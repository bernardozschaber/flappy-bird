#ifndef BACKGROUND_OBJECT_HPP
#define BACKGROUND_OBJECT_HPP

#include "game_object.hpp"

/**
 * @class background_object
 * @brief Classe que representa os sprites de fundo do jogo: Herda da classe genérica de objetos do jogo
 *
 * Se movem baseado em uma velocidade padrão, que pode ser alterada por um multiplicador
 */ 
class background_object : public game_object {
    private:
        static float standard_x_speed; ///< Velocidade padrão de movimento no eixo X

    public:
        /**
         * @brief Construtor da classe background_object
         * @param pos_x Posição X do objeto
         * @param pos_y Posição Y do objeto
         * @param width Largura do objeto
         * @param height Altura do objeto
         * @param Bitmap Bitmap(sprite) do objeto
         */
        background_object(float pos_x, float pos_y, int width, int height, ALLEGRO_BITMAP *Bitmap);

        //Overrides
        /**
         * @brief Desenha o objeto na tela
         * @param scale Escala de desenho do objeto
         */
        void Draw(float scale);

        /**
         * @brief Atualiza a posição do objeto
         * @param multiplier Multiplicador de velocidade para o movimento do objeto (baseado na velocidade padrão)
         */
        void Update(const float multiplier);

        /**
         * @brief Retorna a velocidade padrão de movimento
         * @return Velocidade padrão de movimento
         */
        float Get_standard_speed();

        /**
         * @brief Seta uma nova velocidade padrão de movimento
         * @param new_std_speed Nova velocidade padrão a ser definida
         */
        void Set_standard_speed(float new_std_speed);
};

#endif // BACKGROUND_OBJECT_HPP