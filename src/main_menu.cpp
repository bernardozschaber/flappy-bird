#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "bird_object.hpp"
#include "pipe_object.hpp"
#include "background_object.hpp"
#include "game_loop.hpp"

#include "login_screen.hpp"
#include "register_screen.hpp"
#include "player_list_screen.hpp"

#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>

// CONSTANTES PARA CONFIGURAÇÕES GERAIS DO JOGO
#define FPS 30          // frames por segundo 
#define SCREEN_W 800    // comprimento da tela
#define SCREEN_H 600    // altura da tela
#define SEEN 1          // importante para detecção de teclas
#define RELEASED 2      // importante para detecção de teclas


// DECLARANDO A STATIC VELOCIDADE DO CANO
float pipe_object::vel_x = -5;                                          
int main(int argc, char **argv){
    int max_score = 0;                                                      // Armazena a pontuação máxima do jogador
    int score = 0;                                                          // Armazena a pontuação do jogador
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

    delete sys_install;
    delete prim_install;
    delete font_install;
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

    // VARIÁVEIS DE ESTADO DA EXECUÇÃO
    bool open = true;                  // Jogo está aberto
    bool is_updating = false;          // O jogo deve atualizar o estado
    bool registration_screen = true;   // Tela de registro está aberta
    bool settings_screen = false;      // Tela de configurações está aberta
    bool game_loop_screen = true;     // O jogo está no loop de jogo
    bool achievements_screen = false;  // Tela de conquistas está aberta
  
    // CRIAÇÃO DAS TELAS DO JOGO
    game_loop main_game_loop; // Criação do loop de jogo

    // Carrega background do menu
    ALLEGRO_BITMAP* background_menu = al_load_bitmap("assets/backgroundmenu.png");
    
    registration data("jogadores.txt"); // Objeto que manipula o arquivo

    al_start_timer(timer);  // Início do timer

    login_screen login_scr(SCREEN_W, SCREEN_H, data);
    register_screen register_scr(SCREEN_W, SCREEN_H, data);
    player_list_screen list_scr(SCREEN_W, SCREEN_H, data);

    enum screen_type { SCREEN_LOGIN, SCREEN_REGISTER, SCREEN_LIST };
    
    bool is_open = true;
    ALLEGRO_FONT *pixel_sans = al_load_ttf_font(PSANS_FONT_FILEPATH, 20, 0);

    while(is_open){
        screen_type current = SCREEN_LOGIN;
        login_scr.reset();
        register_scr.reset();
        list_scr.reset();
        while(!login_scr.login_done()){
            al_wait_for_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                is_open = false;
                break;
            }

            // Encaminha evento de acordo com a tela atual
            if (current == SCREEN_LOGIN) {
                login_scr.handle_event(event);

                // Se usuário clicou em "Registrar" → vai para tela de registro
                if (login_scr.go_to_register_screen()) {
                    current = SCREEN_REGISTER;
                    login_scr.reset();
                }
                // Se usuário clicou em "Ver Jogadores" → vai para tela de listagem
                else if (login_scr.go_to_player_list()) {
                    current = SCREEN_LIST;
                    login_scr.reset();
                }
            }
            else if (current == SCREEN_REGISTER) {
                register_scr.handle_event(event);

               // Se registrou com sucesso → volta ao login
                if (register_scr.registration_complete()) {
                    register_scr.reset();
                    current = SCREEN_LOGIN;
                }
                // Se clicou em "Cancelar" → volta ao login
                else if (register_scr.go_to_login_screen()) {
                    register_scr.reset();
                    current = SCREEN_LOGIN;
                }
            } 
            else if (current == SCREEN_LIST) {
                list_scr.handle_event(event);

                // Se clicou em "Menu" → volta ao login
                if (list_scr.go_to_main_menu()) {
                    list_scr.reset();
                    current = SCREEN_LOGIN;
                }
            }

            // A cada tick do timer, redesenha tudo
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if (background_menu) {
                    al_draw_scaled_bitmap(
                        background_menu,
                        0, 0, al_get_bitmap_width(background_menu), al_get_bitmap_height(background_menu),
                        0, 0, SCREEN_W, SCREEN_H, 0
                    );
                }
               // Desenho conforme a tela ativa
                if (current == SCREEN_LOGIN) {
                    login_scr.draw(pixel_sans);
                }
                else if (current == SCREEN_REGISTER) {
                    register_scr.draw(pixel_sans);
                }
                else if (current == SCREEN_LIST) {
                    list_scr.draw(pixel_sans);
                }
                al_flip_display(); 
            }
        }
        is_open = false;
    }
    while(open){
        // ESPERA O EVENTO
        al_wait_for_event(queue, &event);

        // LEITURA DO EVENTO
        switch(event.type) 
        {
            // Fechamento do display - sai do loop principal
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                open = false;
                break;

            // Timer - "chama" o loop de update
            case ALLEGRO_EVENT_TIMER:
                is_updating = true;
                break;

            // Key Down - registra uma tecla pressionada em key (... 0 0 1 1)
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            // Key Up - registra uma tecla que foi solta em key (... 0 0 1 0)
            // Essa parte talvez não funcione ainda, vou dar uma olhada depois
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= RELEASED;
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
        /*
        if(home_screen){
        }
        */
        if(game_loop_screen){
            main_game_loop.commands(key, mouse_is_down, mouse_just_released); // Processa os comandos causados pelas teclas/mouse
            main_game_loop.update(is_updating); // Atualiza o estado do jogo
            is_updating = false;
            main_game_loop.draw(); // Desenha o jogo na tela
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
    al_destroy_font(pixel_sans);
}