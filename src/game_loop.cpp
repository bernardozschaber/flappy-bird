#include "game_loop.hpp"
#include "bird_object.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>


// CONSTANTES DE PATH 
const char * ARIAL_FONT_FILEPATH = "assets/fonts/arial.ttf";                                                            // caminho para a fonte arial
const char * PSANS_FONT_FILEPATH = "assets/fonts/pixelify_sans.ttf";                                                    // caminho para a fonte pixelify sans
const char * BIRD_SPRITE[5] = {"assets/bird-1.png","assets/bird-2.png","assets/bird-3.png","assets/bird-2.png","assets/bird-1.png"};                      // bitmap do sprite do pássaro
const char * PIPE_SPRITE = "assets/pipe.png";                                                                     // caminho do sprite do cano
const char * GOLDEN_PIPE_SPRITE = "assets/pipe_golden.png";                                                       // caminho do sprite do cano dourado
const char * MOUNTAIN_SPRITE_1 = "assets/scenario/mountains_1.png";                                                        // caminho das montanhas (da frente)
const char * MOUNTAIN_SPRITE_2 = "assets/scenario/mountains_2.png";                                                        // caminho das montanhas (do meio)
const char * MOUNTAIN_SPRITE_3 = "assets/scenario/mountains_3.png";                                                        // caminho das montanhas (de trás)
const char * GRASS_SPRITE = "assets/scenario/grama.png";                                                                   // caminho da grama
const char * ACHIEVEMENTS_BUTTON_SPRITE = "assets/UI/achievements_button.png";                                       // caminho do botão de conquistas
const char * BACK_BUTTON_SPRITE = "assets/UI/back_button.png";                                                       // caminho do botão de voltar
const char * SETTINGS_BUTTON_SPRITE = "assets/UI/settings_button.png";                                               // caminho do botão de configurações
const char * INSTRUÇÕES_SPRITE = "assets/UI/instruções.png";                                                         // caminho das instruções
const char * SCORE_SPRITE = "assets/UI/score_text.png";                                                                   // caminho da tela de morte
const char * HOME_SPRITE= "assets/UI/home_button.png";                                                                      // caminho do sprite de home
const char * BACKGROUND = "assets/scenario/background.png";                                                                          // caminho do sprite do fundo
const char * NUMBERS_SPRITES[10] = {"assets/UI/num_0.png", "assets/UI/num_1.png", "assets/UI/num_2.png", "assets/UI/num_3.png",  
                                    "assets/UI/num_4.png", "assets/UI/num_5.png", "assets/UI/num_6.png", "assets/UI/num_7.png", 
                                    "assets/UI/num_8.png", "assets/UI/num_9.png"};                                                              // caminho dos números 
const char * SOUND_BUTTON_SPRITE[2] = {"assets/UI/sound_on.png", "assets/UI/sound_off.png"};                            // caminho do botão de som ligado/desligado
const char * PAUSE_BUTTON_SPRITE[2] = {"assets/UI/pause_button.png", "assets/UI/resume_button.png"};                    // caminho do botão de pause/despause

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
    float score;
    int PIPE_SPACE = 160;                                                   // Espaçamento entre os canos
    float PIPE_INITIAL_SPEED = -5;                                          // Velocidade atual dos canos
    float PIPE_SPEED_MAX = -10;                                             // Velocidade máxima dos canos
    float PIPE_SPEED_INCREASE = 0.01;                                       // Aumento da velocidade dos canos a cada 10 pontos
    int BIRD_JUMP_VEL = -15;                                                // Velocidade do pulo do pássaro
    int BIRD_MAX_UP_VEL = -25;                                              // Velocidade máxima de subida do pássaro
    int BIRD_MAX_DOWN_VEL = 20;                                             // Velocidade máxima de descida do pássaro

    // Construtor
    game_loop::game_loop(){ 
        // Inicialização dos bitmaps dos objetos do jogo
        ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
        ALLEGRO_FONT *pixel_sans = al_load_ttf_font(PSANS_FONT_FILEPATH, 20, 0);   
        pipe_sprite = al_load_bitmap(PIPE_SPRITE);
        golden_pipe_sprite = al_load_bitmap(GOLDEN_PIPE_SPRITE);
        mountain_sprite_1 = al_load_bitmap(MOUNTAIN_SPRITE_1);
        mountain_sprite_2 = al_load_bitmap(MOUNTAIN_SPRITE_2);
        mountain_sprite_3 = al_load_bitmap(MOUNTAIN_SPRITE_3);
        grass_sprite = al_load_bitmap(GRASS_SPRITE);
        achievements_button_sprite = al_load_bitmap(ACHIEVEMENTS_BUTTON_SPRITE);
        back_button_sprite = al_load_bitmap(BACK_BUTTON_SPRITE);
        settings_button_sprite = al_load_bitmap(SETTINGS_BUTTON_SPRITE);
        instruções_sprite = al_load_bitmap(INSTRUÇÕES_SPRITE);
        score_sprite = al_load_bitmap(SCORE_SPRITE);
        home_sprite = al_load_bitmap(HOME_SPRITE);
        background = al_load_bitmap(BACKGROUND);
        for (int i = 0; i < 10; i++)
            numbers_sprites[i] = al_load_bitmap(NUMBERS_SPRITES[i]);
        for (int i = 0; i < 5; i++)
            bird_animation_sprite[i] = al_load_bitmap(BIRD_SPRITE[i]);
        sound_button_sprite[0] = al_load_bitmap(SOUND_BUTTON_SPRITE[0]);
        pause_button_sprite[0] = al_load_bitmap(PAUSE_BUTTON_SPRITE[0]);
        sound_button_sprite[1] = al_load_bitmap(SOUND_BUTTON_SPRITE[1]);
        pause_button_sprite[1] = al_load_bitmap(PAUSE_BUTTON_SPRITE[1]);

        // Criação do pássaro e inserção no vetor de objetos
        game_objects.push_back(new bird_object(SCREEN_W/2, SCREEN_H/2, al_get_bitmap_width(bird_animation_sprite[0]), 
        al_get_bitmap_height(bird_animation_sprite[0]), bird_animation_sprite[0], BIRD_MAX_UP_VEL,
        BIRD_MAX_DOWN_VEL, BIRD_JUMP_VEL));     
        
        //Criação das montanhas
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*3/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*5/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*7/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*3/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*5/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*7/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*3/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*5/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*7/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*3/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*5/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*7/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        //criar os botões aq                                                                               
    };               
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Destrutor
    game_loop::~game_loop() {
        // Deletar os bitmaps dos objetos do jogo
        al_destroy_font(pixel_sans);
        al_destroy_bitmap(pipe_sprite);
        al_destroy_bitmap(golden_pipe_sprite);
        al_destroy_bitmap(mountain_sprite_1);
        al_destroy_bitmap(mountain_sprite_2);
        al_destroy_bitmap(mountain_sprite_3);
        al_destroy_bitmap(grass_sprite);
        al_destroy_bitmap(achievements_button_sprite);
        al_destroy_bitmap(back_button_sprite);
        al_destroy_bitmap(settings_button_sprite);
        al_destroy_bitmap(instruções_sprite);
        al_destroy_bitmap(score_sprite);
        for (int i = 0; i < 9; i++) 
            al_destroy_bitmap(numbers_sprites[i]);
        for (int i = 0; i < 4; i++) 
            al_destroy_bitmap(bird_animation_sprite[i]);
        al_destroy_bitmap(sound_button_sprite[0]);
        al_destroy_bitmap(sound_button_sprite[1]);
        al_destroy_bitmap(pause_button_sprite[0]);
        al_destroy_bitmap(pause_button_sprite[1]);

        // Deletar os objetos do jogo
        for (game_object* obj : game_objects) {
            delete obj; // Deleta cada objeto do jogo
        }
        game_objects.clear(); // Limpa o vetor de objetos do jogo
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
    }

    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void game_loop::commands(unsigned char key[], bool mouse_is_down, bool mouse_just_released){
        if(key[ALLEGRO_KEY_SPACE] == 3) { 
            if(!paused){
                if(!playing && !dead) {                        // Se o jogo não está em andamento e não está morto
                    playing = true;                            // Inicia o jogo
                    game_objects.at(0)->Set_y_acelleration(2); // Define a aceleração da gravidade
                } 
                if(playing && !dead) {                         // Se o jogo está em andamento e não está morto
                    game_objects.at(0)->Jump();                // Faz o pássaro pular
                }
                if(!playing && death_menu){
                    dead = false;
                    death_menu = false;
                    this->reset_game();
                }
                //if()
            }
            key[ALLEGRO_KEY_SPACE] = 0;
        }else if(key[ALLEGRO_KEY_ESCAPE] == 3) { // Se a tecla ESC foi pressionada
            if(playing&&!dead){
                paused=!paused; // Alterna o estado de pausa
            }
            key[ALLEGRO_KEY_ESCAPE] =0;
        }
        
        //dps criar botões aqui
        if(mouse_just_released){
            mouse_just_released = false; // Reseta o mouse just released
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void game_loop::update(bool update){
        if(!update){
            return;
        }
        ////////////////////////////////////////
        //Ver posições e criar/deletar objetos//
        ////////////////////////////////////////

        ///////CANOS////////
        //Criando os canos//
        if (playing &&(game_objects.size()==1 || game_objects.at(game_objects.size()-1)->Get_position()->x<SCREEN_W-100)){    // Adiciona o primeiro cano se não houver nenhum ou se o último cano estiver à distância adequada (100 + 250)
            random_offset = dis(gen);                               // Determina o offset do cano a ser spawnado
            int spawn_x = SCREEN_W + 250;                           // Coordenada X de spawn dos canos (fora da tela)
            int spawn_y = (SCREEN_H / 2) - 108 - random_offset;     // Coordenada Y de referência para spawn dos canos

            game_objects.push_back(new pipe_object(spawn_x, spawn_y, al_get_bitmap_width(pipe_sprite), 
            al_get_bitmap_height(pipe_sprite), pipe_sprite));                                           // Instanciação do cano superior
            game_objects.push_back(new pipe_object(spawn_x, spawn_y+al_get_bitmap_height(pipe_sprite)+PIPE_SPACE, 
            al_get_bitmap_width(pipe_sprite), al_get_bitmap_height(pipe_sprite), pipe_sprite));         // Instanciação do cano inferior
                    
            if (game_objects.at(1)->Get_x_speed() > PIPE_SPEED_MAX) {
                game_objects.at(1)->Set_x_speed(game_objects.at(1)->Get_x_speed()-0.1);     // Se a velocidade do cano for maior que o máximo, reduza ela
            }
            int PIPE_SPEED=game_objects.at(1)->Get_x_speed();
        }    
        
        //Deletando os canos//
        for (int i = game_objects.size() - 1; i >= 1; i--) {
            if(game_objects.at(i)->Get_position()->x < -75) { // Se o cano estiver fora da tela
                delete game_objects.at(i); // Deleta o cano
                game_objects.erase(game_objects.begin() + i); // Remove o cano do vetor
            }
        }

        //Verificando pontuação//
        for (int i = 1; i < game_objects.size() - 1; i++) {
            if(game_objects.at(i)->Get_position()->x<=SCREEN_W/2){
                if(!game_objects.at(i)->is_scored()){
                    score=score+0.5;
                    game_objects.at(i)->Set_score(true);
                }
            }else break;
        }
        
        ///////Montanhas////////
        //Deletando e Criando as montanhas//
        if (background_objects_1.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_1)/2){
            delete background_objects_1.at(0); 
            background_objects_1.erase(background_objects_1.begin());   
            background_objects_1.push_back(new background_object(background_objects_1.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_1), HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        }
        if (background_objects_2.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_2)/2){
            delete background_objects_2.at(0); 
            background_objects_2.erase(background_objects_2.begin());
            background_objects_2.push_back(new background_object(background_objects_2.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_2), HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        }
        if (background_objects_3.at(0)->Get_position()->x<-al_get_bitmap_width(mountain_sprite_3)/2){
            delete background_objects_3.at(0); 
            background_objects_3.erase(background_objects_3.begin());
            background_objects_3.push_back(new background_object(background_objects_3.back()->Get_position()->x+al_get_bitmap_width(mountain_sprite_3), HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));
        } 

        ////////GRAMA///////////
        //Deletando e criando as gramas//
        if (background_objects_0.at(0)->Get_position()->x<-al_get_bitmap_width(grass_sprite)/2){
            delete background_objects_0.at(0); 
            background_objects_0.erase(background_objects_0.begin());
            background_objects_0.push_back(new background_object(background_objects_0.back()->Get_position()->x+al_get_bitmap_width(grass_sprite), SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        }

        ///////PASSARINHO////////
        // Verifica se o pássaro caiu no chão
        if(game_objects.at(0)->Get_position()->y>SCREEN_H&&!dead){
            dead = true;
            game_objects.at(0)->Jump();
            game_objects.at(0)->Set_x_speed(1.5*game_objects.at(1)->Get_x_speed());
        }

        // Verifica se o pássaro bateu em algum cano
        if(!dead){
            for (int i = game_objects.size() - 1; i >= 1; i--) {
                if(game_objects.at(0)->is_colliding(game_objects.at(i))){
                    dead = true;
                    game_objects.at(0)->Jump();
                    game_objects.at(0)->Set_x_speed(1.7*game_objects.at(1)->Get_x_speed());
                    break;
                }
            }
        }

        // Setando death_menu para true caso ele caia de verdade
        if(game_objects.at(0)->Get_position()->y>SCREEN_H+50&&dead){
            death_menu = true;
            playing = false;
        }

        ////////////////////////////////////////
        //////Atualiza os objetos do jogo///////
        ////////////////////////////////////////
        if (update&&!paused&&!death_menu) {
            game_objects.at(0)->Update(SCREEN_W, SCREEN_H); // Atualiza o pássaro
            if(!dead){
                for (int i = game_objects.size() - 1; i >= 1; i--) {
                    game_objects.at(i)->Update(SCREEN_W, SCREEN_H);
                }
                if(playing&&!dead)
                background_objects_1.at(0)->Set_standard_speed(game_objects.at(1)->Get_x_speed());
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
        //If menu
        //If death_menu

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Método que desenha os objetos do jogo na tela
    void game_loop::draw(){
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
        for (int i = game_objects.size() - 1; i >= 1; i--) {
            game_objects.at(i)->Draw(1);
        }
        if(dead){
            game_objects.at(0)->Draw_spin(0.1*game_objects.at(1)->Get_x_speed());
        }else{
            game_objects.at(0)->Draw(1);
        }

        // Desenha os botões
        for (moving_button* btn : buttons) {
            btn->draw();
        }

        //Desenhar o score
        //al_draw_textf(pixel_sans, black, 10, 10, 0, "Score: %d", score);
        al_flip_display();
    }      

    // Método que reseta o jogo, recriando os objetos e o cenário
    void game_loop::reset_game()
    {   if(game_objects.size()>1)
        score = 0;
        game_objects.at(1)->Set_x_speed(-5);
        game_objects.clear();
        game_objects.push_back(new bird_object(SCREEN_W/2, SCREEN_H/2, al_get_bitmap_width(bird_animation_sprite[0]), 
        al_get_bitmap_height(bird_animation_sprite[0]), bird_animation_sprite[0], BIRD_MAX_UP_VEL,
        BIRD_MAX_DOWN_VEL, BIRD_JUMP_VEL));
        
        background_objects_0.clear();
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*3/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*5/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.push_back(new background_object(al_get_bitmap_width(grass_sprite)*7/2, SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
        background_objects_0.at(0)->Set_standard_speed(0);
        
        background_objects_1.clear();
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*3/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*5/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              
        background_objects_1.push_back(new background_object(al_get_bitmap_width(mountain_sprite_1)*7/2, HEIGHT_REFFERENCE, al_get_bitmap_width(mountain_sprite_1), al_get_bitmap_height(mountain_sprite_1), mountain_sprite_1));              

        background_objects_2.clear();
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*3/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*5/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        background_objects_2.push_back(new background_object(al_get_bitmap_width(mountain_sprite_2)*7/2, HEIGHT_REFFERENCE - 103.5, al_get_bitmap_width(mountain_sprite_2), al_get_bitmap_height(mountain_sprite_2), mountain_sprite_2));              
        
        background_objects_3.clear();
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*3/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));              
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*5/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));                   
        background_objects_3.push_back(new background_object(al_get_bitmap_width(mountain_sprite_3)*7/2, HEIGHT_REFFERENCE - 73.5, al_get_bitmap_width(mountain_sprite_3), al_get_bitmap_height(mountain_sprite_3), mountain_sprite_3));                   
        
        buttons.clear();
        
    } 