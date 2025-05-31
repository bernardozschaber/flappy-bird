/*
ESSE MAIN ESTÁ SENDO FEITO PELO SAM PQ O MAIN DO LAÉRCIO TÁ HORRÍVEL DE ENTENDER
AGORA SIM ESSE MAIN FUNCIONA, PODEM USAR
DEPOIS A GENTE RESOLVE QUAL MAIN A GENTE DEVE APAGAR
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "bird_object.hpp"
#include "pipe_object.hpp"
#include "background_object.hpp"

#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include <sstream>

// CONSTANTES PARA CONFIGURAÇÕES GERAIS DO JOGO
#define FPS 30          // frames por segundo 
#define SCREEN_W 800    // comprimento da tela
#define SCREEN_H 600    // altura da tela
#define SEEN 1          // importante para detecção de teclas
#define RELEASED 2      // importante para detecção de teclas

// CONSTANTES DE PATH
const std::string ARIAL_FONT_FILEPATH = "assets/arial.ttf";         // caminho para a fonte arial
const std::string PSANS_FONT_FILEPATH = "assets/pixelify_sans.ttf"; // caminho para a fonte pixelify sans
const char * BIRD_SPRITE = "assets/birdo.png";                      // bitmap do sprite do pássaro
const char * PIPE_SPRITE = "assets/cano.png";                       // bitmap do sprite do cano

// CONSTANTES DE PROPRIEDADE PARA GAME OBJECTS
const int WIDTH_BIRD = 44;          // largura do sprite do pássaro
const int HEIGHT_BIRD = 41;         // altura do sprite do pássaro
const int WIDTH_PIPE = 75;          // largura do sprite do cano
const int HEIGHT_PIPE = 450;        // altura do sprite do cano
const int WIDTH_MOUNTAIN_1 = 384;   // largura do sprite da montanha (1)
const int HEIGHT_MOUNTAIN_1 = 192;  // altura do sprite da montanha (1)

// CONFIGURAÇÃO DO RNG PARA OS CANOS (NÃO MEXER, NGM SABE COMO FUNCIONA DIREITO)
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 384);

int main(int argc, char **argv) 
{
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
        return 4;
    }

    delete sys_install;
    delete prim_install;
    delete font_install;
    delete keyboard_install;
    delete mouse_install;

    // VARIÁVEIS INICIAIS ALLEGRO
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);   // Inicialização do display
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();               // Inicialização da fila de eventos
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);                  // Inicialização do timer
    ALLEGRO_EVENT event;                                                // Armazena o evento a ser atendido da fila

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

    // VARIÁVEIS EXTRAS
    ALLEGRO_BITMAP *death_bitmap = al_load_bitmap("assets/urdeadfrfr.png"); // Imagem de morte (temporário provavelmente)
    int random_offset;                                                      // Offset do cano a ser spawnado
    float chronometer = 0;                                                  // Controle de tempo (em segundos) para spawns e afins
    int PIPE_SPACE = 160;                                                   // Espaçamento entre os canos
    float PIPE_SPEED = -5;                                                  // Velocidade atual dos canos
    float PIPE_SPEED_MAX = -10;                                             // Velocidade máxima dos canos
    std::vector<game_object*> game_objects;                                 // Vetor que guarda os objects (pássaro(0) e canos(>0))
    std::vector<background_object*> background_objects;                     // Vetor que armazena os elementos do cenario
    int mouse_click_pos_x;                                                  // Armazena a posição X do clique do mouse
    int mouse_click_pos_y;                                                  // Armazena a posição Y do clique do mouse

    // VARIÁVEIS DE ESTADO DA EXECUÇÃO
    bool open = true;           // Jogo está aberto
    bool update = false;        // O jogo deve atualizar o estado
    bool playing = false;       // Jogador está no meio de uma partida
    bool dead = false;          // Jogador está morto
    bool death_menu = false;    // Menu de morte está aberto

    // CRIAÇÃO DO PÁSSARO
    bird_object* birdo = new bird_object(SCREEN_W/2, SCREEN_H/2, WIDTH_BIRD, HEIGHT_BIRD, BIRD_SPRITE, -25, +20, -15);
    game_objects.push_back(birdo);  

    // INÍCIO DA EXECUÇÃO DO JOGO DE FATO
    al_start_timer(timer);
    while(open)
    {
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
                update = true;
                break;

            // Key Down - registra uma tecla pressionada em key (... 0 0 1 1)
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            // Key Up - registra uma tecla que foi solta em key (... 0 0 1 0)
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= RELEASED;
                break;

            // Mouse Button Down - registra as coordenadas do clique do mouse
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button & 1) {
                    mouse_click_pos_x = event.mouse.x;
                    mouse_click_pos_y = event.mouse.y;
                }
                break;
        }

        if (open && update) 
        {
            // PROCESSAMENTO SE ESTIVER EM JOGO
            if (playing) 
            {
                chronometer += 1.0 / FPS;                               // Atualiza o cronômetro
                al_clear_to_color(al_map_rgba_f(0.6, 0.6, 1.0, 1));     // Desenha um fundo azul

                // SPAWN DE UM CANO COM BASE NO CRONÔMETRO
                if (chronometer >= -11/PIPE_SPEED)    // Não sei de onde saiu esse -11, só o Laércio sabe
                {
                    random_offset = dis(gen);                               // Determina o offset do cano a ser spawnado
                    int spawn_x = SCREEN_W + 250;                           // Coordenada X de spawn dos canos (fora da tela)
                    int spawn_y = (SCREEN_H / 2) - 108 - random_offset;     // Coordenada Y de referência para spawn dos canos

                    game_objects.push_back(new pipe_object(spawn_x, spawn_y, WIDTH_PIPE, HEIGHT_PIPE, PIPE_SPRITE, PIPE_SPEED));                                           // Instanciação do cano superior (?)
                    game_objects.push_back(new pipe_object(spawn_x, spawn_y+HEIGHT_PIPE+PIPE_SPACE, WIDTH_PIPE, HEIGHT_PIPE, PIPE_SPRITE, PIPE_SPEED));                              // Instanciação do cano inferior (?)

                    if (PIPE_SPEED > PIPE_SPEED_MAX) {
                        PIPE_SPEED -= 0.1;     // Se a velocidade do cano for maior que o máximo, reduza ela
                    }

                    chronometer = 0;    // Reseta o cronômetro (age como cooldown)
                }

                // CHECAGEM SE O PÁSSARO CAIU NO CHÃO
                if (game_objects.size() > 0 && game_objects.at(0)->Get_position()->y > SCREEN_H) 
                {
                    if (!dead && !death_menu) {
                        dead = true;                                        // Ativa o estado de morto
                        game_objects.at(0)->Set_y_speed(PIPE_SPEED*1.5);    // Não tenho a menor ideia do que é isso
                        game_objects.at(0)->Jump();                         // Pulinho para animação (?)
                    }
                }

                // ATUALIZAÇÕES DOS OBJETOS
                if (!dead)       // Caso não esteja morto
                {
                    for (int i = game_objects.size() - 1; i >= 0; i--) {
                        game_objects.at(i)->Update(SCREEN_W, SCREEN_H);     // Faz o update de cada game object no vetor

                        if (game_objects.at(i)->Get_position()->x < -400)       // Despawna o objeto se ele está fora da tela à esquerda
                        {
                            delete game_objects.at(i);
                            game_objects.erase(game_objects.begin() + i);
                            continue;
                        }
                        if ((i!=0) && (game_objects.at(i)->is_colliding(game_objects.at(0)))) // Detecta colisão entre pássaro e cano
                        {
                            dead = true;                                        // Ativa o estado de morto se houve colisão
                            game_objects.at(0)->Set_x_speed(PIPE_SPEED*1.7);    // Não tenho a menor ideia do que é isso
                            game_objects.at(0)->Jump();                         // Pulinho para animação (?)
                        }

                        game_objects.at(i)->Draw(1);                        // Desenha cada game object no vetor
                    }
                }

                else            // Caso esteja morto
                {
                    game_objects.at(0)->Update(SCREEN_W, SCREEN_H);     // Faz o Update somente do pássaro

                    for (int i = game_objects.size() - 1; i >= 1; i--) {
                        game_objects.at(i)->Draw(1);    // Desenha todos os canos
                    }

                    game_objects.at(0)->Draw_spin(0.1*PIPE_SPEED);      // Desenha o pássaro com rotação (?)

                    if (game_objects.at(0)->Get_position()->y >= SCREEN_H + 100 || game_objects.at(0)->Get_position()->x < -100)    // Controle da posição da animação de morte do pássaro em que o menu de morte deve aparecer
                    {
                        death_menu = true;              // Ativa o estado de menu de morte
                        dead = false;                   // Tira o estado de morto (não sei por quê)
                        playing = false;                // Desativa o estado de jogando
                    }
                }
                
                // DETECÇÃO DE PRESSÃO DE TECLA
                if (key[ALLEGRO_KEY_SPACE] == 3)     // Ser =3 aqui significa que ESPAÇO acabou de ser pressionada
                {
                    if (!dead) {
                        game_objects.at(0)->Jump();     // Se não estiver morto, faça o pássaro pular
                    }
                }
                if (key[ALLEGRO_KEY_ESCAPE] == 3)    // Ser =3 aqui significa que ESC acabou de ser pressionada
                {
                    // ESC fecha o jogo
                    playing = false;
                    open = false;
                }
                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)   // "Marca" que as teclas apertadas já foram vistas
                {
                    key[i] &= SEEN;
                }

                al_flip_display();      // Atualiza o display (?)
            }

            // PROCESSAMENTO SE ESTIVER NA TELA DE MORTE
            if (death_menu) 
            {
                chronometer += 1.0 / FPS;
                al_clear_to_color(al_map_rgba_f(1.0, 0.6, 1.0, 1));   // Desenha um fundo rosa

                // DESENHOS DE SPRITES
                for (int i = game_objects.size() - 1; i >= 1; i--) {
                    game_objects.at(i)->Draw(1);    // Desenha cada objeto do vetor
                }

                al_draw_scaled_rotated_bitmap(death_bitmap,al_get_bitmap_width(death_bitmap)/2,al_get_bitmap_height(death_bitmap)/2,SCREEN_W/2,SCREEN_H/2,2,2,0,0);             // Desenho do bitmap de morte (Temporário)

                al_draw_textf(al_create_builtin_font(), al_map_rgb(210, 20, 20), SCREEN_W / 2, SCREEN_H / 2 + 70, ALLEGRO_ALIGN_CENTRE, "Press SPACE to restart or ESC to exit");   // Desenho de texto de instrução (Temporário)
                

                // DETECÇÃO DE PRESSÃO DE TECLA
                if (key[ALLEGRO_KEY_SPACE] == 3)    // Ser =3 aqui significa que ESPAÇO acabou de ser pressionada
                {
                    // RESET DO ESTADO DO JOGO
                    // Deleção de todos os objetos
                    for (game_object* obj : game_objects) {
                        delete obj;
                    }
                    game_objects.clear();

                    // Recriação do pássaro
                    birdo = new bird_object(SCREEN_W/2, SCREEN_H/2, WIDTH_BIRD, HEIGHT_BIRD, BIRD_SPRITE, -25, +20, -15);
                    game_objects.push_back(birdo);

                    chronometer = 0;    // Reset do cronômetro
                    dead = false;       // Desativa o estado de morto
                    death_menu = false; // Desativa o estado de menu de morte
                }
                if (key[ALLEGRO_KEY_ESCAPE] == 3)   // Ser =3 aqui significa que ESC acabou de ser pressionada
                {
                    // ESC fecha o jogo
                    death_menu = false;
                    open = false;
                }
                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)   // "Marca" que as teclas apertadas já foram vistas
                {
                    key[i] &= SEEN;
                }

                al_flip_display();      // Atualiza o display (?)
            }

            // PROCESSAMENTO SE ESTIVER PARA COMEÇAR O JOGO
            if (!playing && !death_menu)
            {
                chronometer = 0;                                    // Zera o cronômetro
                al_clear_to_color(al_map_rgba_f(0.6, 1.0, 0.4, 1)); // Desenha um fundo verde
                game_objects.at(0)->Draw(1);                        // Desenha o pássaro na tela
                

                // DETECÇÃO DE PRESSÃO DE TECLA
                if (key[ALLEGRO_KEY_SPACE] == 3)    // Ser =3 aqui significa que ESPAÇO acabou de ser pressionada
                {
                    playing = true;                             // ESPAÇO inicia o jogo
                    game_objects.at(0)->Jump();                 // Executa o primeiro pulo
                    game_objects.at(0)->Set_y_acelleration(2);  // Seta a aceleração da gravidade (eu acho)
                }
                if (key[ALLEGRO_KEY_ESCAPE] == 3)   // Ser =3 aqui significa que ESC acabou de ser pressionada
                {
                    // ESC fecha o jogo
                    open = false;                               
                }
                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)   // "Marca" que as teclas apertadas já foram vistas
                {
                    key[i] &= SEEN;
                }

                al_flip_display();      // Atualiza o display (?)
            }

            update = false;
        }
    }

    // FIM DA EXECUÇÃO
    for (game_object* object : game_objects) {
        delete object;  // Deleção de todos os game objects
    }
    for (background_object* object : background_objects) {
        delete object;  // Deleção de todos os objetos de background
    }

    al_destroy_display(display);    // Destruição do display
    al_destroy_event_queue(queue);  // Destruição da fila de eventos
    al_destroy_timer(timer);        // Destruição do timer

    return 0;
}