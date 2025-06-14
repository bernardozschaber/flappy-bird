#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

#include "login_screen.hpp"
#include "register_screen.hpp"
#include "player_list_screen.hpp"
#include "remove_user_screen.hpp"

#include <iostream>

// CONSTANTES PARA CONFIGURAÇÕES GERAIS DO JOGO
#define FPS 30          // frames por segundo 
#define SCREEN_W 800    // comprimento da tela
#define SCREEN_H 600    // altura da tela

int main(int argc, char **argv) {
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

    al_set_window_title(display, "Flappy Bird - Cadastro/Login");
    
    al_install_audio(); // instala subsistema de áudio
    al_init_acodec_addon(); // codecs (WAV)
    al_reserve_samples(4); // quantos sons simultâneos podem tocar
    ALLEGRO_SAMPLE* sample_button = al_load_sample("assets/audio/button_press.wav");
    ALLEGRO_SAMPLE* sample_key = al_load_sample("assets/audio/keyboard_key.wav"); 

    // REGISTRO DA ORIGEM DOS EVENTOS NA FILA DE EVENTOS
    al_register_event_source(queue, al_get_display_event_source(display));  // Eventos do display
    al_register_event_source(queue, al_get_timer_event_source(timer));      // Eventos do timer
    al_register_event_source(queue, al_get_keyboard_event_source());        // Eventos do teclado
    al_register_event_source(queue, al_get_mouse_event_source());           // Eventos do mouse

    // Carrega background do menu
    ALLEGRO_BITMAP* background_menu = al_load_bitmap("assets/scenario/background_login.png");

    // Carrega imagem da coroa do leaderboard
    ALLEGRO_BITMAP *crown = al_load_bitmap("assets/UI/crown-2.png");

    // Inicia objeto que manipula os arquivos
    registration data("jogadores.txt");
    std::multiset<player> players = data.get_all();

    al_start_timer(timer);

    // Inicializa as telas da interface
    login_screen login_scr(SCREEN_W, SCREEN_H, data, sample_key, sample_button);
    register_screen register_scr(SCREEN_W, SCREEN_H, data, players, sample_key, sample_button);
    player_list_screen list_scr(SCREEN_W, SCREEN_H, sample_button, crown, players, data);
    remove_user_screen rm_scr(SCREEN_W, SCREEN_H, data, sample_key, sample_button);

    enum screen_type { SCREEN_LOGIN, SCREEN_REGISTER, SCREEN_LIST, SCREEN_REMOVE };
    
    bool is_open = true;
    ALLEGRO_FONT *pixel_sans = al_load_ttf_font("assets/fonts/pixelify_sans.ttf", 20, 0);

    while(is_open){
        screen_type current = SCREEN_LOGIN;
        login_scr.reset();
        register_scr.reset();
        list_scr.reset();
        rm_scr.reset();
        while(!login_scr.login_done()){
            al_wait_for_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                is_open = false;
                break;
            }

            // Encaminha evento de acordo com a tela atual
            if (current == SCREEN_LOGIN) {
                // ESC no menu fecha o programa
                if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    is_open = false;
                    break;
                }
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
                // Se usuário clicou em "Remover Usuário" → vai para tela de remoção de jogador
                else if (login_scr.go_to_remove_screen()) {
                    current = SCREEN_REMOVE;
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
            else if (current == SCREEN_REMOVE) {
                rm_scr.handle_event(event);

                if (rm_scr.go_to_main_menu()) {
                    rm_scr.reset();
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
                else if (current == SCREEN_REMOVE) {
                    rm_scr.draw(pixel_sans);
                }
                al_flip_display(); 
            }
        }
        is_open = false;
    }
    // Libera recursos
    al_destroy_sample(sample_key);
    al_destroy_sample(sample_button);
    al_destroy_bitmap(background_menu);
    al_destroy_bitmap(crown);
    al_destroy_font(pixel_sans);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
