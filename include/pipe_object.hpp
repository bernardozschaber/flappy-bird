#include "game_object.hpp"
#ifndef PIPE_OBJECT_HPP
#define PIPE_OBJECT_HPP

/**
 * @class pipe_object
 * @brief Classe que representa os canos do jogo: Herda da classe genérica de objetos do jogo
 * 
 * Os canos se movem horizontalmente na tela de acordo com uma velocidade fixa.
 */
class pipe_object : public game_object {
    private:
        static float vel_x;     ///< Velocidade fixa de movimento horizontal dos canos
        int vel_y;              ///< Velocidade vertical dos canos
        bool scored;            ///< Indica se o cano já foi "marcado" (se o pássaro passou por ele)
        bool golden;            ///< Indica se o cano é um cano dourado (que vale mais pontos)

    public:
        /**
         * @brief Construtor da classe pipe_object
         * @param pos_x Posição X do cano
         * @param pos_y Posição Y do cano
         * @param width Largura do cano
         * @param height Altura do cano
         * @param Bitmap Bitmap(sprite) do cano
         * @param is_golden Indica se o cano é um cano dourado
         */
        pipe_object(float pos_x, float pos_y, int width, int height, ALLEGRO_BITMAP *Bitmap, bool is_golden);

        /**
         * @brief Desenha o cano na tela
         * @param scale Escala de desenho do cano
         */
        void Draw(float scale);

        /**
         * @brief Atualiza a posição do cano
         * @param a Não utilizado, mas necessário para manter a assinatura
         * @param b Não utilizado, mas necessário para manter a assinatura
         */
        void Update(int a, int b);

        /**
         * @brief Seta a velocidade horizontal do cano
         * @param new_x_speed Nova velocidade horizontal a ser definida
         */
        void Set_x_speed(float new_x_speed);

        /**
         * @brief Seta a velocidade vertical do cano
         * @param new_y_speed Nova velocidade vertical a ser definida
         */
        void Set_y_speed(float new_y_speed);

        /**
         * @brief Seta se o cano já foi pontuado (se o pássaro passou por ele)
         * @param scored True caso para que tenha sido pontuado, false caso contrário
         */
        void Set_score(bool scored);

        /**
         * @brief Verifica se o cano já foi pontuado (se o pássaro passou por ele)
         * @return True se o cano já foi pontuado, false caso contrário
         */
        bool is_scored();

        /**
         * @brief Verifica se o cano é um cano dourado
         * @return True se o cano é dourado, false caso contrário
         */
        bool is_golden();

        /**
         * @brief Retorna a velocidade horizontal do cano
         * @return Velocidade horizontal do cano            
         */
        float Get_x_speed();

};
#endif // PIPE_OBJECT_HPP