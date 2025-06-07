#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include "game_object.hpp"
#include "background_object.hpp"
#include "pipe_object.hpp"
#include "moving_button.hpp"
#include <vector>
#include <random>

// CONSTANTES DE PATH 
extern const char * ARIAL_FONT_FILEPATH;                        // caminho para a fonte arial
extern const char * PSANS_FONT_FILEPATH;                        // caminho para a fonte pixelify sans
extern const char * BIRD_SPRITE[5];                             // bitmap do sprite do pássaro
extern const char * PIPE_SPRITE;                                // caminho do sprite do cano
extern const char * GOLDEN_PIPE_SPRITE;                         // caminho do sprite do cano dourado
extern const char * MOUNTAIN_SPRITE_1;                          // caminho das montanhas (da frente)
extern const char * MOUNTAIN_SPRITE_2;                          // caminho das montanhas (do meio)
extern const char * MOUNTAIN_SPRITE_3;                          // caminho das montanhas (de trás)
extern const char * GRASS_SPRITE;                               // caminho da grama
extern const char * ACHIEVEMENTS_BUTTON_SPRITE;                 // caminho do botão de conquistas
extern const char * BACK_BUTTON_SPRITE;                         // caminho do botão de voltar
extern const char * SETTINGS_BUTTON_SPRITE;                     // caminho do botão de configurações
extern const char * INSTRUÇÕES_SPRITE;                          // caminho das instruções
extern const char * SCORE_SPRITE;                               // caminho da tela de morte
extern const char * HOME_SPRITE;                                // caminho do sprite de home
extern const char * BACKGROUND;                                 // caminho do sprite do fundo
extern const char * NUMBERS_SPRITES[10];                        // caminho dos números 
extern const char * SOUND_BUTTON_SPRITE[2];                     // caminho do botão de som ligado/desligado
extern const char * PAUSE_BUTTON_SPRITE[4];                     // caminho do botão de pause/despause

// CONSTANTES DE PROPRIEDADE PARA OBJETOS DO CENÁRIO
extern const int SCREEN_H;    // altura da tela
extern const int SCREEN_W;    // comprimento da tela
extern const int HEIGHT_REFFERENCE;


// VARIÁVEIS EXTRAS
    extern int random_offset;                                                      // Offset do cano a ser spawnado
    extern float score;
    extern int PIPE_SPACE;                                                  // Espaçamento entre os canos
    extern float PIPE_INITIAL_SPEED;                                        // Velocidade atual dos canos
    extern float PIPE_SPEED_MAX;                                            // Velocidade máxima dos canos
    extern float PIPE_SPEED_INCREASE;                                       // Aumento da velocidade dos canos a cada 10 pontos
    extern int BIRD_JUMP_VEL;                                               // Velocidade do pulo do pássaro
    extern int BIRD_MAX_UP_VEL;                                             // Velocidade máxima de subida do pássaro
    extern int BIRD_MAX_DOWN_VEL;                                           // Velocidade máxima de descida do pássaro

class game_loop {
    private:
        //Vetores dos objetos do jogo
        std::vector<game_object*> game_objects;               // Vetor que armazena os objetos do jogo
        std::vector<moving_button*> buttons;                  // Vetor que armazena os botões do jogo
        std::vector<background_object*> background_objects_0; // Vetor que armazena os tiles de grama
        std::vector<background_object*> background_objects_1; // Vetor que armazena as montanhas (1)
        std::vector<background_object*> background_objects_2; // Vetor que armazena as montanhas (2)
        std::vector<background_object*> background_objects_3; // Vetor que armazena as montanhas (3)

        //Bitmaps dos objetos do jogo
        ALLEGRO_BITMAP* bird_animation_sprite[5];             // Vetor de bitmaps do pássaro
        ALLEGRO_BITMAP* pipe_sprite;                          // Bitmap do cano 
        ALLEGRO_BITMAP* golden_pipe_sprite;                   // Bitmap do cano dourado
        ALLEGRO_BITMAP* mountain_sprite_1;                    // Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    // Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    // Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         // Bitmap da grama 
        ALLEGRO_BITMAP* achievements_button_sprite;           // Bitmap do botão de conquistas
        ALLEGRO_BITMAP* back_button_sprite;                   // Bitmap do botão de voltar
        ALLEGRO_BITMAP* settings_button_sprite;               // Bitmap do botão de configurações
        ALLEGRO_BITMAP* instruções_sprite;                    // Bitmap das instruções
        ALLEGRO_BITMAP* score_sprite;                         // Bitmap da tela de morte
        ALLEGRO_BITMAP* home_sprite;                          // Bitmap do botão de home
        ALLEGRO_BITMAP* background;                           // Bitmap do fundo
        ALLEGRO_BITMAP* numbers_sprites[10];                  // Bitmap dos números de 0 a 9 
        ALLEGRO_BITMAP* sound_button_sprite[2];               // Vetor de bitmaps do botão de som ligado/desligado
        ALLEGRO_BITMAP* pause_button_sprite[4];               // Vetor de bitmaps do botão de pause/despause

        //Fontes do jogo
        ALLEGRO_FONT *pixel_sans;

        //Cores do jogo
        ALLEGRO_COLOR black;

        //Váriáveis de estado do game_loop
        bool playing = false;
        bool dead = false;
        bool death_menu = false;
        bool paused = false;
        bool sound = true; 
        bool debug_mode = true;

    public:
        game_loop();               // Construtor
        ~game_loop();              // Destrutor
        void commands(unsigned char key[], bool mouse_is_down, bool &mouse_just_released, int mouse_update_x, int mouse_update_y);
        void update(bool update);  // Método que atualiza o estado dos objetos do jogo
        void draw();               // Método que desenha os objetos do jogo na tela
        void reset_game();         // Método que reseta o jogo, recriando os objetos e o cenário
};
#endif // GAME_LOOP_HPP