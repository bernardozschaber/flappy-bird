#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include "game_object.hpp"
#include "background_object.hpp"
#include "pipe_object.hpp"
#include "moving_button.hpp"
#include "bird_object.hpp"
#include "image.hpp"
#include "score.hpp"
#include <allegro5/allegro_audio.h>
#include <vector>
#include <random>

// CONSTANTES DE PATH 
extern const char * ARIAL_FONT_FILEPATH;                        // caminho para a fonte arial
extern const char * PSANS_FONT_FILEPATH;                        // caminho para a fonte pixelify sans
extern const char * BIRD_SPRITE[6];                             // bitmap do sprite do pássaro
extern const char * PIPE_SPRITE;                                // caminho do sprite do cano
extern const char * GOLDEN_PIPE_SPRITE;                         // caminho do sprite do cano dourado
extern const char * MOUNTAIN_SPRITE_1;                          // caminho das montanhas (da frente)
extern const char * MOUNTAIN_SPRITE_2;                          // caminho das montanhas (do meio)
extern const char * MOUNTAIN_SPRITE_3;                          // caminho das montanhas (de trás)
extern const char * GRASS_SPRITE;                               // caminho da grama
extern const char * ACHIEVEMENTS_BUTTON_SPRITE[2];              // caminho do botão de conquistas
extern const char * BACK_BUTTON_SPRITE[2];                      // caminho do botão de voltar
extern const char * SETTINGS_BUTTON_SPRITE[2];                  // caminho do botão de configurações
extern const char * INSTRUÇÕES_SPRITE;                          // caminho das instruções
extern const char * SCORE_SPRITE;                               // caminho da tela de morte
extern const char * HOME_SPRITE[2];                             // caminho do sprite de home
extern const char * BACKGROUND;                                 // caminho do sprite do fundo
extern const char * NUMBERS_SPRITES[10];                        // caminho dos números 
extern const char * SOUND_BUTTON_SPRITE[4];                     // caminho do botão de som ligado/desligado
extern const char * PAUSE_BUTTON_SPRITE[4];                     // caminho do botão de pause/despause
extern const char * DEATH_SCREEN_FRAME;                         // caminho do frame da tela de morte
extern const char * TRY_AGAIN_BUTTON_SPRITE[2];                 // caminho do botão de tentar de novo
extern const char * SCORE_NOW;                                  // caminho do sprite do score da jogatina
extern const char * MAX_SCORE;                                  // caminho do sprite do max score
extern const char * PAUSED;                                     // caminho do sprite do texto de pause
extern const char * SCORE_BOX_1;                                // caminho da caixa de score
extern const char * SCORE_BOX_2;                                // caminho da caixa de score
extern const char * STATISTICS_BUTTON_SPRITE[2]; // caminho do botão de achievements

// CONSTANTES DE PROPRIEDADE PARA OBJETOS DO CENÁRIO
extern const int SCREEN_H;    // altura da tela
extern const int SCREEN_W;    // comprimento da tela
extern const int HEIGHT_REFFERENCE;


// VARIÁVEIS EXTRAS
    extern int random_offset;                                                      // Offset do cano a ser spawnado
    extern float golden_odds_setter;
    extern float gravity_setter;
    extern float score;
    extern float max_score;
    extern int PIPE_SPACE;                                                  // Espaçamento entre os canos
    extern float PIPE_INITIAL_SPEED;                                        // Velocidade atual dos canos
    extern float PIPE_SPEED_MAX;                                            // Velocidade máxima dos canos
    extern float PIPE_SPEED_INCREASE;                                       // Aumento da velocidade dos canos a cada 10 pontos
    extern int BIRD_JUMP_VEL;                                               // Velocidade do pulo do pássaro
    extern int BIRD_MAX_UP_VEL;                                             // Velocidade máxima de subida do pássaro
    extern int BIRD_MAX_DOWN_VEL;                                           // Velocidade máxima de descida do pássaro

// STRUCT PARA CONTROLAR OS ESTADOS DO JOGO
struct states{
    bool open = true;                  // Jogo está aberto
    bool is_updating = false;          // O jogo deve atualizar o estado
    bool registration_screen = true;   // Tela de registro está aberta
    bool settings_screen = false;      // Tela de configurações está aberta
    bool was_in_menu = false;
    bool was_playing = false;
    bool game_loop_screen = false;     // O jogo está no loop de jogo
    bool achievements_screen = false;  // Tela de conquistas está aberta
    bool home_screen = false;          // Tela inicial esta aberta
    float volume = 1.0;
};

class Game_Loop {
    private:
        //Vetores dos objetos do jogo
        bird_object* birdo;
        std::vector<pipe_object*> pipe_objects;               // Vetor que armazena os objetos do jogo
        std::vector<moving_button*> buttons;                  // Vetor que armazena os botões do jogo
        std::vector<background_object*> background_objects_0; // Vetor que armazena os tiles de grama
        std::vector<background_object*> background_objects_1; // Vetor que armazena as montanhas (1)
        std::vector<background_object*> background_objects_2; // Vetor que armazena as montanhas (2)
        std::vector<background_object*> background_objects_3; // Vetor que armazena as montanhas (3)
        std::vector<image*> images;                           // Vetor que armazena imagens

        //Bitmaps dos objetos do jogo
        ALLEGRO_BITMAP* bird_animation_sprite[6];             // Vetor de bitmaps do pássaro
        ALLEGRO_BITMAP* pipe_sprite;                          // Bitmap do cano 
        ALLEGRO_BITMAP* golden_pipe_sprite;                   // Bitmap do cano dourado
        ALLEGRO_BITMAP* mountain_sprite_1;                    // Bitmap da montanha (da frente)
        ALLEGRO_BITMAP* mountain_sprite_2;                    // Bitmap da montanha (do meio)
        ALLEGRO_BITMAP* mountain_sprite_3;                    // Bitmap da montanha (de trás)
        ALLEGRO_BITMAP* grass_sprite;                         // Bitmap da grama 
        ALLEGRO_BITMAP* achievements_button_sprite[2];        // Bitmap do botão de conquistas
        ALLEGRO_BITMAP* back_button_sprite[2];                // Bitmap do botão de voltar
        ALLEGRO_BITMAP* settings_button_sprite[2];            // Bitmap do botão de configurações
        ALLEGRO_BITMAP* instruções_sprite;                    // Bitmap das instruções
        ALLEGRO_BITMAP* score_sprite;                         // Bitmap da tela de morte
        ALLEGRO_BITMAP* home_sprite[2];                       // Bitmap do botão de home
        ALLEGRO_BITMAP* background;                           // Bitmap do fundo
        ALLEGRO_BITMAP* numbers_sprites[10];                  // Bitmap dos números de 0 a 9 
        ALLEGRO_BITMAP* sound_button_sprite[4];               // Vetor de bitmaps do botão de som ligado/desligado
        ALLEGRO_BITMAP* pause_button_sprite[4];               // Vetor de bitmaps do botão de pause/despause
        ALLEGRO_BITMAP* death_screen_frame;                   // Bitmap do frame da tela de morte
        ALLEGRO_BITMAP* best_score_text;                      // Bitmap do texto de melhor pontuação (tela de morte)
        ALLEGRO_BITMAP* new_best_text;                        // Bitmap do texto de novo recorde (tela de morte)
        ALLEGRO_BITMAP* tryagain_sprite[2];                   // Vetor de bitmaps do botão de tentar de novo
        ALLEGRO_BITMAP* max_score;                            // Bitmap do max score
        ALLEGRO_BITMAP* score_now;                            // Bitmap do score na partida atual
        ALLEGRO_BITMAP* paused_text;                          // Bitmap do texto de pause
        ALLEGRO_BITMAP* score_box_1;                          // Bitmap da caixa de score
        ALLEGRO_BITMAP* score_box_2;                          // Bitmap da caixa de score
        
        //Fontes do jogo
        ALLEGRO_FONT *pixel_sans;

        //Cores do jogo
        ALLEGRO_COLOR black;

        //Controle de áudio
        ALLEGRO_SAMPLE* flap_sound;                 // Som do pulo do pássaro
        ALLEGRO_SAMPLE* score_sound;                // Som de pontuação
        ALLEGRO_SAMPLE* golden_score_sound;         // Som de pontuação quando o pássaro passa pelo cano dourado
        ALLEGRO_SAMPLE* death_sound;                // Som de morte do pássaro
        ALLEGRO_SAMPLE* death_screen_point_sound;   // Som de pontuação na tela de morte
        ALLEGRO_SAMPLE* high_score_sound;           // Som de novo recorde

        //Váriáveis de estado do game_loop
        bool playing = false;
        bool dead = false;
        bool death_menu = false;
        bool paused = false;
        bool sound = true; 
        bool debug_mode = true;

        //Score game_score;
 
    public:
        Game_Loop();               // Construtor
        ~Game_Loop();              // Destrutor
        void commands(unsigned char key[], bool mouse_is_down, bool &mouse_just_released, int mouse_update_x, int mouse_update_y, states* state);
        void update(states* state);             // Método que atualiza o estado dos objetos do jogo
        void draw();               // Método que desenha os objetos do jogo na tela
        void reset_game();         // Método que reseta o jogo, recriando os objetos e o cenário
        void configure(float* valores); //Configura o jogo
};
#endif // GAME_LOOP_HPP