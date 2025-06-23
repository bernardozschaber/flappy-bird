#include "menu.hpp"
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
    
    al_install_audio(); // instala subsistema de áudio
    al_init_acodec_addon(); // codecs (WAV)
    al_reserve_samples(4); // quantos sons simultâneos podem tocar

    // REGISTRO DA ORIGEM DOS EVENTOS NA FILA DE EVENTOS
    al_register_event_source(queue, al_get_display_event_source(display));  // Eventos do display
    al_register_event_source(queue, al_get_timer_event_source(timer));      // Eventos do timer
    al_register_event_source(queue, al_get_keyboard_event_source());        // Eventos do teclado
    al_register_event_source(queue, al_get_mouse_event_source());           // Eventos do mouse

    // Inicia objeto que manipula os arquivos
    registration data("../jogadores.txt");
   
    // Variável que controla a condição do programa estar aberto
    bool is_open = true;

    // Declara o menu principal
    menu main_menu (SCREEN_W, SCREEN_H, data);

    // Inicia o timer
    al_start_timer(timer);

    while(is_open){
        // Reseta o menu para poder ser reutilizado
        main_menu.reset();
        while(!main_menu.is_login_done() && is_open){
            // Seta o título da janela
            al_set_window_title(display, "Flappy Bird - Cadastro/Login");

            al_wait_for_event(queue, &event);

            // Fechar o display encerra o loop
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                is_open = false;
                break;
            }
            
            // Menu lida com o evento ocorrido
            main_menu.handle_event(event, is_open);

            main_menu.draw(SCREEN_W, SCREEN_H, event);

            }
        is_open = false;
    }
    // Libera recursos
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
