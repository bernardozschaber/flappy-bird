#ifndef HOME_SCREEN_HPP
#define HOME_SCREEN_HPP

#include "game_object.hpp"
#include "background_object.hpp"
#include "moving_button.hpp"
#include "image.hpp"
#include <vector>

class home_screen {
    private:
        std::vector<moving_button*> buttons;                  // Vetor que armazena os botões do jogo
        std::vector<background_object*> background_objects_0; // Vetor que armazena os tiles de grama
        std::vector<background_object*> background_objects_1; // Vetor que armazena as montanhas (1)
        std::vector<background_object*> background_objects_2; // Vetor que armazena as montanhas (2)
        std::vector<background_object*> background_objects_3; // Vetor que armazena as montanhas (3)

        ALLEGRO_BITMAP* mountain_sprite_1;                    // Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    // Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    // Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         // Bitmap da grama 
        ALLEGRO_BITMAP* background;                           // Bitmap do fundo
        ALLEGRO_BITMAP* home_screen_frame;                    // Bitmap do quadro da tela de início
        ALLEGRO_BITMAP* title_sprite;                         // Bitmap do título do jogo
        ALLEGRO_BITMAP* achievements_button_sprite[2];        // Bitmap do botão de achievements
        ALLEGRO_BITMAP* settings_button_sprite[2];            // Bitmap do botão de configurações
        ALLEGRO_BITMAP* play_button_sprite[2];                // Bitmap do botão de jogar

    public:
        home_screen();      // Construtor
        ~home_screen();     // Destrutor

        void commands();    // Método que processa os comandos 
        void update();      // Método que atualiza o estado dos objetos
        void draw();        // Método que desenha os objetos
};

#endif