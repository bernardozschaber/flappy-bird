#include "game_loop.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// CONSTANTES DE PATH 
const char * ARIAL_FONT_FILEPATH = "assets/fonts/arial.ttf";                                                            // caminho para a fonte arial
const char * PSANS_FONT_FILEPATH = "assets/fonts/pixelify_sans.ttf";                                                    // caminho para a fonte pixelify sans
const char * BIRD_SPRITE[6] = {"assets/bird-1.png","assets/bird-2.png","assets/bird-3.png","assets/bird-4.png","assets/bird-3.png","assets/bird-2.png"};  // bitmap do sprite do pássaro
const char * PIPE_SPRITE = "assets/pipe.png";                                                                     // caminho do sprite do cano
const char * GOLDEN_PIPE_SPRITE = "assets/pipe_golden.png";                                                       // caminho do sprite do cano dourado
const char * MOUNTAIN_SPRITE_1 = "assets/scenario/mountains_1.png";                                                        // caminho das montanhas (da frente)
const char * MOUNTAIN_SPRITE_2 = "assets/scenario/mountains_2.png";                                                        // caminho das montanhas (do meio)
const char * MOUNTAIN_SPRITE_3 = "assets/scenario/mountains_3.png";                                                        // caminho das montanhas (de trás)
const char * GRASS_SPRITE = "assets/scenario/grama.png";                                                                   // caminho da grama
const char * ACHIEVEMENTS_BUTTON_SPRITE[2] = {"assets/UI/achievements_button.png","assets/UI/achievements_button_pressed.png"};                                       // caminho do botão de conquistas
const char * BACK_BUTTON_SPRITE[2] = {"assets/UI/back_button.png","assets/UI/back_button_pressed.png"};                                                       // caminho do botão de voltar
const char * SETTINGS_BUTTON_SPRITE[2] = {"assets/UI/settings_button.png","assets/UI/settings_button_pressed.png"};                                               // caminho do botão de configurações
const char * INSTRUÇÕES_SPRITE = "assets/UI/instruções.png";                                                         // caminho das instruções
const char * SCORE_SPRITE = "assets/UI/score_text.png";                                                                   // caminho da tela de morte
const char * HOME_SPRITE[2]= {"assets/UI/home_button.png","assets/UI/home_button_pressed.png"};                                                                      // caminho do sprite de home
const char * BACKGROUND = "assets/scenario/background.png";                                                                          // caminho do sprite do fundo
const char * NUMBERS_SPRITES[10] = {"assets/UI/num_0.png", "assets/UI/num_1.png", "assets/UI/num_2.png", "assets/UI/num_3.png",  
                                    "assets/UI/num_4.png", "assets/UI/num_5.png", "assets/UI/num_6.png", "assets/UI/num_7.png", 
                                    "assets/UI/num_8.png", "assets/UI/num_9.png"};                                                              // caminho dos números 
const char * SOUND_BUTTON_SPRITE[4] = {"assets/UI/sound_on.png", "assets/UI/sound_off.png", "assets/UI/sound_on_pressed.png", "assets/UI/sound_off_pressed.png"};                            // caminho do botão de som ligado/desligado
const char * PAUSE_BUTTON_SPRITE[4] = {"assets/UI/pause_button.png", "assets/UI/resume_button.png", "assets/UI/pause_button_pressed.png", "assets/UI/resume_button_pressed.png"};                    // caminho do botão de pause/despause
const char * DEATH_SCREEN_FRAME = "assets/UI/death_screen_frame.png";   // caminho do frame da tela de morte
const char * TRY_AGAIN_BUTTON_SPRITE[2] = {"assets/UI/de_novo_button.png","assets/UI/de_novo_button_pressed.png"};  // caminho do botão de jogar de novo
const char * BEST_SCORE_TEXT = "assets/UI/best_score_text.png"; // caminho do texto de melhor pontuação (tela de morte)
const char * NEW_BEST_TEXT = "assets/UI/new_best_text.png"; // caminho do texto de novo recorde (tela de morte) 
const char * SCORE_NOW = "assets/UI/score_text.png";
const char * MAX_SCORE = "assets/UI/max_score_text.png";
const char * PAUSED = "assets/UI/paused_text.png";
const char * SCORE_BOX_1 = "assets/UI/score_box_1.png";
const char * SCORE_BOX_2 = "assets/UI/score_box_2.png";


// CONSTANTES DE PROPRIEDADE PARA OBJETOS DO CENÁRIO
const int SCREEN_H = 600;    // altura da tela
const int SCREEN_W = 800;    // comprimento da tela
const int HEIGHT_REFFERENCE = SCREEN_H - 204;

// CONFIGURAÇÃO DO RNG PARA OS CANOS
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 384);

// VARIÁVEIS EXTRAS
    int random_offset;                                                      // Offset do cano a ser spawnado
    bool golden_factor;                                                     // Característica se o cano é dourado ou não
    float score;
    float maxscore = 0;
    float dif;                                                              // Float que faz as instruções variarem de tamanho
    bool going_up;                                                          // Bool que controla se o dif aumenta ou diminui
    int PIPE_SPACE = 160;                                                   // Espaçamento entre os canos
    float PIPE_INITIAL_SPEED = -2.5;                                        // Velocidade atual dos canos
    float PIPE_SPEED_MAX = -8;                                              // Velocidade máxima dos canos
    float PIPE_SPEED_INCREASE = -0.02;                                      // Aumento da velocidade dos canos a cada 10 pontos
    int BIRD_JUMP_VEL = -10;                                                // Velocidade do pulo do pássaro
    int BIRD_MAX_UP_VEL = -16;                                              // Velocidade máxima de subida do pássaro
    int BIRD_MAX_DOWN_VEL = 15;                                             // Velocidade máxima de descida do pássaro
    bool death_screen_animation = false;                                    // Bool que controla se o menu de morte está em animação
    bool points_animation = false;                                          // Bool que controla se a pontuação está em animação
    bool best_score_animation = false;                                      // Bool que controla a animação de mostrar o recorde
    bool new_best = false;                                                  // Bool que controla se o jogador fez um novo recorde
    bool play_record_audio = false;                                         // Bool que controla se o áudio de novo recorde deve ser tocado
    bool bird_animation = false;                                            // Bool que controla se o passaro está em animação
    float animation_speed=0;                                                // Float que define quando tem que passar o frame de animação
    int sprite_now=0;                                                       // Int que guarda em que sprite o passaro esta
    int frames_per_point;                                                   // Define a velocidade da animação de pontos
    int frame_count;                                                        // Contagem de frames para a animação dos pontos
    int score_displayed = 0;                                                // Monitora a pontuação que está sendo mostrada
    int c = 0, d = 0, u = 0;                                                // Índices para o sprite da pontuação

    // Construtor
    Game_Loop::Game_Loop(){ 
        // Inicialização dos bitmaps dos objetos do jogo
        ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
        ALLEGRO_FONT *pixel_sans = al_load_ttf_font(PSANS_FONT_FILEPATH, 20, 0);
        pipe_sprite = al_load_bitmap(PIPE_SPRITE);
        golden_pipe_sprite = al_load_bitmap(GOLDEN_PIPE_SPRITE);
        mountain_sprite_1 = al_load_bitmap(MOUNTAIN_SPRITE_1);
        mountain_sprite_2 = al_load_bitmap(MOUNTAIN_SPRITE_2);
        mountain_sprite_3 = al_load_bitmap(MOUNTAIN_SPRITE_3);
        grass_sprite = al_load_bitmap(GRASS_SPRITE);
        instruções_sprite = al_load_bitmap(INSTRUÇÕES_SPRITE);
        score_sprite = al_load_bitmap(SCORE_SPRITE);
        background = al_load_bitmap(BACKGROUND);
        death_screen_frame = al_load_bitmap(DEATH_SCREEN_FRAME);
        best_score_text = al_load_bitmap(BEST_SCORE_TEXT);
        new_best_text = al_load_bitmap(NEW_BEST_TEXT);
        max_score = al_load_bitmap(MAX_SCORE);                 
        score_now = al_load_bitmap(SCORE_NOW);                 
        paused_text = al_load_bitmap(PAUSED);
        score_box_1 = al_load_bitmap(SCORE_BOX_1);
        score_box_2 = al_load_bitmap(SCORE_BOX_2);
        for (int i = 0; i < 2; i++)
            achievements_button_sprite[i] = al_load_bitmap(ACHIEVEMENTS_BUTTON_SPRITE[i]);
        for (int i = 0; i < 2; i++)
            back_button_sprite[i] = al_load_bitmap(BACK_BUTTON_SPRITE[i]);
        for (int i = 0; i < 2; i++)
            settings_button_sprite[i] = al_load_bitmap(SETTINGS_BUTTON_SPRITE[i]);
        for (int i = 0; i < 2; i++)
            home_sprite[i] = al_load_bitmap(HOME_SPRITE[i]);
        for (int i = 0; i < 10; i++)
            numbers_sprites[i] = al_load_bitmap(NUMBERS_SPRITES[i]);
        for (int i = 0; i < 6; i++)
            bird_animation_sprite[i] = al_load_bitmap(BIRD_SPRITE[i]);
        for (int i = 0; i < 4; i++)
            sound_button_sprite[i] = al_load_bitmap(SOUND_BUTTON_SPRITE[i]);
        for (int i = 0; i < 4; i++)
            pause_button_sprite[i] = al_load_bitmap(PAUSE_BUTTON_SPRITE[i]);
        for (int i = 0; i < 2; i++)
            tryagain_sprite[i] = al_load_bitmap(TRY_AGAIN_BUTTON_SPRITE[i]);

        // Inicialização dos sons
        al_reserve_samples(5);

        flap_sound = al_load_sample("assets/audio/flap.wav");
        score_sound = al_load_sample("assets/audio/point.wav");
        golden_score_sound = al_load_sample("assets/audio/gold_point.wav");
        // death_sound = al_load_sample("assets/audio/death.wav");
        death_screen_point_sound = al_load_sample("assets/audio/death_screen_point_up.wav");
        high_score_sound = al_load_sample("assets/audio/high_score.wav");
            
        // Criação do pássaro e inserção no vetor de objetos
        birdo=new bird_object(SCREEN_W/2, SCREEN_H/2, al_get_bitmap_width(bird_animation_sprite[0]), 
        al_get_bitmap_height(bird_animation_sprite[0]), bird_animation_sprite[0], BIRD_MAX_UP_VEL,
        BIRD_MAX_DOWN_VEL, BIRD_JUMP_VEL); 

        //Criação das montanhas
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*3/2-1, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*5/2-2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*7/2-3, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*3/2-1, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*5/2-2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*7/2-3, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*3/2-1, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*5/2-2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*7/2-3, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*3/2-1, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*5/2-2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*7/2-3, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
    
        // Criação das imagens
        images.push_back(new image(death_screen_frame, SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2-80, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+80, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(paused_text,SCREEN_W/2,SCREEN_H/2));
        images.push_back(new image(score_box_1,al_get_bitmap_width(score_box_1)*0.66/2+7,SCREEN_H-al_get_bitmap_height(max_score)+5));
        images.push_back(new image(score_box_2,SCREEN_W-(al_get_bitmap_width(score_box_2)*0.66/2+7),SCREEN_H+100));
        images.push_back(new image(best_score_text, SCREEN_W/2, SCREEN_H/2));
        images.push_back(new image(new_best_text, SCREEN_W/2, SCREEN_H/2));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+56, SCREEN_H/2-150));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+96, SCREEN_H/2-150));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+136, SCREEN_H/2-150));


        // Criação dos botões
        buttons.push_back(new moving_button(SCREEN_W-64, -40, pause_button_sprite[0]));     
        buttons.push_back(new moving_button(SCREEN_W/2-126, 60, settings_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2-42, 60, sound_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2+42, 60, achievements_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2+126, 60, home_sprite[0]));  
        buttons.push_back(new moving_button(SCREEN_W/2,SCREEN_H/2+80, instruções_sprite));
        buttons.push_back(new moving_button(SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)+168, tryagain_sprite[0]));
        
        dif = 0;
        going_up=true;
    };               
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Destrutor
    Game_Loop::~Game_Loop() {
        // Deletar os bitmaps dos objetos do jogo
        al_destroy_font(pixel_sans);
        al_destroy_bitmap(pipe_sprite);
        al_destroy_bitmap(golden_pipe_sprite);
        al_destroy_bitmap(mountain_sprite_1);
        al_destroy_bitmap(mountain_sprite_2);
        al_destroy_bitmap(mountain_sprite_3);
        al_destroy_bitmap(grass_sprite);
        al_destroy_bitmap(instruções_sprite);
        al_destroy_bitmap(score_sprite);
        al_destroy_bitmap(death_screen_frame);
        for (int i = 0; i < 2; i++) 
            al_destroy_bitmap(achievements_button_sprite[i]);
        for (int i = 0; i < 2; i++) 
            al_destroy_bitmap(back_button_sprite[i]);
            for (int i = 0; i < 2; i++) 
            al_destroy_bitmap(settings_button_sprite[i]);
        for (int i = 0; i < 9; i++) 
            al_destroy_bitmap(numbers_sprites[i]);
        for (int i = 0; i < 4; i++) 
            al_destroy_bitmap(bird_animation_sprite[i]);
        for (int i = 0; i < 4; i++) 
            al_destroy_bitmap(sound_button_sprite[i]);
        for (int i = 0; i < 4; i++)
            al_destroy_bitmap(pause_button_sprite[i]);
        for (int i = 0; i < 2; i++)
            al_destroy_bitmap(tryagain_sprite[i]);

        // Deletar mixer e áudios
        al_destroy_sample(flap_sound);
        al_destroy_sample(score_sound); 
        al_destroy_sample(golden_score_sound);
        // al_destroy_sample(death_sound);
        al_destroy_sample(death_screen_point_sound);
        al_destroy_sample(high_score_sound);

        // Deletar os objetos do jogo
        delete birdo;
        for (pipe_object* obj : pipe_objects) {
            delete obj; // Deleta cada objeto do jogo
        }
        pipe_objects.clear(); // Limpa o vetor de objetos do jogo
        for (background_object* bgo : background_objects_0) {
            delete bgo; // Deleta cada objeto de background
        }
        background_objects_0.clear(); // Limpa o vetor de objetos de background
        for (background_object* bgo : background_objects_1) {
            delete bgo; // Deleta cada objeto de background
        }
        background_objects_1.clear(); // Limpa o vetor de objetos de background
        for (background_object* bgo : background_objects_2) {
            delete bgo; // Deleta cada objeto de background
        }
        background_objects_2.clear(); // Limpa o vetor de objetos de background
        for (background_object* bgo : background_objects_3) {
            delete bgo; // Deleta cada objeto de background
        }
        background_objects_3.clear(); // Limpa o vetor de objetos de background

        // Deletar os botões
        for (moving_button* btn : buttons) {
            delete btn; // Deleta cada botão
        }
        buttons.clear(); // Limpa o vetor de botões

        // Deletar as imagens
        for (image* img : images) {
            delete img;
        }
        images.clear();
    }

    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Game_Loop::commands(unsigned char key[], bool mouse_is_down, bool &mouse_just_released, int mouse_update_x, int mouse_update_y, states* state) {

        // Processamento dos botões
        if(buttons.size() > 0) {
            // Mouse acabou de ser solto
            if(mouse_just_released) {
                if(!dead){
                    if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(0)->is_pressed()) {
                        paused = !paused;   // Alterna o estado de pausa
                        for(int i=1; i<5; i++)
                            buttons.at(i)->set_velocity(0,0);
                        buttons.at(0)->set_pressed(false);
                    }
                }
                if(paused||death_menu||!playing){
                    if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(1)->is_pressed()) {
                        state->game_loop_screen = false;
                        state->settings_screen = true;
                        buttons.at(1)->set_pressed(false);
                    }
                    if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(2)->is_pressed()) {
                        sound = !sound;
                        buttons.at(2)->set_pressed(false);
                    }
                    if(buttons.at(3)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(3)->is_pressed()) {
                        buttons.at(3)->set_bitmap(achievements_button_sprite[0]);
                        // Vá para a tela de achievements se clicar em "Achievements"
                        state->game_loop_screen = false;
                        state->achievements_screen = true;
                        buttons.at(3)->set_pressed(false);
                        this->reset_game();
                    }
                    if(buttons.at(4)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(4)->is_pressed()) {
                        state->game_loop_screen=false;
                        state->home_screen=true;
                        buttons.at(4)->set_pressed(false);
                        this->reset_game();
                        return;
                    }
                }
                /*if(buttons.at(5)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(5)->is_pressed()) {
                    buttons.at(5)->set_pressed(false);
                }
                */ 
                if(buttons.at(6)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(6)->is_pressed()) {
                    buttons.at(6)->set_pressed(false);
                    // Reinicia o jogo
                    this->reset_game();
                }
            }
            
            // Mouse está pressionado
            if(mouse_is_down) {
                // Botão de pause
                if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y)) {
                    buttons.at(0)->set_pressed(true);
                    switch(paused) {
                        case true: {
                            buttons.at(0)->set_bitmap(pause_button_sprite[3]);
                            break;
                        }
                        case false: {
                            buttons.at(0)->set_bitmap(pause_button_sprite[2]);
                            break;
                        }
                    }
                }

                // Botão de play again do death menu
                if (death_menu) {
                    if(buttons.at(6)->contains_click(mouse_update_x, mouse_update_y)) {
                        buttons.at(6)->set_pressed(true);
                        buttons.at(6)->set_bitmap(tryagain_sprite[1]);
                    }
                }

                // Outros botões do menu
                if(paused||death_menu||!playing){
                    if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y)) {
                        buttons.at(1)->set_pressed(true);
                        buttons.at(1)->set_bitmap(settings_button_sprite[1]);
                    }
                    if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y)) {
                        buttons.at(2)->set_pressed(true);
                        switch(sound){
                            case true:
                                buttons.at(2)->set_bitmap(sound_button_sprite[2]);
                                break;
                            case false:
                                buttons.at(2)->set_bitmap(sound_button_sprite[3]);
                                break;
                        }
                    }
                    if(buttons.at(3)->contains_click(mouse_update_x, mouse_update_y)) {
                        buttons.at(3)->set_pressed(true);
                        buttons.at(3)->set_bitmap(achievements_button_sprite[1]);
                    }
                    if(buttons.at(4)->contains_click(mouse_update_x, mouse_update_y)) {
                        buttons.at(4)->set_pressed(true);
                        buttons.at(4)->set_bitmap(home_sprite[1]);
                    }
                }
                
            }

            // Botão do mouse está solto
            else {
                switch(paused) {
                    case true: {
                        buttons.at(0)->set_bitmap(pause_button_sprite[1]);
                        break;
                    }
                    case false: {
                        buttons.at(0)->set_bitmap(pause_button_sprite[0]);
                        break;
                    }
                }
                buttons.at(1)->set_bitmap(settings_button_sprite[0]);
                switch(sound){
                    case true:
                        buttons.at(2)->set_bitmap(sound_button_sprite[0]);
                        break;
                    case false:
                        buttons.at(2)->set_bitmap(sound_button_sprite[1]);
                        break;
                }
                buttons.at(3)->set_bitmap(achievements_button_sprite[0]);
                buttons.at(4)->set_bitmap(home_sprite[0]);
                buttons.at(6)->set_bitmap(tryagain_sprite[0]);
            }
        }

        // Processamento das teclas
        if(key[ALLEGRO_KEY_SPACE] == 3) { 
            if(!paused){
                if(!playing && !dead) {                        // Se o jogo não está em andamento e não está morto
                    playing = true;                            // Inicia o jogo
                    birdo->Set_y_acelleration(0.7); // Define a aceleração da gravidade
                } 
                if(playing && !dead) {                         // Se o jogo está em andamento e não está morto
                    birdo->Jump();                // Faz o pássaro pular
                    if(sound) {
                        al_play_sample(flap_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // Toca o som do flap
                    }
                    sprite_now=0;
                    bird_animation = true;
                }
                if(!playing && death_menu && !death_screen_animation){
                    dead = false;
                    death_menu = false;
                    this->reset_game();
                }
                //if()
            }
        }
        else if(key[ALLEGRO_KEY_ESCAPE] == 3) {
            if(playing && !dead) {
                paused = !paused;   // Alterna o estado de pausa
            }
        }

        if(mouse_just_released) {
            mouse_just_released = false; // Reseta o mouse just released
        }

        // "Marca" que as teclas apertadas já foram vistas
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
            key[i] &= 1;
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Game_Loop::update(){
        ////////////////////////////////////////
        //Ver posições e criar/deletar objetos//
        ////////////////////////////////////////

        ///////CANOS////////
        //Criando os canos//
        if (playing &&(pipe_objects.size()==0 || pipe_objects.at(pipe_objects.size()-1)->Get_position()->x<SCREEN_W-100)){    // Adiciona o primeiro cano se não houver nenhum ou se o último cano estiver à distância adequada (100 + 250)
            random_offset = dis(gen);                               // Determina o offset do cano a ser spawnado
            golden_factor = dis(gen) <= 3;
            int spawn_x = SCREEN_W + 250;                           // Coordenada X de spawn dos canos (fora da tela)
            int spawn_y = (SCREEN_H / 2) - 108 - random_offset;     // Coordenada Y de referência para spawn dos canos

            if (!golden_factor) {
                pipe_objects.push_back(new pipe_object(spawn_x, spawn_y, al_get_bitmap_width(pipe_sprite), 
                al_get_bitmap_height(pipe_sprite), pipe_sprite, false));                                           // Instanciação do cano superior
                pipe_objects.push_back(new pipe_object(spawn_x, spawn_y+al_get_bitmap_height(pipe_sprite)+PIPE_SPACE, 
                al_get_bitmap_width(pipe_sprite), al_get_bitmap_height(pipe_sprite), pipe_sprite, false));         // Instanciação do cano inferior
            }
            else {
                pipe_objects.push_back(new pipe_object(spawn_x, spawn_y, al_get_bitmap_width(pipe_sprite), 
                al_get_bitmap_height(pipe_sprite), golden_pipe_sprite, true));                                           // Instanciação do cano superior
                pipe_objects.push_back(new pipe_object(spawn_x, spawn_y+al_get_bitmap_height(pipe_sprite)+PIPE_SPACE, 
                al_get_bitmap_width(pipe_sprite), al_get_bitmap_height(pipe_sprite), golden_pipe_sprite, true));         // Instanciação do cano inferior
            }
                    
            if (pipe_objects.at(1)->Get_x_speed() > PIPE_SPEED_MAX) {
                pipe_objects.at(1)->Set_x_speed(pipe_objects.at(1)->Get_x_speed()+PIPE_SPEED_INCREASE);     // Se a velocidade do cano for maior que o máximo, reduza ela
            }
            int PIPE_SPEED=pipe_objects.at(1)->Get_x_speed();
        }    
        
        //Deletando os canos//
        for (int i = 0; i < pipe_objects.size(); i++) {
            if(pipe_objects.at(i)->Get_position()->x < -75) { // Se o cano estiver fora da tela
                delete pipe_objects.at(i); // Deleta o cano
                pipe_objects.erase(pipe_objects.begin() + i); // Remove o cano do vetor
                i--;
            }
        }

        //Verificando pontuação//
        for (int i = 0; i < pipe_objects.size(); i++) {
            if(pipe_objects.at(i)->Get_position()->x<=SCREEN_W/2){
                if(!pipe_objects.at(i)->is_scored()) {
                    // Veririficação se é dourado (cano dourado vale 3)
                    if(pipe_objects.at(i)->is_golden()) {
                        if(sound) {
                            al_play_sample(golden_score_sound, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                        score=score+1.5;
                    }
                    else {
                        if(sound) {
                            al_play_sample(score_sound, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                        score=score+0.5;
                    }
                    pipe_objects.at(i)->Set_score(true);
                }
            }else break;
        }
        if(score>maxscore)
        maxscore=score;
        
        ///////Montanhas////////
        //Deletando e Criando as montanhas//
        if (background_objects_1.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_1)/2){
            delete background_objects_1.at(0); 
            background_objects_1.erase(background_objects_1.begin());   
            background_objects_1.push_back(new background_object(background_objects_1.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_1)-1, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        }
        if (background_objects_2.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_2)/2){
            delete background_objects_2.at(0); 
            background_objects_2.erase(background_objects_2.begin());
            background_objects_2.push_back(new background_object(background_objects_2.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_2)-1, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        }
        if (background_objects_3.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_3)/2){
            delete background_objects_3.at(0); 
            background_objects_3.erase(background_objects_3.begin());
            background_objects_3.push_back(new background_object(background_objects_3.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_3)-1, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));
        } 

        ////////GRAMA///////////
        //Deletando e criando as gramas//
        if (background_objects_0.at(0)->Get_position()->x<-al_get_bitmap_width(grass_sprite)/2){
            delete background_objects_0.at(0); 
            background_objects_0.erase(background_objects_0.begin());
            background_objects_0.push_back(new background_object(background_objects_0.back()->Get_position()->x+al_get_bitmap_width(grass_sprite)-1, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        }

        ///////PASSARINHO////////
        // Verifica se o pássaro caiu no chão
        if(birdo->Get_position()->y>SCREEN_H&&!dead){
            dead = true;
            paused = false;
            birdo->Jump();
            birdo->Set_x_speed(1.5*pipe_objects.at(0)->Get_x_speed());
        }

        // Verifica se o pássaro bateu em algum cano
        if(!dead){
            for (int i = 0; i < pipe_objects.size(); i++) {
                if(birdo->is_colliding(pipe_objects.at(i))){
                    dead = true;
                    paused = false;
                    birdo->Jump();
                    birdo->Set_x_speed(1.7*pipe_objects.at(0)->Get_x_speed());
                    break;
                }
            }
        }

        // Setando death_menu para true caso ele caia de verdade
        if(birdo->Get_position()->y>SCREEN_H+50 && dead && !death_menu){
            death_menu = true;
            playing = false;
            death_screen_animation = true;

            // Movendo os botões de achievements (3) e home (4) para a tela de morte
            buttons.at(3)->set_x(SCREEN_W/2 + 115);
            buttons.at(3)->set_y(SCREEN_H+al_get_bitmap_height(death_screen_frame)+168);
            buttons.at(4)->set_x(SCREEN_W/2 - 115);
            buttons.at(4)->set_y(SCREEN_H+al_get_bitmap_height(death_screen_frame)+168);

            // Calculando qual vai ser a velocidade da animação dos pontos
            frames_per_point = ceil(5/ceil((score+1)/20));
            frame_count = frames_per_point - 1;
        }

        //Animação passarinho
        if(bird_animation&&!paused){
            if(animation_speed>=3){
                if(sprite_now==5){
                    sprite_now=0;
                    birdo->set_bitmap(bird_animation_sprite[sprite_now]);
                    bird_animation = false;
                }else{
                    sprite_now++;
                    birdo->set_bitmap(bird_animation_sprite[sprite_now]);
                }
                animation_speed=0;
            }else{
                animation_speed++;
            }
        }


        //////////BOTÕES///////////////
        //Pause//
        if (!death_menu) {
            if (buttons.at(0)->get_velocity_y()+buttons.at(0)->get_y()>=60) {             //Delimitadores de posição
                buttons.at(0)->set_y(60);
                buttons.at(0)->set_acceleration(0,0);
                buttons.at(0)->set_velocity(0,0);
            }
            if (buttons.at(0)->get_velocity_y()+buttons.at(0)->get_y()<=-100) {
                buttons.at(0)->set_y(-100);
                buttons.at(0)->set_acceleration(0,0);
                buttons.at(0)->set_velocity(0,0);
            }
            if (playing&&!dead&&buttons.at(0)->get_y()<60) {                               //Movimentando o botão
                buttons.at(0)->set_acceleration(0,3);   
            }
            else if (dead&&buttons.at(0)->get_y()>-100) {
                buttons.at(0)->set_acceleration(0,-3);
            }
            else {
                buttons.at(0)->set_acceleration(0,0);
                buttons.at(0)->set_velocity(0,0);
            }
        }
        

        //Carregando os botões do pause//
        if(!death_menu) {
            for(int i=1; i<5; i++){
                if(buttons.at(i)->get_velocity_y()+buttons.at(i)->get_y()>=60){             //Delimitadores de posição
                    buttons.at(i)->set_y(60);
                    buttons.at(i)->set_acceleration(0,0);
                    buttons.at(i)->set_velocity(0,0);
                }
                if(buttons.at(i)->get_velocity_y()+buttons.at(i)->get_y()<=-100){
                    buttons.at(i)->set_y(-40);
                    buttons.at(i)->set_acceleration(0,0);
                    buttons.at(i)->set_velocity(0,0);
                }
                if((paused||(!playing&&!dead))&&buttons.at(i)->get_y()<60){                                    //Movimentando o botão
                    buttons.at(i)->set_acceleration(0,5);
                }else if((!paused&&(playing||dead))&&buttons.at(i)->get_y()>-40){
                    buttons.at(i)->set_acceleration(0,-4);
                }else{
                buttons.at(i)->set_acceleration(0,0);
                buttons.at(i)->set_velocity(0,0);
                }
            }
        }

        //////////MENU DE MORTE///////////////
        if(death_menu && images.size() > 0) {
            // Animação da tela de morte subindo
            if(death_screen_animation) {
                // Velocidade padrão para todos os objetos da tela de morte
                float vel = (SCREEN_H/2 - images.at(0)->get_y())/10 - 5;
                for (int i = 0; i <= 3; i++) {
                    images.at(i)->set_velocity(0, vel);
                }

                for(moving_button* btn : buttons) {
                    btn->set_acceleration(0, 0);
                }

                buttons.at(3)->set_velocity(0, vel);
                buttons.at(4)->set_velocity(0, vel);
                buttons.at(6)->set_velocity(0, vel);

                if(images.at(0)->get_y() <= SCREEN_H/2)     // Frame da tela de morte chegou/passou do meio da tela
                {
                    death_screen_animation = false;
                    points_animation = true;

                    for (int j = 0; j <= 3; j++) {
                        images.at(j)->set_acceleration(0, 0);
                        images.at(j)->set_velocity(0, 0);
                        images.at(j)->set_position_y(SCREEN_H/2);
                    }

                    buttons.at(3)->set_velocity(0, 0);
                    buttons.at(3)->set_y(SCREEN_H/2+168);
                    buttons.at(4)->set_velocity(0, 0);
                    buttons.at(4)->set_y(SCREEN_H/2+168);
                    buttons.at(6)->set_velocity(0, 0);
                    buttons.at(6)->set_y(SCREEN_H/2+168);
                }
            }

            // Animação mostrando os pontos
            else if(points_animation) {

                if (score_displayed  == score)          // Pontuação mostrada chegou na pontuação de fato, pare a animação
                {
                    points_animation = false;
                    best_score_animation = true;
                    play_record_audio = true;
                    for (int i = 1; i <= 3; i++) {
                        images.at(i)->set_position_y(SCREEN_H/2);
                    }
                }
                
                if(frame_count == frames_per_point)     // Aumenta 1 na pontuação mostrada
                {
                    u++;
                    if (u == 10) {
                        u = 0;
                        d++;
                    }
                    if (d == 10) {
                        d = 0;
                        c++;
                    }
                    if (c == 10) {
                        c = 0;
                    }
                    images.at(1)->set_bitmap(numbers_sprites[c]);
                    images.at(2)->set_bitmap(numbers_sprites[d]);
                    images.at(3)->set_bitmap(numbers_sprites[u]);

                    if(sound) {
                        al_play_sample(death_screen_point_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }

                    score_displayed++;

                    frame_count = 0;
                }
                
                frame_count++;
            }

            else if(best_score_animation) {
                if(score >= maxscore) {
                    new_best = true;            // Se a pontuação atual é maior que a máxima, marca como novo recorde
                }
                else {
                    new_best = false;           // Se não, marca como não é novo recorde
                }
                if(play_record_audio) {
                    if(sound) {
                        al_play_sample(high_score_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    play_record_audio = false;
                }
            }
        }

        //Instruções//
        if (going_up) {
        dif += 0.0008;
        if (dif >= 0.03) going_up = false;
        } else {
        dif -= 0.0008;
        if (dif <= 0.01) going_up = true;
        }

        /////////////////Score////////////////
        //Movimentando e Tirando score da tela//
        if(playing&&!dead&&images.at(12)->get_y()>SCREEN_H-al_get_bitmap_height(max_score)+5){
            images.at(12)->set_acceleration(0,-3);
            if(images.at(12)->get_y()+images.at(12)->get_velocity_y()<SCREEN_H-al_get_bitmap_height(max_score)+5)
                images.at(12)->set_position_y(SCREEN_H-al_get_bitmap_height(max_score)/2+5);
        }else if(dead&&images.at(12)->get_y()<SCREEN_H+100){
            images.at(12)->set_acceleration(0,3);
            if(images.at(12)->get_y()+images.at(12)->get_velocity_y()>SCREEN_H+100)
                images.at(12)->set_position_y(SCREEN_H+100);
        }else{
            images.at(12)->set_velocity(0,0);
            images.at(12)->set_acceleration(0,0);
        }

        //Tirando o max score da tela//
        if(playing&&images.at(11)->get_y()<SCREEN_H+100){
            images.at(11)->set_acceleration(0,3);
            if(images.at(11)->get_y()+images.at(11)->get_velocity_y()>SCREEN_H+100)
                images.at(11)->set_position_y(SCREEN_H+100);
        }else{
            images.at(11)->set_velocity(0,0);
            images.at(11)->set_acceleration(0,0);
        }
        

        ////////////////////////////////////////
        //////Atualiza os objetos do jogo///////
        ////////////////////////////////////////
        if (!paused&&!death_menu) {
            birdo->Update(SCREEN_W, SCREEN_H); // Atualiza o pássaro
            if(!dead&&playing){
                for (int i = 0; i < pipe_objects.size(); i++){
                    pipe_objects.at(i)->Update(SCREEN_W, SCREEN_H);
                }
                background_objects_1.at(0)->Set_standard_speed(pipe_objects.at(1)->Get_x_speed());
                for (background_object* bgo_3 : background_objects_3) {
                    bgo_3->Update(SCREEN_W, SCREEN_H, 0.1); // Atualiza as montanhas de trás
                }
                for (background_object* bgo_2 : background_objects_2) {
                    bgo_2->Update(SCREEN_W, SCREEN_H, 0.2); // Atualiza as montanhas do meio
                }
                for (background_object* bgo_1 : background_objects_1) {
                    bgo_1->Update(SCREEN_W, SCREEN_H, 0.3); // Atualiza as montanhas da frente
                }
                for (background_object* bgo_0 : background_objects_0) {
                    bgo_0->Update(SCREEN_W, SCREEN_H, 0.4); // Atualiza a grama
                }
            }
        }
        for(moving_button* btn : buttons){
            btn->Update();
        }

        for(image* img : images) {
            img->Update();
        }
        
        //If menu

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Método que desenha os objetos do jogo na tela
    void Game_Loop::draw(){
        al_draw_bitmap(background, 0, 0, 0);
        // Desenha os objetos de background
        for (background_object* bgo_3 : background_objects_3) {
            bgo_3->Draw(1);
        }
        for (background_object* bgo_2 : background_objects_2) {
            bgo_2->Draw(1);
        }
        for (background_object* bgo_1 : background_objects_1) {
            bgo_1->Draw(1);
        }
        for (background_object* bgo_0 : background_objects_0) {
            bgo_0->Draw(1);
        }

        // Desenha os objetos do jogo
        for (int i = 0; i < pipe_objects.size(); i++) {
            pipe_objects.at(i)->Draw(1);
        }
        if(dead&&!paused){
            birdo->Draw_spin(0.1*pipe_objects.at(0)->Get_x_speed());
        }else if(dead&&paused){
            birdo->Draw_spin(0);
        }else{
            birdo->Draw(1);
        }

        // Desenha o menu de morte
        if(death_menu && images.size() > 0) {
            // Frame
            images.at(0)->Draw();
            // Pontos
            for (int i = 1; i <= 3; i++) {
                images.at(i)->Draw(2);
            }
            // Botões
            buttons.at(3)->draw();
            buttons.at(4)->draw();
            buttons.at(6)->draw();
            // Texto de novo recorde
            if(best_score_animation && new_best) {
                images.at(14)->Draw(1.33);
            }
            else if(best_score_animation && !new_best) {
                images.at(13)->Draw(1.33);
                if(maxscore < 10) {
                    images.at(15)->set_bitmap(numbers_sprites[(int)maxscore]);
                    images.at(15)->Draw(1);
                }
                else if(maxscore < 100) {
                    images.at(15)->set_bitmap(numbers_sprites[(int)maxscore/10]);
                    images.at(16)->set_bitmap(numbers_sprites[(int)maxscore%10]);
                    images.at(15)->Draw(1);
                    images.at(16)->Draw(1);
                }
                else {
                    images.at(15)->set_bitmap(numbers_sprites[(int)maxscore%100]);
                    images.at(16)->set_bitmap(numbers_sprites[(int)maxscore%100/10]);
                    images.at(17)->set_bitmap(numbers_sprites[(int)maxscore%10]);
                    images.at(15)->Draw(1);
                    images.at(16)->Draw(1);
                    images.at(17)->Draw(1);
                }
            }
        }

        // Desenha os Scores
        images.at(11)->Draw(0.666);
        images.at(12)->Draw(0.666);
        if(score>999)
        score=999;
        for (int a = 4; a<7 ;a++)
            images.at(a)->set_position_y(images.at(12)->get_y());
        if((int)score/100==0&&(int)score/10==0){
            images.at(6)->set_bitmap(numbers_sprites[(int)score]);
            images.at(6)->set_position_x(images.at(12)->get_x()+50);
            images.at(6)->Draw(0.5);
        }else if((int)score/100==0&&(int)score/10!=0){
            images.at(5)->set_bitmap(numbers_sprites[(int)score/10]);
            images.at(5)->set_position_x(images.at(12)->get_x()+40);
            images.at(5)->Draw(0.5);
            images.at(6)->set_bitmap(numbers_sprites[(int)score%10]);
            images.at(6)->set_position_x(images.at(12)->get_x()+60);
            images.at(6)->Draw(0.5);
        }else{
            images.at(4)->set_bitmap(numbers_sprites[(int)score/100]);
            images.at(4)->set_position_x(images.at(12)->get_x()+30);
            images.at(4)->Draw(0.5);
            images.at(5)->set_bitmap(numbers_sprites[(int)score%100/10]);
            images.at(5)->set_position_x(images.at(12)->get_x()+50);
            images.at(5)->Draw(0.5);
            images.at(6)->set_bitmap(numbers_sprites[(int)score%10]);
            images.at(6)->set_position_x(images.at(12)->get_x()+70);
            images.at(6)->Draw(0.5);
        }
    
        for (int a = 7; a<10 ;a++)
            images.at(a)->set_position_y(images.at(11)->get_y());
        if((int)maxscore/100==0&&(int)maxscore/10==0){
            images.at(9)->set_bitmap(numbers_sprites[(int)maxscore]);
            images.at(9)->set_position_x(images.at(11)->get_x()+85);
            images.at(9)->Draw(0.5);
        }else if((int)maxscore/100==0&&(int)maxscore/10!=0){
            images.at(8)->set_bitmap(numbers_sprites[(int)maxscore/10]);
            images.at(8)->set_position_x(images.at(11)->get_x()+75);
            images.at(8)->Draw(0.5);
            images.at(9)->set_bitmap(numbers_sprites[(int)maxscore%10]);
            images.at(9)->set_position_x(images.at(11)->get_x()+95);
            images.at(9)->Draw(0.5);
        }else{
            images.at(7)->set_bitmap(numbers_sprites[(int)maxscore/100]);
            images.at(7)->set_position_x(images.at(11)->get_x()+65);
            images.at(7)->Draw(0.5);
            images.at(8)->set_bitmap(numbers_sprites[(int)maxscore%100/10]);
            images.at(8)->set_position_x(images.at(11)->get_x()+85);
            images.at(8)->Draw(0.5);
            images.at(9)->set_bitmap(numbers_sprites[(int)maxscore%10]);
            images.at(9)->set_position_x(images.at(11)->get_x()+105);
            images.at(9)->Draw(0.5);
        }
        

        // Desenha o texto de pause
        if(paused)
        images.at(10)->Draw();

        // Desenha os botões
        if(!death_menu) {
            for (int i = 0; i <= 4; i++) {
                buttons.at(i)->draw();
            }
            if(!playing&&!dead) {
                buttons.at(5)->draw(0.22+dif);
            }
        }
        /*             SE FOR USAR ESSE É SO TIRAR O COMENTARIO E BOTAR COMENTARIO NO OUTRO
        if(playing) {            
            // Cálculo dos dígitos
            int unidades = (int)score % 10;
            int dezenas = (int)(score / 10) % 10;
            int centenas = (int)(score / 100) % 10;

            // Parâmetros de layout
            int digit_width = al_get_bitmap_width(numbers_sprites[0]); // Largura de cada número
            int total_digits = (score >= 100) ? 3 : (score >= 10) ? 2 : 1;
            int total_width = digit_width * total_digits;

            int start_x = (SCREEN_W / 2) - (total_width / 2); // Centraliza no meio da tela
            int y = SCREEN_H / 2 - 225; // Mesma altura que você estava usando para o texto

            // Desenha os dígitos corretamente posicionados
            if (total_digits == 3) {
                al_draw_bitmap(numbers_sprites[centenas], start_x, y, 0);
                al_draw_bitmap(numbers_sprites[dezenas], start_x + digit_width, y, 0);
                al_draw_bitmap(numbers_sprites[unidades], start_x + 2 * digit_width, y, 0);
            }
            else if (total_digits == 2) {
                al_draw_bitmap(numbers_sprites[dezenas], start_x, y, 0);
                al_draw_bitmap(numbers_sprites[unidades], start_x + digit_width, y, 0);
            }
            else {
                al_draw_bitmap(numbers_sprites[unidades], start_x, y, 0);
            }
            
        }*/
        al_flip_display();
    }      

    // Método que reseta o jogo, recriando os objetos e o cenário
    void Game_Loop::reset_game()
    {   score = 0;
        if(pipe_objects.size()>0)
        pipe_objects.at(0)->Set_x_speed(-2.5);
        pipe_objects.clear();
        delete birdo;
        birdo = new bird_object(SCREEN_W/2, SCREEN_H/2, al_get_bitmap_width(bird_animation_sprite[0]), 
        al_get_bitmap_height(bird_animation_sprite[0]), bird_animation_sprite[0], BIRD_MAX_UP_VEL,
        BIRD_MAX_DOWN_VEL, BIRD_JUMP_VEL);
        
        background_objects_0.clear();
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*3/2-1, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*5/2-2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*7/2-3, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.at(0)->Set_standard_speed(0);
        
        background_objects_1.clear();
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*3/2-1, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*5/2-2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*7/2-3, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              

        background_objects_2.clear();
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*3/2-1, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*5/2-2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*7/2-3, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        background_objects_3.clear();
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*3/2-1, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*5/2-2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));                   
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*7/2-3, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));                   
        
        images.clear();
        /*
        0 -> Frame da tela de morte
        1 -> Centenas da pontuação (morte)
        2 -> Dezenas da pontuação (morte)
        3 -> Unidades da pontuação (morte)
        4 -> ?
        5 -> ?
        6 -> ?
        7 -> ?
        8 -> ?
        9 -> ?
        10 -> Texto de pause
        11 -> ?
        12 -> ?
        13 -> Text do best score na tela de morte
        14 -> Texto do new best na tela de morte
        15 -> Dígito 1 da máxima pontuação (tela de morte)
        16 -> Dígito 2 da máxima pontuação (tela de morte)
        17 -> Dígito 3 da máxima pontuação (tela de morte)
        */
        images.push_back(new image(death_screen_frame, SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2-80, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+80, SCREEN_H+al_get_bitmap_height(death_screen_frame)));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,SCREEN_H+100));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(numbers_sprites[0],0,0));
        images.push_back(new image(paused_text,SCREEN_W/2,SCREEN_H/2));
        images.push_back(new image(score_box_1,al_get_bitmap_width(score_box_1)*0.66/2+7,SCREEN_H-al_get_bitmap_height(max_score)+5));
        images.push_back(new image(score_box_2,SCREEN_W-(al_get_bitmap_width(score_box_2)*0.66/2+7),SCREEN_H+100));
        images.push_back(new image(best_score_text, SCREEN_W/2, SCREEN_H/2));
        images.push_back(new image(new_best_text, SCREEN_W/2, SCREEN_H/2));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+56, SCREEN_H/2-150));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+96, SCREEN_H/2-150));
        images.push_back(new image(numbers_sprites[0], SCREEN_W/2+136, SCREEN_H/2-150));

        
        birdo->set_bitmap(bird_animation_sprite[0]);
        bird_animation=false;
        death_screen_animation = false;
        points_animation = false;
        best_score_animation = false;
        new_best = false;

        buttons.clear();
        /*
        0 -> Pause
        1 -> Settings
        2 -> Sound
        3 -> Achievements
        4 -> Home
        5 -> Instruções (???)
        6 -> Play Again
        */
        buttons.push_back(new moving_button(SCREEN_W-64, -40, pause_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2-126, 60, settings_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2-42, 60, sound_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2+42, 60, achievements_button_sprite[0]));
        buttons.push_back(new moving_button(SCREEN_W/2+126, 60, home_sprite[0]));  
        buttons.push_back(new moving_button(SCREEN_W/2,SCREEN_H/2+80, instruções_sprite));
        buttons.push_back(new moving_button(SCREEN_W/2, SCREEN_H+al_get_bitmap_height(death_screen_frame)+168, tryagain_sprite[0]));
        dif=0;
        going_up=true;

        //Resetando variaveis de controle
        playing = false;
        dead = false;
        death_menu = false;
        paused = false;

        // Reset das variáveis da animação de pontuação na tela de morte
        score_displayed = 0;
        c = 0;
        d = 0;
        u = 0;
        
    } 