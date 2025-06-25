#ifndef SETTINGS_SCREEN_HPP
#define SETTINGS_SCREEN_HPP
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "game_object.hpp"
#include "background_object.hpp"
#include "moving_button.hpp"
#include "image.hpp"
#include "slider.hpp"
#include "game_loop.hpp"
#include <vector>

/**
 * @class settings_screen
 * @brief Classe que representa a tela de configurações do jogo
 * 
 * Esta tela é composta basicamente por sliders e botões que permitem ao usuário alterar as configurações do jogo, como volume, força do pulo, etc.
 */
class settings_screen {
    private:
        // Vetores de objetos
        std::vector<moving_button*> buttons;                  ///< Vetor que armazena os botões do menu de configurações
        std::vector<slider*> slides;                          ///< Vetor que armazena os sliders do menu de configurações
        std::vector<image*> images;                           ///< Vetor que armazena as imagens
        std::vector<background_object*> background_objects_0; ///< Vetor que armazena os tiles de grama (cenário)
        std::vector<background_object*> background_objects_1; ///< Vetor que armazena as montanhas (1) (cenário)
        std::vector<background_object*> background_objects_2; ///< Vetor que armazena as montanhas (2) (cenário)
        std::vector<background_object*> background_objects_3; ///< Vetor que armazena as montanhas (3) (cenário)

        // Bitmaps
        ALLEGRO_BITMAP* mountain_sprite_1;                    ///< Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    ///< Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    ///< Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         ///< Bitmap da grama 
        ALLEGRO_BITMAP* background_sprite;                    ///< Bitmap do fundo
        ALLEGRO_BITMAP* settings_frame_sprite;                ///< Bitmap do quadro da tela de configuração
        ALLEGRO_BITMAP* title_settings_sprite;                ///< Bitmap do titulo da tela de configuração
        ALLEGRO_BITMAP* show_sprite;                          ///< Bitmap da parte de tras do numero do slider
        ALLEGRO_BITMAP* back_sprite[2];                       ///< Bitmap da parte de tras do slider
        ALLEGRO_BITMAP* indicator_sprite[2];                  ///< Bitmap da parte da frente do slider
        ALLEGRO_BITMAP* back_button_sprite[2];                ///< Bitmap do botão de voltar

        // Fonte principal do jogo
        ALLEGRO_FONT* pixel_sans;                             ///< Fonte principal do jogo

    public:
        /**
         * @brief Construtor da classe settings_screen
         */
        settings_screen();

        /**
         * @brief Destrutor da classe settings_screen
         * Destrói bitmaps e objetos da tela
         */
        ~settings_screen();

        /**
         * @brief Processa os comandos da tela de configurações
         * @param key Array de teclas pressionadas
         * @param mouse_is_down Indica se o mouse está pressionado
         * @param mouse_just_released Indica se o mouse foi solto
         * @param mouse_update_x Posição X do mouse na atualização
         * @param mouse_update_y Posição Y do mouse na atualização
         * @param mouse_x_now Posição X atual do mouse
         * @param state Referência ao estado do jogo
         * @param main_game_loop Ponteiro para o loop principal do jogo
         */
        void commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, int mouse_x_now, states& state, Game_Loop* main_game_loop);

        /**
         * @brief Desenha todos os componentes na tela
         */
        void update();

        /**
         * @brief Desenha os objetos da tela de configurações
         */
        void draw();

        /**
         * @brief Pega os valores dos sliders e os armazena nas variáveis correspondentes
         */
        void set_values();
};
#endif