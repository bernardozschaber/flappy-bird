#ifndef HOME_SCREEN_HPP
#define HOME_SCREEN_HPP

#include "game_object.hpp"
#include "background_object.hpp"
#include "moving_button.hpp"
#include "image.hpp"
#include "game_loop.hpp"
#include <vector>

/**
 * @class Home_Screen
 * @brief Classe que representa a tela de título do jogo
 */
class Home_Screen {
    private:
        // Vetores de objetos
        std::vector<moving_button*> buttons;                  ///< Vetor que armazena os botões da home screen
        std::vector<image*> images;                           ///< Vetor que armazena as imagens
        std::vector<background_object*> background_objects_0; ///< Vetor que armazena os tiles de grama (cenário)
        std::vector<background_object*> background_objects_1; ///< Vetor que armazena as montanhas(1) (cenário)
        std::vector<background_object*> background_objects_2; ///< Vetor que armazena as montanhas(2) (cenário)
        std::vector<background_object*> background_objects_3; ///< Vetor que armazena as montanhas(3) (cenário)

        // Bitmaps
        ALLEGRO_BITMAP* mountain_sprite_1;                    ///< Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    ///< Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    ///< Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         ///< Bitmap da grama 
        ALLEGRO_BITMAP* background_sprite;                    ///< Bitmap do fundo
        ALLEGRO_BITMAP* home_screen_frame_sprite;             ///< Bitmap do quadro da tela de início
        ALLEGRO_BITMAP* achievements_screen_frame_sprite;     ///< Bitmap do quadro da tela de achievements
        ALLEGRO_BITMAP* title_sprite;                         ///< Bitmap do título do jogo
        ALLEGRO_BITMAP* achievements_button_sprite[2];        ///< Bitmap do botão de achievements
        ALLEGRO_BITMAP* settings_button_sprite[2];            ///< Bitmap do botão de configurações
        ALLEGRO_BITMAP* play_button_sprite[2];                ///< Bitmap do botão de jogar
        ALLEGRO_BITMAP* statistics_button_sprite[2];          ///< Bitmap do botão de estatísticas (stats)
        ALLEGRO_BITMAP* logout_button_sprite[2];              ///< Bitmap do botão de logout

        // Fontes usadas
        ALLEGRO_FONT* title_font;                             ///< Fonte de título
        ALLEGRO_FONT* regular_text_font;                      ///< Fonte de texto regular

    public:
        /**
         * @brief Construtor da classe Home_Screen
         */
        Home_Screen();

        /**
         * @brief Destrutor da classe Home_Screen
         * Destrói bitmaps e objetos da tela
         */
        ~Home_Screen();     // Destrutor

        /**
         * @brief Processa os comandos da tela de início
         * @param key Array de teclas pressionadas
         * @param mouse_is_down Indica se o mouse está pressionado
         * @param mouse_just_released Indica se o mouse foi solto
         * @param mouse_update_x Posição X de click/release do mouse
         * @param mouse_update_y Posição Y de click/release do mouse
         * @param state Referência ao estado do jogo
         */
        void commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, states& state);

        /**
         * @brief Atualiza o estado dos objetos da tela de início
         */
        void update();

        /**
         * @brief Desenha os objetos da tela de início
         */
        void draw();
};

#endif