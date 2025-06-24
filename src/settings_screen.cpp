#include "settings_screen.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "game_loop.hpp"

// CONSTANTES DE PATH
const char * BACK_SPRITE[2] = {"../assets/UI/back_not.png", "../assets/UI/back_yes.png"}; // caminho do botão de jogar
const char * INDICATOR_SPRITE[2] = {"../assets/UI/indicator.png", "../assets/UI/indicator_pressed.png"};;
//const char * BACK_BUTTON_SPRITE[2] = {"../assets/UI/back_button.png", "../assets/UI/back_button_pressed.png"};
const char * SETTINGS_SCREEN_FRAME = {"../assets/UI/settings_background.png"};                            // caminho para o frame da tela de início
const char * TITLE_SETTINGS_SPRITE = {"../assets/UI/settings_title.png"};                                                // caminho para o título do jogo
const char* SHOW_SPRITE = {"../assets/UI/show.png"};

// CONSTRUTOR
settings_screen::settings_screen() {
    // Carregamento de sprites
    mountain_sprite_1 = al_load_bitmap(MOUNTAIN_SPRITE_1);
    mountain_sprite_2 = al_load_bitmap(MOUNTAIN_SPRITE_2);
    mountain_sprite_3 = al_load_bitmap(MOUNTAIN_SPRITE_3);
    grass_sprite = al_load_bitmap(GRASS_SPRITE);
    background_sprite = al_load_bitmap(BACKGROUND);
    settings_frame_sprite = al_load_bitmap(SETTINGS_SCREEN_FRAME);
    title_settings_sprite = al_load_bitmap(TITLE_SETTINGS_SPRITE);
    show_sprite = al_load_bitmap(SHOW_SPRITE);
    back_sprite[0] = al_load_bitmap(BACK_SPRITE[0]);                      
    back_sprite[1] = al_load_bitmap(BACK_SPRITE[1]);
    indicator_sprite[0] = al_load_bitmap(INDICATOR_SPRITE[0]);              
    indicator_sprite[1] = al_load_bitmap(INDICATOR_SPRITE[1]);
    back_button_sprite[0] = al_load_bitmap(BACK_BUTTON_SPRITE[0]);                
    back_button_sprite[1] = al_load_bitmap(BACK_BUTTON_SPRITE[1]);  
    
    
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
    images.push_back(new image(settings_frame_sprite, SCREEN_W/2, SCREEN_H/2));
    images.push_back(new image(title_settings_sprite, SCREEN_W/2, 70));

    // Criação de  elementos de UI (imagens)   
    buttons.push_back(new moving_button(60, SCREEN_H-55, back_button_sprite[0]));
    
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,200,160,210,1,0,0,1,0,100,100,1)); //Volume
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,200,260,210,1,0,0,1,1,50,10,1)); //Força do pulo
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,200,360,210,1,0,0,1,1,50,15,1)); //Velocidade Máxima do passáro
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,200,460,210,1,0,0,1,1,20,7,1));  //Gravidade
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,560,160,210,1,0,0,1,0,150,20,1)); //Aceleração do cano
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,560,260,210,1,0,0,1,0,50,25,1));  //Velocidade Inicial do Cano
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,560,360,210,1,0,0,1,50,150,80,1)); //Velocidade Maxima do Cano
    slides.push_back(new slider(back_sprite,indicator_sprite,show_sprite,560,460,210,1,0,0,1,0,100,3,1));  //Chance de cano dourado

}

// DESTRUTOR
settings_screen::~settings_screen() {
    std::cout<<"Inicio do Destrutor Settings Screen"<<std::endl;
    //std::cout << "Destroyed Home Screen.\n\n";
    // Destruição dos bitmaps
    al_destroy_bitmap(mountain_sprite_1);
    al_destroy_bitmap(mountain_sprite_2);
    al_destroy_bitmap(mountain_sprite_3);
    al_destroy_bitmap(grass_sprite);
    al_destroy_bitmap(background_sprite);
    al_destroy_bitmap(settings_frame_sprite);
    al_destroy_bitmap(title_settings_sprite);
    for (int i = 0; i < 2; i++) {
        al_destroy_bitmap(back_button_sprite[i]);
        al_destroy_bitmap(back_sprite[i]);
        al_destroy_bitmap(indicator_sprite[i]);
    }

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
    for (slider* slid : slides) {
            delete slid;
    }
    
    background_objects_0.clear();
    background_objects_1.clear();
    background_objects_2.clear();
    background_objects_3.clear();
    buttons.clear();
    images.clear();
    slides.clear();
    std::cout<<"Destrutor Settings"<<std::endl;
}

void settings_screen::commands(unsigned char key[], bool& mouse_is_down, bool& mouse_just_released, int mouse_update_x, int mouse_update_y, int mouse_x_now, states& state, Game_Loop* main_game_loop){
    if(mouse_is_down){
        if(buttons.at(0)->contains_click(mouse_update_x,mouse_update_y)){
            buttons.at(0)->set_pressed(true);
            buttons.at(0)->set_bitmap(back_button_sprite[1]);
        }
    }
    if(mouse_just_released){
        if(buttons.at(0)->is_pressed()){
            buttons.at(0)->set_bitmap(back_button_sprite[0]);
        }
    }
    for(slider* slid : slides)
    slid->update(mouse_is_down,mouse_just_released,mouse_update_x,mouse_update_y,mouse_x_now);

    //Acerta o volume//
    state.volume=slides.at(0)->get_value()/100.0;

    // Reseta o mouse just released
    if (mouse_just_released) {
        if(buttons.at(0)->is_pressed()&&buttons.at(0)->contains_click(mouse_update_x,mouse_update_y)){
            this->set_values();
            if(state.was_in_menu){
                state.settings_screen=false;
                state.home_screen=true;
                main_game_loop->reset_game();
            }else if(state.was_playing){
                state.settings_screen=false;
                state.game_loop_screen=true;
            }else{
                state.settings_screen=false;
                state.game_loop_screen=true;
                main_game_loop->reset_game();
            }
        }
        buttons.at(0)->set_pressed(false);
        mouse_just_released = false;
    }
    
    // Marca que as teclas apertadas já foram vistas
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        key[i] &= 1;
    }
}

void settings_screen::update() {
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

void settings_screen::draw() {
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
    images.at(1)->Draw(0.5);

    for (moving_button* btn : buttons) {
        btn->draw();
    }
    slides.at(0)->draw("Volume");
    slides.at(1)->draw("Força do Pulo");
    slides.at(2)->draw("Velocidade Máxima do Passáro");
    slides.at(3)->draw("Gravidade");
    slides.at(4)->draw("Aceleração do Cano");
    slides.at(5)->draw("Velocidade Inicial do Cano");
    slides.at(6)->draw("Velocidade Máxima do Cano");
    slides.at(7)->draw("Chance de Cano Dourado");

    al_flip_display();
}

void settings_screen::set_values(){
    BIRD_JUMP_VEL = -slides.at(1)->get_value();
    BIRD_MAX_DOWN_VEL = slides.at(2)->get_value();
    BIRD_MAX_UP_VEL = -slides.at(2)->get_value();
    gravity_setter = slides.at(3)->get_value()/10.0;
    PIPE_SPEED_INCREASE = -slides.at(4)->get_value()/1000.0;
    PIPE_INITIAL_SPEED = -slides.at(5)->get_value()/10.0;
    PIPE_SPEED_MAX = -slides.at(6)->get_value()/10.0;
    golden_odds_setter = slides.at(7)->get_value();
    return;
}