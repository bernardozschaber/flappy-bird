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

class settings_screen {
    private:
        // Vetores de objetos
        std::vector<moving_button*> buttons;                  // Vetor que armazena os botões do jogo
        std::vector<slider*> slides;
        std::vector<image*> images;                           // Vetor que armazena as imagens
        std::vector<background_object*> background_objects_0; // Vetor que armazena os tiles de grama
        std::vector<background_object*> background_objects_1; // Vetor que armazena as montanhas (1)
        std::vector<background_object*> background_objects_2; // Vetor que armazena as montanhas (2)
        std::vector<background_object*> background_objects_3; // Vetor que armazena as montanhas (3)

        // Bitmaps
        ALLEGRO_BITMAP* mountain_sprite_1;                    // Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    // Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    // Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         // Bitmap da grama 
        ALLEGRO_BITMAP* background_sprite;                    // Bitmap do fundo
        ALLEGRO_BITMAP* settings_frame_sprite;                // Bitmap do quadro da tela de configuração
        ALLEGRO_BITMAP* title_settings_sprite;                // Bitmap do titulo da tela de configuração
        ALLEGRO_BITMAP* back_sprite[2];                       // Bitmap da parte de tras do slider
        ALLEGRO_BITMAP* indicator_sprite[2];                  // Bitmap da parte da frente do slider
        ALLEGRO_BITMAP* back_button_sprite[2];                // Bitmap do botão de voltar

        // Fonte principal do jogo
        ALLEGRO_FONT* pixel_sans;                             // Fonte principal do jogo

    public:
        settings_screen();      // Construtor
        ~settings_screen();     // Destrutor

        void commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, int mouse_x_now, states& state);     // Método que processa os comandos 
        void update();      // Método que atualiza o estado dos objetos
        void draw();        // Método que desenha os objetos
};
#endif