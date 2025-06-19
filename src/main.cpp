#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "bird_object.hpp"
#include "pipe_object.hpp"
#include "background_object.hpp"
#include "game_loop.hpp"
#include "home_screen.hpp"

#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>

// CONSTANTES PARA CONFIGURAÇÕES GERAIS DO JOGO
#define FPS 60          // frames por segundo 
#define SCREEN_W 800    // comprimento da tela
#define SCREEN_H 600    // altura da tela
#define SEEN 1          // importante para detecção de teclas
#define RELEASED 2      // importante para detecção de teclas


// DECLARANDO A STATIC VELOCIDADE DO CANO
float pipe_object::vel_x = -5;    

int main(int argc, char **argv) {
    
    // Arquivo para debug (just in case)
    std::ofstream debug("debug_log.txt");
    if (!debug.is_open()) {
        std::cout << "Debug file didn't open";
    }

    // Variáveis
    int max_score;                                                          // Armazena a pontuação máxima do jogador
    int score;                                                             // Armazena a pontuação do jogador
    int mouse_click_pos_x;                                                  // Armazena a posição X do clique do mouse
    int mouse_click_pos_y;                                                  // Armazena a posição Y do clique do mouse
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

    bool* sys_install = new bool;
    bool* prim_install = new bool;
    bool* font_install = new bool;
    bool* ttf_install = new bool;
    bool* img_install = new bool;
    bool* keyboard_install = new bool;
    bool* mouse_install = new bool;

    *sys_install = al_init();                   // Instalação principal
    *prim_install = al_init_primitives_addon(); // Instalação dos primitivos
    *font_install = al_init_font_addon();       // Instalação do addon de fontes
    *ttf_install = al_init_ttf_addon();         // Instalação do addon de fontes ttf
    *img_install = al_init_image_addon();       // Instalação do addon de imagem
    *keyboard_install = al_install_keyboard();  // Instalação do teclado
    *mouse_install = al_install_mouse();        // Instalação do mouse

    if(!(*sys_install && *prim_install && *font_install && *ttf_install && *img_install && *keyboard_install && *mouse_install)) {
        std::cout << "Falha na instalação." << std::endl;
        std::cout << "SYS: " << sys_install << std::endl;
        std::cout << "PRIMITIVES: " << prim_install << std::endl;
        std::cout << "FONT: " << font_install << std::endl;
        std::cout << "KEYBOARD: " << keyboard_install << std::endl;
        std::cout << "MOUSE: " << mouse_install << std::endl;
        system("pause");
        return -1;
    }

    delete prim_install;
    delete font_install;
    delete ttf_install;
    delete img_install;
    delete keyboard_install;
    delete mouse_install;

    // VARIÁVEIS INICIAIS ALLEGRO
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);           // Inicialização do display
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();                       // Inicialização da fila de eventos
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);                          // Inicialização do timer
    ALLEGRO_EVENT event; 
    // VERIFICAÇÃO DE INICIALIZAÇÃO CORRETA DOS PONTEIROS
    if (display == NULL) {
        std::cout << "Display nao foi criado com sucesso.\n";
        system("pause");
        return 1;
    }
    if (queue == NULL) {
        std::cout << "Fila de eventos nao foi criada com sucesso.\n";
        system("pause");
        return 2;
    }
    if (timer == NULL) {
        std::cout << "Timer nao foi criado com sucesso.\n";
        system("pause");
        return 3;
    }

    // VETOR PARA LEITURA DE TECLA PRESSIONADA
    unsigned char key[ALLEGRO_KEY_MAX];     // Cria um vetor com a quantidade de teclas que podem ser detectadas
    memset(key, 0, sizeof(key));            // Inicializa todas os elementos do vetor como 0
    
    // REGISTRO DA ORIGEM DOS EVENTOS NA FILA DE EVENTOS
    al_register_event_source(queue, al_get_display_event_source(display));  // Eventos do display
    al_register_event_source(queue, al_get_timer_event_source(timer));      // Eventos do timer
    al_register_event_source(queue, al_get_keyboard_event_source());        // Eventos do teclado
    al_register_event_source(queue, al_get_mouse_event_source());           // Eventos do mouse
    al_start_timer(timer);

  
    // CRIAÇÃO DAS TELAS DO JOGO E OS ESTADOS DE CONTROLE
    states state;
    Game_Loop main_game_loop;       // Criação do loop de jogo
    // Home_Screen main_home_screen;   // Criação da home screen

    while(state.open){
        // ESPERA O EVENTO
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
        }

        /*
        if(registration_screen){

        }
        */
        
        if(state.home_screen) {
            main_home_screen.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, state);
            if(state.is_updating && state.home_screen) {
                main_home_screen.update();
                main_home_screen.draw();
                state.is_updating = false;
            }
        }
        
        if(state.game_loop_screen){
            main_game_loop.commands(key, mouse_is_down, mouse_just_released, mouse_click_pos_x, mouse_click_pos_y, &state); // Processa os comandos causados pelas teclas/mouse
            if(state.is_updating){
            main_game_loop.update(); // Atualiza o estado do jogo
            main_game_loop.draw(); // Desenha o jogo na tela
            state.is_updating = false;
            }
        }
        /*
        if(settings_screen){
        }
        */
        /*
        if(achievements_screen){
        }
        */
        
    }
    // Libera recursos Allegro
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    debug.close();
    return 0;
}