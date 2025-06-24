#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "bird_object.hpp"
#include "pipe_object.hpp"
#include "background_object.hpp"
#include "game_loop.hpp"
#include "home_screen.hpp"
#include "settings_screen.hpp"
#include "achievements_screen.hpp"
#include "menu.hpp"

#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

// CONSTANTES PARA CONFIGURAÇÕES GERAIS DO JOGO
#define FPS 60          // frames por segundo 
#define SCREEN_W 800    // comprimento da tela
#define SCREEN_H 600    // altura da tela
#define SEEN 1          // importante para detecção de teclas
#define RELEASED 2      // importante para detecção de teclas

// DECLARANDO A STATIC VELOCIDADE DO CANO
float pipe_object::vel_x = -2.5;    

int main(int argc, char **argv) {
    // Arquivo para debug (just in case)
    std::ofstream debug("../debug_log.txt");
    if (!debug.is_open()) {
        std::cout << "Debug file didn't open";
    }

    // Variáveis
    int mouse_click_pos_x;                                                  // Armazena a posição X do clique do mouse
    int mouse_click_pos_y;                                                  // Armazena a posição Y do clique do mouse
    int mouse_is_now_at_x;                                                  // Armazena a posição X do mouse 
    int mouse_is_now_at_y;                                                  // Armazena a posição Y do mouse
    bool mouse_is_down = false;                                            // Armazena se o mouse está pressionado ou não
    bool mouse_just_released = false;                                      // Armazena se o mouse foi solto nesse momento ou não

    // ROTINAS DO SISTEMA, ADDONS E EXTENSÕES
    /*
    Essa parte talvez seja difícil de entender o que está acontecendo, então é básicamente assim:
        1- Criamos booleanas dinamicamente para cada uma das instalações
        2- Atribuímos cada booleana à respectiva função de instalação 
        3- Como as funções retornam false em caso de erro, verificamos se alguma delas não foi instalada corretamente
        4- Apagamos a memória alocada dinamicamente
    */

    debug << "Iniciando Allegro..." << std::endl;

    bool* sys_install = new bool;
    bool* prim_install = new bool;
    bool* font_install = new bool;
    bool* ttf_install = new bool;
    bool* img_install = new bool;
    bool* keyboard_install = new bool;
    bool* mouse_install = new bool;
    bool* audio_install = new bool;
    bool* acodec_install = new bool;
    
    *sys_install = al_init();                   // Instalação principal
    *prim_install = al_init_primitives_addon(); // Instalação dos primitivos
    *font_install = al_init_font_addon();       // Instalação do addon de fontes
    *ttf_install = al_init_ttf_addon();         // Instalação do addon de fontes ttf
    *img_install = al_init_image_addon();       // Instalação do addon de imagem
    *keyboard_install = al_install_keyboard();  // Instalação do teclado
    *mouse_install = al_install_mouse();        // Instalação do mouse
    *audio_install = al_install_audio();        // Instalação do áudio
    *acodec_install = al_init_acodec_addon();   // Instalação do codec de áudio
    al_reserve_samples(4); // quantos sons simultâneos podem tocar
    
    if(!(*sys_install && *prim_install && *font_install && *ttf_install && *img_install && *keyboard_install && *mouse_install && *audio_install)) {
        debug << "Falha na instalação." << std::endl;
        debug << "SYS: " << *sys_install << std::endl;
        debug << "PRIMITIVES: " << *prim_install << std::endl;
        debug << "FONT: " << *font_install << std::endl;
        debug << "TTF: " << *ttf_install << std::endl;
        debug << "KEYBOARD: " << *keyboard_install << std::endl;
        debug << "MOUSE: " << *mouse_install << std::endl;
        debug << "AUDIO: " << *audio_install << std::endl;
        debug << "CODEC: " << *acodec_install << std::endl;
        system("pause");
        return -1;
    }
    
    delete sys_install;
    delete prim_install;
    delete font_install;
    delete ttf_install;
    delete img_install;
    delete keyboard_install;
    delete mouse_install;
    delete audio_install;
    delete acodec_install;
    
    debug << "Allegro iniciado com sucesso." << std::endl;
    
    debug << "Preparando para o início do jogo..." << std::endl;
    
    // VARIÁVEIS INICIAIS ALLEGRO
    debug << "\tCriando display, fila de eventos e timer..." << std::endl;
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);           // Inicialização do display
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();                       // Inicialização da fila de eventos
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);                          // Inicialização do timer
    ALLEGRO_EVENT event; 
    // VERIFICAÇÃO DE INICIALIZAÇÃO CORRETA DOS PONTEIROS
    if (display == NULL) {
        debug << "Display nao foi criado com sucesso.\n";
        system("pause");
        return 1;
    }
    if (queue == NULL) {
        debug << "Fila de eventos nao foi criada com sucesso.\n";
        system("pause");
        return 2;
    }
    if (timer == NULL) {
        debug << "Timer nao foi criado com sucesso.\n";
        system("pause");
        return 3;
    }
    debug << "\tDisplay, fila de eventos e timer criados com sucesso." << std::endl;
    
    // VETOR PARA LEITURA DE TECLA PRESSIONADA
    debug << "\tCriando vetor de teclas..." << std::endl;
    unsigned char key[ALLEGRO_KEY_MAX];     // Cria um vetor com a quantidade de teclas que podem ser detectadas
    memset(key, 0, sizeof(key));            // Inicializa todas os elementos do vetor como 0
    debug << "\tVetor de teclas criado com sucesso." << std::endl;

    // REGISTRO DA ORIGEM DOS EVENTOS NA FILA DE EVENTOS
    debug << "\tRegistrando fontes de eventos..." << std::endl;
    al_register_event_source(queue, al_get_display_event_source(display));  // Eventos do display
    al_register_event_source(queue, al_get_timer_event_source(timer));      // Eventos do timer
    al_register_event_source(queue, al_get_keyboard_event_source());        // Eventos do teclado
    al_register_event_source(queue, al_get_mouse_event_source());           // Eventos do mouse
    debug << "\tFontes de eventos registradas com sucesso. \n\tIniciando timer..." << std::endl;
    al_start_timer(timer);
    debug << "\tTimer iniciado com sucesso." << std::endl;
    
    // CRIAÇÃO DAS TELAS DO JOGO E OS ESTADOS DE CONTROLE
    debug << "\tCriando telas do jogo..." << std::endl;
    states state;
    Game_Loop main_game_loop;       // Criação do loop de jogo
    Home_Screen main_home_screen;   // Criação da home screen
    Achievements_Screen main_achievements_screen; // Criação da tela de conquistas
    settings_screen main_settings_screen; // Criação da tela de configurações
    registration data("../jogadores.txt"); // Criação do objeto que manipula os dados
    menu main_menu (SCREEN_W, SCREEN_H, data); // Criação do menu principal
    debug << "\tTelas criadas com sucesso." << std::endl;
    
    debug << "\tJogo iniciando...\n" << std::endl;

    al_set_window_title(display, "Flappy Bird");
    
    while(state.open){
        // ESPERA O EVENTO
        // debug << "Esperando por eventos..." << std::endl;
        al_wait_for_event(queue, &event);
        // LEITURA DO EVENTO
        switch(event.type) 
        {
            // Fechamento do display - sai do loop principal
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state.open = false;
                break;

            // Timer - "chama" o loop de update
            case ALLEGRO_EVENT_TIMER:
                if(al_is_event_queue_empty(queue))
                    state.is_updating = true;
                break;

            // Key Down - registra uma tecla pressionada em key (... 0 0 1 1)
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            // Key Up - registra uma tecla que foi solta em key (... 0 0 1 0)
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] = 2;
                break;

            // Mouse Button Down - registra as coordenadas do clique do mouse
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button & 1) // Botão esquerdo
                {
                    mouse_is_down = true; // Marca que o mouse está pressionado
                    mouse_click_pos_x = event.mouse.x;
                    mouse_click_pos_y = event.mouse.y;
                }
                break;
            // Mouse Button Up - registra as coordenadas do clique do mouse
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (event.mouse.button & 1) // Botão esquerdo
                {
                    mouse_just_released = true; // Marca que o mouse foi solto
                    mouse_is_down = false; // Marca que o mouse não está pressionado
                    mouse_click_pos_x = event.mouse.x;
                    mouse_click_pos_y = event.mouse.y;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse_is_now_at_x = event.mouse.x;
                mouse_is_now_at_y = event.mouse.y;
                break;
        }

        if(state.registration_screen){
            if(main_menu.is_login_done())
                main_menu.reset();
            if(!main_menu.is_login_done() && state.registration_screen){
                // Seta o título da janela
                //al_set_window_title(display, "Flappy Bird - Cadastro/Login");
            
                // Menu lida com o evento ocorrido
                main_menu.handle_event(event, state.open, &state);
                
                main_menu.draw(SCREEN_W, SCREEN_H, event);
            }
            if(main_menu.is_login_done())
                state.p=main_menu.get_logged_user();
        }

        // debug << "Processando comandos..." << std::endl;
        if(state.home_screen) {
            if (state.registration_screen == true){
                state.registration_screen = false;
                mouse_is_down = false;
            }
            // debug << "Home Screen ativa." << std::endl;
            main_home_screen.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, state);
            if(state.is_updating && state.home_screen) {
                main_home_screen.update();
                main_home_screen.draw();
                state.is_updating = false;
            }
        }
        
        if(state.game_loop_screen){
            // debug << "Game Loop Screen ativa." << std::endl;
            main_game_loop.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, &state); // Processa os comandos causados pelas teclas/mouse
            if(state.is_updating){
                main_game_loop.update(&state); // Atualiza o estado do jogo
                main_game_loop.draw(); // Desenha o jogo na tela
                state.is_updating = false;
            }
        }
        
        if(state.settings_screen){
            main_settings_screen.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, mouse_is_now_at_x,state,&main_game_loop);
            if(state.is_updating){
                main_settings_screen.update();
                main_settings_screen.draw();
                state.is_updating = false;
            }
        }
        
        if(state.achievements_screen) {
            // debug << "Achievements Screen ativa." << std::endl;
            main_achievements_screen.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, state);
            if(state.is_updating && state.achievements_screen) {
                main_achievements_screen.update();
                main_achievements_screen.draw();
                state.is_updating = false;
            }
        }
        if(mouse_just_released)
            mouse_just_released = false;

        if(state.load_user){
            data.update(state.p);
            state.load_user = false;
        }
    }
    
    debug << "Fim da execução. Fechando Allegro..." << std::endl;

    // Libera recursos Allegro
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    //al_uninstall_mouse();
    //al_uninstall_audio();
    //al_shutdown_primitives_addon();
    //al_shutdown_font_addon();
    //al_shutdown_ttf_addon();
    //al_shutdown_image_addon();
    debug.close();
    return 0;
}