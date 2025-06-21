#include "achievements_screen.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// CONSTANTES DE PATH

const char * ACHIEVEMENTS_SCREEN_FRAME = {"assets/UI/achievements/achievements_screen_frame.png"}; // caminho do frame da tela de achievements

// CONSTRUTOR
Achievements_Screen::Achievements_Screen() {
    //std::cout << "Created Achievements Screen.\n\n";
    // Carregamento de spites
    mountain_sprite_1 = al_load_bitmap(MOUNTAIN_SPRITE_1);
    mountain_sprite_2 = al_load_bitmap(MOUNTAIN_SPRITE_2);
    mountain_sprite_3 = al_load_bitmap(MOUNTAIN_SPRITE_3);
    grass_sprite = al_load_bitmap(GRASS_SPRITE);
    background_sprite = al_load_bitmap(BACKGROUND);
    achievements_screen_frame_sprite = al_load_bitmap(ACHIEVEMENTS_SCREEN_FRAME);
    for (int i = 0; i < 2; i++)
        settings_button_sprite[i] = al_load_bitmap(SETTINGS_BUTTON_SPRITE[i]);
    for (int i = 0; i < 2; i++)
        home_sprite[i] = al_load_bitmap(HOME_SPRITE[i]);
    for (int i =0; i < 2; i++)
        statistics_button_sprite[i] = al_load_bitmap(STATISTICS_BUTTON_SPRITE[i]);

    // Carregamento da fonte
    ALLEGRO_FONT *pixel_sans = al_load_ttf_font(PSANS_FONT_FILEPATH, 20, 0);   

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

    // Criação de  elementos de UI (imagens)
    images.push_back(new image(achievements_screen_frame_sprite, SCREEN_W/2, SCREEN_H/2));

    // Criação de  elementos de UI (imagens)   
    buttons.push_back(new moving_button(SCREEN_W/2-115, SCREEN_H/2+168, settings_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2, SCREEN_H/2+168, statistics_button_sprite[0]));
    buttons.push_back(new moving_button(SCREEN_W/2+126, 60, home_sprite[0])); 


    //std::cout << "Sizes of vectors:\n\tbackground_objects_0: " << background_objects_0.size() << " (expected 4)\n\tbackground_objects_1: " << background_objects_1.size() << " (expected 4)\n\tbackground_objects_2: " << background_objects_2.size() << " (expected 4)\n\tbackground_objects_3: " << background_objects_3.size() << " (expected 4)\n\timages: " << images.size() << " (expected 2)\n\n";
}

// DESTRUTOR
Achievements_Screen::~Achievements_Screen() {
    //std::cout << "Destroyed Achievements Screen.\n\n";
    // Destruição dos bitmaps
    al_destroy_bitmap(mountain_sprite_1);
    al_destroy_bitmap(mountain_sprite_2);
    al_destroy_bitmap(mountain_sprite_3);
    al_destroy_bitmap(grass_sprite);
    al_destroy_bitmap(background_sprite);
    al_destroy_bitmap(achievements_screen_frame_sprite);
    for (int i = 0; i < 2; i++) {
        al_destroy_bitmap(settings_button_sprite[i]);
         al_destroy_bitmap(home_sprite[i]);
        al_destroy_bitmap(statistics_button_sprite[i]);
    }

    // Destruição da fonte
    al_destroy_font(pixel_sans);

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
void Achievements_Screen::commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, states& state) {
    if (buttons.size() > 0) {
        if (mouse_just_released) 
        {
            if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(0)->is_pressed()) 
            {
                buttons.at(0)->set_bitmap(settings_button_sprite[0]);
                buttons.at(0)->set_pressed(false);
                // Volta para a tela de configurações se clicar no botão de configurações
                state.settings_screen = true; 
                state.achievements_screen = false;
            }

            if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(2)->is_pressed()) 
            {
                buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
                buttons.at(2)->set_pressed(false);
                // Volta para a tela de estatísticas se clicar no botão de estatísticas
                // state.statistics_screen = true;
                state.achievements_screen = false;
            }

            if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(1)->is_pressed()) 
            {
                buttons.at(1)->set_bitmap(home_sprite[0]);
                buttons.at(1)->set_pressed(false);
                // Volta para a tela inicial se clicar no botão de home
                state.home_screen = true;
                state.achievements_screen = false;
            }
        }
        if (mouse_is_down) 
        {
            if(buttons.at(0)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(0)->set_bitmap(settings_button_sprite[1]);
                buttons.at(0)->set_pressed(true);
            }

            if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(1)->set_bitmap(home_sprite[1]);
                buttons.at(1)->set_pressed(true);
            }

            if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y)) 
            {
                buttons.at(2)->set_bitmap(statistics_button_sprite[1]);
                buttons.at(2)->set_pressed(true);
            }

        }
        else 
        {
            buttons.at(0)->set_bitmap(settings_button_sprite[0]);
            buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
             buttons.at(1)->set_bitmap(home_sprite[0]);
        }
    }

    // Reseta o mouse just released
    if (mouse_just_released) {
        mouse_just_released = false;
    }

    // Marca que as teclas apertadas já foram vistas
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        key[i] &= 1;
    }
}

void Achievements_Screen::update() {
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

    //////////UI////////////
    //Atualizando as imagens//
    for (image* img : images)
        img->Update();

    //Atualizando os botões//
    for (moving_button* btn : buttons)
        btn->Update();
}

void Achievements_Screen::draw() {
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

    for (moving_button* btn : buttons) {
        btn->draw();
    }

    al_flip_display();
}