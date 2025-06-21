#include "achievements_screen.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// CONSTANTES DE PATH

const char * ACHIEVEMENTS_SCREEN_FRAME = {"assets/UI/achievements/achievements_screen_frame.png"}; // caminho do frame da tela de achievements
const char * ACHIEVEMENTS_BADGES[16] = {
    "assets/UI/achievements/achievements-01.png", 
    "assets/UI/achievements/achievements-02.png", 
    "assets/UI/achievements/achievements-03.png", 
    "assets/UI/achievements/achievements-04.png",
    "assets/UI/achievements/achievements-05.png",
    "assets/UI/achievements/achievements-06.png",
    "assets/UI/achievements/achievements-07.png",       
    "assets/UI/achievements/achievements-08.png",
    "assets/UI/achievements/achievements-09.png",
    "assets/UI/achievements/achievements-10.png",
    "assets/UI/achievements/achievements-11.png",
    "assets/UI/achievements/achievements-12.png",
    "assets/UI/achievements/achievements-13.png",
    "assets/UI/achievements/achievements-14.png",
    "assets/UI/achievements/achievements-15.png",
    "assets/UI/achievements/achievements-16.png"
};  // caminho dos badges de conquistas


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
    for (int i = 0; i < 2; i++)
        statistics_button_sprite[i] = al_load_bitmap(STATISTICS_BUTTON_SPRITE[i]);

    achievements_badges[0] = al_load_bitmap(ACHIEVEMENTS_BADGES[0]);
    achievements_badges[1] = al_load_bitmap(ACHIEVEMENTS_BADGES[1]);
    achievements_badges[2] = al_load_bitmap(ACHIEVEMENTS_BADGES[2]);
    achievements_badges[3] = al_load_bitmap(ACHIEVEMENTS_BADGES[3]);
    achievements_badges[4] = al_load_bitmap(ACHIEVEMENTS_BADGES[4]);
    achievements_badges[5] = al_load_bitmap(ACHIEVEMENTS_BADGES[5]);
    achievements_badges[6] = al_load_bitmap(ACHIEVEMENTS_BADGES[6]);
    achievements_badges[7] = al_load_bitmap(ACHIEVEMENTS_BADGES[7]);
    achievements_badges[8] = al_load_bitmap(ACHIEVEMENTS_BADGES[8]);
    achievements_badges[9] = al_load_bitmap(ACHIEVEMENTS_BADGES[9]);
    achievements_badges[10] = al_load_bitmap(ACHIEVEMENTS_BADGES[10]);
    achievements_badges[11] = al_load_bitmap(ACHIEVEMENTS_BADGES[11]);
    achievements_badges[12] = al_load_bitmap(ACHIEVEMENTS_BADGES[12]);
    achievements_badges[13] = al_load_bitmap(ACHIEVEMENTS_BADGES[13]);
    achievements_badges[14] = al_load_bitmap(ACHIEVEMENTS_BADGES[14]);
    achievements_badges[15] = al_load_bitmap(ACHIEVEMENTS_BADGES[15]);   

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

    // Criação de  elementos de UI (botões)
    buttons.push_back(new moving_button(SCREEN_W/2-115, SCREEN_H/2+225, settings_button_sprite[0])); // BOTÃO 0
    buttons.push_back(new moving_button(SCREEN_W/2+115, SCREEN_H/2+225, home_sprite[0]));            // BOTÃO 1
    buttons.push_back(new moving_button(SCREEN_W/2, SCREEN_H/2+225, statistics_button_sprite[0]));   // BOTÃO 2

    int img_size = 128 * 0.8;   // 102 pixels
    int spacing_x = 48;         // espaçamento horizontal
    int spacing_y = 2;          // espaçamento vertical
    int text_space = 10;        // espaço para texto abaixo

    int columns = 4;
    int rows = 4;

    int usable_height = 500;

    int total_width = columns * img_size + (columns - 1) * spacing_x;
    int total_height = rows * (img_size + spacing_y + text_space);

    int start_x = (800 - total_width) / 2 + img_size / 2;
    int start_y = (usable_height - total_height) / 2 + img_size / 2;

    for (int i = 0; i < 16; i++) {
        int col = i % columns;
        int row = i / columns;

        int x = start_x + col * (img_size + spacing_x);
        int y = start_y + row * (img_size + spacing_y + text_space) + 10; 

        images.push_back(new image(achievements_badges[i], x, y));
    }

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
    al_destroy_bitmap(achievements_badges[0]);
    al_destroy_bitmap(achievements_badges[1]);
    al_destroy_bitmap(achievements_badges[2]);
    al_destroy_bitmap(achievements_badges[3]);
    al_destroy_bitmap(achievements_badges[4]);
    al_destroy_bitmap(achievements_badges[5]);
    al_destroy_bitmap(achievements_badges[6]);
    al_destroy_bitmap(achievements_badges[7]);
    al_destroy_bitmap(achievements_badges[8]);
    al_destroy_bitmap(achievements_badges[9]);
    al_destroy_bitmap(achievements_badges[10]);
    al_destroy_bitmap(achievements_badges[11]);
    al_destroy_bitmap(achievements_badges[12]);
    al_destroy_bitmap(achievements_badges[13]);
    al_destroy_bitmap(achievements_badges[14]);
    al_destroy_bitmap(achievements_badges[15]);


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
                
            }

            if(buttons.at(1)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(1)->is_pressed()) 
            {
                buttons.at(1)->set_bitmap(home_sprite[0]);
                buttons.at(1)->set_pressed(false);
                // Volta para a tela inicial se clicar no botão de home
                state.home_screen = true;
                state.achievements_screen = false;
            }

            if(buttons.at(2)->contains_click(mouse_update_x, mouse_update_y) && buttons.at(2)->is_pressed()) 
            {
                buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
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
            buttons.at(1)->set_bitmap(home_sprite[0]);
            buttons.at(2)->set_bitmap(statistics_button_sprite[0]);
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
    images[0]->Draw(); // Desenha o frame da tela de achievements
    for (size_t i = 1; i < images.size(); i++) {
        images[i]->Draw(0.8);  
        }

    // Desenho dos botões
    for (moving_button* btn : buttons) {
        btn->draw();
    }

    al_flip_display();
}