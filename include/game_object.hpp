#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/**
 * @struct absolute_position
 * @brief Estrutura que armazena a posição e dimensão de um objeto no jogo
 */
typedef struct absolute_position {
    float x;  //posição horizontal do ponto central do objeto
    float y;  //posição vertical do ponto central do objeto
    int w;    //comprimento (width)
    int h;    //altura (height)
} abs_pos;

/**
 * @class button
 * @brief Classe genérica que representa os objetos do jogo
 */ 
class game_object {
    private:
        absolute_position position; ///< Posição absoluta do objeto no jogo
        ALLEGRO_BITMAP* Bitmap;     ///< Bitmap(sprite) do objeto

    public:
        /**
         * @brief Construtor da classe game_object
         * @param x Posição X do objeto
         * @param y Posição Y do objeto
         * @param w Largura do objeto
         * @param h Altura do objeto
         * @param bitmap Bitmap(sprite) do objeto
         */
        game_object(float x, float y, int w, int h, ALLEGRO_BITMAP* bitmap);

        /**
         * @brief Retorna a posição absoluta do objeto
         * @return Ponteiro para a estrutura absolute_position que contém a posição e dimensão do objeto
         */
        abs_pos* Get_position();

        /**
         * @brief Retorna o bitmap(sprite) do objeto
         * @return Bitmap do objeto
         */
        ALLEGRO_BITMAP* get_bitmap();

        /**
         * @brief Detecta colisão entre este objeto e outro objeto
         * @param other_object Referência ao outro objeto a ser verificado a colisão
         * @return True se está colidindo, false caso contrário
         */
        bool is_colliding(game_object* other_object);

        /**
         * @brief Troca o bitmap(sprite) do objeto
         * @param sprite Nome do arquivo de imagem a ser carregado como bitmap
         */
        void set_bitmap(std::string sprite);

        /**
         * @brief Troca o bitmap(sprite) do objeto
         * @param sprite Ponteiro para o bitmap a ser usado
         */
        void set_bitmap(ALLEGRO_BITMAP* sprite);

        /**
         * @brief Desenha o objeto na tela
         * @param scale Escala de desenho do objeto
         */
        void Draw(float scale);
};

#endif // GAME_OBJECT_HPP