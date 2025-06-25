#include "home_screen.hpp"
#include "registration.hpp" //remover depois
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// CONSTANTES DE PATH
const char * PLAY_BUTTON_SPRITE[2] = {"../assets/UI/play_button.png", "../assets/UI/play_button_pressed.png"}; // caminho do botão de jogar
const char * STATISTICS_BUTTON_SPRITE[2] = {"../assets/UI/statistics_button.png", "../assets/UI/statistics_button_pressed.png"}; // caminho do botão de achievements
const char * LOGOUT_BUTTON_SPRITE[2] = {"../assets/UI/logout_button.png", "../assets/UI/logout_button_pressed.png"}; // caminho do botão de logout
const char * HOME_SCREEN_FRAME = {"../assets/UI/title_screen_frame.png"};  // caminho para o frame da tela de início
const char * TITLE_SPRITE = {"../assets/UI/title_text.png"};               // caminho para o título do jogo

// VARIÁVEIS EXTRAS
int statistics_screen_spawn_x = SCREEN_W+192;   // Posição X do spawn da tela de estatísticas
bool statistics_showing = false;                // Bool que controla se a tela de estatísticas está sendo mostrada
bool statistics_animation_entry = false;        // Bool que controla se a animação da tela de estatísticas está mostrando
bool statistics_animation_exit = false;         // Bool que controla se a animação da tela de estatísticas está escondendo
player p1;

// CONSTRUTOR
Home_Screen::Home_Screen() {
    // Carregamento de sprites
    mountain_sprite_1 = al_load_bitmap(MOUNTAIN_SPRITE_1);
    mountain_sprite_2 = al_load_bitmap(MOUNTAIN_SPRITE_2);
    mountain_sprite_3 = al_load_bitmap(MOUNTAIN_SPRITE_3);
    grass_sprite = al_load_bitmap(GRASS_SPRITE);
    background_sprite = al_load_bitmap(BACKGROUND);
    home_screen_frame_sprite = al_load_bitmap(HOME_SCREEN_FRAME);
    achievements_screen_frame_sprite = al_load_bitmap(DEATH_SCREEN_FRAME);
    achievements_button_sprite[0] = al_load_bitmap(ACHIEVEMENTS_BUTTON_SPRITE[0]);
    achievements_button_sprite[1] = al_load_bitmap(ACHIEVEMENTS_BUTTON_SPRITE[1]);
    settings_button_sprite[0] = al_load_bitmap(SETTINGS_BUTTON_SPRITE[0]);
    settings_button_sprite[1] = al_load_bitmap(SETTINGS_BUTTON_SPRITE[1]);
    play_button_sprite[0] = al_load_bitmap(PLAY_BUTTON_SPRITE[0]);
    play_button_sprite[1] = al_load_bitmap(PLAY_BUTTON_SPRITE[1]);
    statistics_button_sprite[0] = al_load_bitmap(STATISTICS_BUTTON_SPRITE[0]);
    statistics_button_sprite[1] = al_load_bitmap(STATISTICS_BUTTON_SPRITE[1]);
    logout_button_sprite[0] = al_load_bitmap(LOGOUT_BUTTON_SPRITE[0]);
    logout_button_sprite[1] = al_load_bitmap(LOGOUT_BUTTON_SPRITE[1]);

    title_sprite = al_load_bitmap(TITLE_SPRITE);

    // Carregamento da fonte
    title_font = al_load_ttf_font(PSANS_FONT_FILEPATH, 40, 0);
    regular_text_font = al_load_ttf_font(PSANS_FONT_FILEPATH, 24, 0);

    // Criação dos objetos de fundo
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

    // Criação de elementos de UI (imagens)
    /*
    0 - quadro da tela principal
    1 - título do jogo
    2 - quadro da tela de achievements
    */
    images.push_back(new image(home_screen_frame_sprite, SCREEN_W/2, SCREEN_H/2));
    images.push_back(new image(title_sprite, SCREEN_W/2, SCREEN_H/2-110));
    images.push_back(new image(achievements_screen_frame_sprite, statistics_screen_spawn_x, SCREEN_H/2));

    // Criação de elementos de UI (botões)
    /*
    0 - configurações
    1 - achievements
    2 - estatísticas
    3 - logout
    4 - jogar
    */
    buttons.push_back(new moving_button(SCREEN_W/2-117, SCREEN_H/2+168, settings_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2+117, SCREEN_H/2+168, achievements_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2+39, SCREEN_H/2+168, statistics_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2-39, SCREEN_H/2+168, logout_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2, SCREEN_H/2+64, play_button_sprite[0]));

    // Reset de variáveis extras
    statistics_showing = false;
    statistics_animation_entry = false;
    statistics_animation_exit = false;

    //std::cout << "Sizes of vectors:\n\tbackground_objects_0: " << background_objects_0.size() << " (expected 4)\n\tbackground_objects_1: " << background_objects_1.size() << " (expected 4)\n\tbackground_objects_2: " << background_objects_2.size() << " (expected 4)\n\tbackground_objects_3: " << background_objects_3.size() << " (expected 4)\n\timages: " << images.size() << " (expected 2)\n\n";
}

// DESTRUTOR
Home_Screen::~Home_Screen() {
    //std::cout << "Destroyed Home Screen.\n\n";
    // Destruição dos bitmaps
    al_destroy_bitmap(mountain_sprite_1);
    al_destroy_bitmap(mountain_sprite_2);
    al_destroy_bitmap(mountain_sprite_3);
    al_destroy_bitmap(grass_sprite);
    al_destroy_bitmap(background_sprite);
    al_destroy_bitmap(home_screen_frame_sprite);
    al_destroy_bitmap(title_sprite);
    for (int i = 0; i < 2; i++) {
        al_destroy_bitmap(achievements_button_sprite[i]);
        al_destroy_bitmap(settings_button_sprite[i]);
        al_destroy_bitmap(play_button_sprite[i]);
        al_destroy_bitmap(statistics_button_sprite[i]);
        al_destroy_bitmap(logout_button_sprite[i]);
    }

    // Destruição da fonte
    al_destroy_font(title_font);
    al_destroy_font(regular_text_font);

    // Limpeza dos vetores
    for (background_object* bgo : background_objects_0) {
            delete bgo;
    }
    for (background_object* bgo : background_objects_1) {
            delete bgo;
    }
    for (background_object* bgo : background_objects_2) {
            delete bgo;
    }
    for (background_object* bgo : background_objects_3) {
            delete bgo;
    }
    for (moving_button* btn : buttons) {
            delete btn;
    }
    for (image* img : images) {
            delete img;
    }
        
    background_objects_0.clear();
    background_objects_1.clear();
    background_objects_2.clear();
    background_objects_3.clear();
    buttons.clear();
    images.clear();
}

// PROCESSAMENTO DE COMANDOS
void Home_Screen::commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, states& state) {
    // Processamento do mouse
    if (buttons.size() > 0) {
        // Processo caso o mouse tenha acabado de ser solto
        if (mouse_just_released) 
        {
            // Botão de configurações
            if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(0)->is_pressed()) 
            {
                buttons.at(0)->set_bitmap(settings_button_sprite[0]);
                buttons.at(0)->set_pressed(false);
                // Vá para a tela de configurações se clicar em "Configurações"
                state.home_screen = false;
                state.settings_screen = true;
                state.was_in_menu = true;
                // Reseta a velocidade padrão do cenário
                background_objects_0.at(0)->Set_standard_speed(0);
            }

            // Botão de achievements
            if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(1)->is_pressed()) 
            {
                buttons.at(1)->set_bitmap(achievements_button_sprite[0]);
                buttons.at(1)->set_pressed(false);
                // Vá para a tela de achievements se clicar em "Achievements"
                state.home_screen = false;
                state.achievements_screen = true;
                // Reseta a velocidade padrão do cenário
                background_objects_0.at(0)->Set_standard_speed(0);
            }

            // Botão de estatísticas
            if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(2)->is_pressed()) 
            {
                buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
                buttons.at(2)->set_pressed(false);
                // Mostre a tela de estatísticas se clicar em "Estatísticas"
                statistics_showing = !statistics_showing;
                if(statistics_showing) {
                    statistics_animation_entry = true;  // Inicia a animação da tela de estatísticas
                    statistics_animation_exit = false;  // Para a animação de saída da tela de estatísticas
                }
                else {
                    statistics_animation_entry = false; // Para a animação da tela de estatísticas
                    statistics_animation_exit = true;   // Inicia a animação de saída da tela de estatísticas
                }
            }

            // Botão de logout
            if(buttons.at(3)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(3)->is_pressed()) 
            {
                buttons.at(3)->set_bitmap(logout_button_sprite[0]);
                buttons.at(3)->set_pressed(false);
                state.load_user = true;
                state.registration_screen = true;
                state.home_screen = false;
            }

            // Botão de jogar
            if(buttons.at(4)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(4)->is_pressed()) 
            {
                buttons.at(4)->set_bitmap(play_button_sprite[0]);
                buttons.at(4)->set_pressed(false);
                // Vá para o game_loop se clicar em "Jogar"
                state.home_screen = false;
                state.game_loop_screen = true;
                // Reseta a velocidade padrão do cenário
                background_objects_0.at(0)->Set_standard_speed(0);
            }
        }
        // Processo caso o mouse esteja pressionado
        if (mouse_is_down) 
        {
            if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(0)->set_bitmap(settings_button_sprite[1]);
                buttons.at(0)->set_pressed(true);
            }

            if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(1)->set_bitmap(achievements_button_sprite[1]);
                buttons.at(1)->set_pressed(true);
            }

            if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(2)->set_bitmap(statistics_button_sprite[1]);
                buttons.at(2)->set_pressed(true);
            }

            if(buttons.at(3)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(3)->set_bitmap(logout_button_sprite[1]);
                buttons.at(3)->set_pressed(true);
            }

            if(buttons.at(4)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(4)->set_bitmap(play_button_sprite[1]);
                buttons.at(4)->set_pressed(true);
            }
        }
        // Processo caso o mouse esteja solto
        else 
        {   
            // Reseta o estado de pressionamento dos botões
            for(int a=0;a<5;a++)
                buttons.at(a)->set_pressed(false);
            buttons.at(0)->set_bitmap(settings_button_sprite[0]);
            buttons.at(1)->set_bitmap(achievements_button_sprite[0]);
            buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
            buttons.at(3)->set_bitmap(logout_button_sprite[0]);
            buttons.at(4)->set_bitmap(play_button_sprite[0]);
        }
    }

    //Setando player//
    p1=state.p;

    // Reseta o mouse just released
    if (mouse_just_released) {
        mouse_just_released = false;
    }

    // Marca que as teclas apertadas já foram vistas
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        key[i] &= 1;
    }
}

void Home_Screen::update() {
    ///////CENÁRIO//////////
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

    //Deletando e criando as gramas//
    if (background_objects_0.at(0)->Get_position()->x<-al_get_bitmap_width(grass_sprite)/2){
        delete background_objects_0.at(0); 
        background_objects_0.erase(background_objects_0.begin());
        background_objects_0.push_back(new background_object(background_objects_0.back()->Get_position()->x+al_get_bitmap_width(grass_sprite), SCREEN_H - 60, al_get_bitmap_width(grass_sprite), al_get_bitmap_height(grass_sprite), grass_sprite));
    }

    //Atualizando os objetos do cenário//
    background_objects_1.at(0)->Set_standard_speed(-2.5);
    for (background_object* bgo_3 : background_objects_3) {
        bgo_3->Update(0.1); // Atualiza as montanhas de trás
    }
    for (background_object* bgo_2 : background_objects_2) {
        bgo_2->Update(0.2); // Atualiza as montanhas do meio
    }
    for (background_object* bgo_1 : background_objects_1) {
        bgo_1->Update(0.3); // Atualiza as montanhas da frente
    }
    for (background_object* bgo_0 : background_objects_0) {
        bgo_0->Update(0.4); // Atualiza a grama
    }

    //////////UI////////////
    //Tela de estatísticas//
    if (statistics_showing && statistics_animation_entry) {
        // Movendo a tela principal um pouco para a esquerda
        float std_home_screen_speed_in = (((SCREEN_W/2-200)-images.at(0)->get_x())/10)-2;
        images.at(0)->set_velocity(std_home_screen_speed_in, 0);
        images.at(1)->set_velocity(std_home_screen_speed_in, 0);
        for (moving_button* btn : buttons) {
            btn->set_velocity(std_home_screen_speed_in, 0);
        }
        // Movendo a tela de estatísticas para a esquerda
        images.at(2)->set_velocity((((SCREEN_W/2+200)-images.at(2)->get_x())/10)-2, 0);
    }
    else if (!statistics_showing && statistics_animation_exit) {
        // Voltando a tela principal para o centro
        float std_home_screen_speed_out = ((SCREEN_W/2-images.at(0)->get_x())/10)+2;
        images.at(0)->set_velocity(std_home_screen_speed_out, 0);
        images.at(1)->set_velocity(std_home_screen_speed_out, 0);
        for (moving_button* btn : buttons) {
            btn->set_velocity(std_home_screen_speed_out, 0);
        }
        // Voltando a tela de estatísticas para baixo
        images.at(2)->set_velocity(((statistics_screen_spawn_x-images.at(2)->get_x())/10)+2, 0);
    }

    //Atualizando as imagens//
    for (image* img : images)
        img->Update();

    //Verificando se a animação da tela de estatísticas deve ter terminado//
    if (statistics_animation_entry) {
        if (images.at(0)->get_x() <= SCREEN_W/2-200) {
            // Se a tela principal já estiver no lugar, para de mover
            images.at(0)->set_position_x(SCREEN_W/2-200);
            images.at(1)->set_position_x(SCREEN_W/2-200);
            images.at(0)->set_velocity(0, 0);
            images.at(1)->set_velocity(0, 0);
            buttons.at(0)->set_x(SCREEN_W/2-317);
            buttons.at(1)->set_x(SCREEN_W/2-83);
            buttons.at(2)->set_x(SCREEN_W/2-161);
            buttons.at(3)->set_x(SCREEN_W/2-239);
            buttons.at(4)->set_x(SCREEN_W/2-200);
            for (moving_button* btn : buttons) {
                btn->set_velocity(0, 0);
            }
        }
        if (images.at(2)->get_x() <= SCREEN_W/2+200) {
            // Se a tela de estatísticas já estiver no lugar, para de mover
            images.at(2)->set_position_x(SCREEN_W/2+200);
            images.at(2)->set_velocity(0, 0);
        }
        if (images.at(0)->get_x() <= SCREEN_W/2-200 && images.at(2)->get_x() <= SCREEN_W/2+200) {
            // Termina a animação de entrada
            statistics_animation_entry = false;
        }
    }
    else if (statistics_animation_exit) {
        if (images.at(0)->get_x() >= SCREEN_W/2) {
            // Se a tela principal já estiver no lugar, para de mover
            images.at(0)->set_position_x(SCREEN_W/2);
            images.at(1)->set_position_x(SCREEN_W/2);
            images.at(0)->set_velocity(0, 0);
            images.at(1)->set_velocity(0, 0);
            buttons.at(0)->set_x(SCREEN_W/2-117);
            buttons.at(1)->set_x(SCREEN_W/2+117);
            buttons.at(2)->set_x(SCREEN_W/2+39);
            buttons.at(3)->set_x(SCREEN_W/2-39);
            buttons.at(4)->set_x(SCREEN_W/2);
            for (moving_button* btn : buttons) {
                btn->set_velocity(0, 0);
            }
        }
        if (images.at(2)->get_x() >= statistics_screen_spawn_x) {
            // Se a tela de estatísticas já estiver no lugar, para de mover
            images.at(2)->set_position_x(statistics_screen_spawn_x);
            images.at(2)->set_velocity(0, 0);
        }
        if (images.at(0)->get_x() >= SCREEN_W/2 && images.at(2)->get_x() >= statistics_screen_spawn_x) {
            // Termina a animação de saída
            statistics_animation_exit = false;
        }
    }

    //Atualizando os botões//
    for (moving_button* btn : buttons)
        btn->Update();
}

void Home_Screen::draw() {
    // Desenho do background
    al_draw_bitmap(background_sprite, 0, 0, 0);

    // Desenho dos objetos do cenário
    for (background_object* bgo : background_objects_3)
        bgo->Draw(1);
    for (background_object* bgo : background_objects_2)
        bgo->Draw(1);
    for (background_object* bgo : background_objects_1)
        bgo->Draw(1);
    for (background_object* bgo : background_objects_0)
        bgo->Draw(1);

    // Desenho da UI
    images.at(0)->Draw();
    images.at(1)->Draw(1.25);

    // Desenho das estatísticas
    if (statistics_showing || statistics_animation_entry || statistics_animation_exit) {
        // Desenha a tela de estatísticas se estiver sendo mostrada
        images.at(2)->Draw();
        // Escreve as estatísticas do jogador
        int num_achievements;
        for (int a=0; a<16 ; a++){
            if (p1.achievements[a]) num_achievements++;
        }
        al_draw_textf(title_font, al_map_rgb(255, 50, 70), images.at(2)->get_x(), images.at(2)->get_y()-190, ALLEGRO_ALIGN_CENTER, "%s", p1.username.c_str());
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()-130, ALLEGRO_ALIGN_LEFT, "Total de Jogos: %d", p1.games);
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()-90, ALLEGRO_ALIGN_LEFT, "Pontuação máxima: %d", p1.score);
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()-50, ALLEGRO_ALIGN_LEFT, "Conquistas: %d/%d", num_achievements, 16);
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()+10, ALLEGRO_ALIGN_LEFT, "Mortes para canos: %d", p1.pipe_deaths);
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()+50, ALLEGRO_ALIGN_LEFT, "Mortes por cair: %d", p1.ground_deaths);
        al_draw_textf(regular_text_font, al_map_rgb(0, 0, 0), images.at(2)->get_x()-150, images.at(2)->get_y()+90, ALLEGRO_ALIGN_LEFT, "Pulos: %d", p1.jump_count);
    }

    for (moving_button* btn : buttons) {
        btn->draw();
    }

    al_flip_display();
}
