#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include "game_object.hpp"
#include "bird_object.hpp"
#include "pipe_object.hpp"
#include <vector>
#include <random>

#include <iostream>
#include <sstream>

using namespace std;

// Constants for game configuration
const float FPS = 30;                                        // Frames per second
const int SCREEN_W = 800;                                    // Screen width in pixels
const int SCREEN_H = 600;                                    // Screen height in pixels
//const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);  // Background color (black)
const string FONT_FILEPATH = "assets/arial.ttf";             // Path to the font file
const int WIDTH_BIRD=44;
const int HEIGHT_BIRD=41;
const int WIDTH_PIPE=75;
const int HEIGHT_PIPE=450;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 384);

bool is_colliding(abs_pos* position_one, abs_pos* position_two) {
    return (std::fabs(position_one->x - position_two->x) < (position_one->w + position_two->w) / 2.0) && (std::fabs(position_one->y - position_two->y) < (position_one->h + position_two->h) / 2.0);
}

int main(int argc, char **argv) {
    // Pointers for Allegro components
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;


    // Initialize Allegro library
    if (!al_init()) {
        cout << "ERROR:" << "failed to initialize allegro" << endl;
        return -1;
    }

    // Initialize Allegro primitives addon
    if (!al_init_primitives_addon()) {
        cout << "ERROR:" << "failed to initialize allegro primitives" << endl;
        return -1;
    }

    // Initialize Allegro image addon
    if (!al_init_image_addon()) {
        cout << "ERROR:" << "failed to initialize allegro images" << endl;
        return -1;
    }

    // Initialize Allegro font and TTF addons
   // if (!al_init_font_addon() || !al_init_ttf_addon()) {
    //    cout << "ERROR:" << "failed to initialize fonts" << endl;
   //     al_destroy_timer(timer);
   //     return -1;
   // }

    // Load the font from the specified file
   // ALLEGRO_FONT *font_arial = al_load_font(FONT_FILEPATH.c_str(), 32, 0);
   // if (font_arial == nullptr) {
   //     cout << "ERROR:" << "failed to load font" << endl;
   //     return -1;
   // }

    // Create an event queue to handle events
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "ERROR:" << "failed to create event_queue" << endl;
        return -1;
    }

    // Install keyboard input support
    if (!al_install_keyboard()) {
        cout << "ERROR:" << "failed to initialize keyboard" << endl;
        return -1;
    }

    // Create the display window
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        cout << "ERROR:" << "failed to create display" << endl;
        return -1;
    }

    // Create a timer to control the game loop
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cout << "ERROR:" << "failed to initialize timer" << endl;
        al_destroy_display(display);
        return -1;
    }

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display)); 
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);

    // Main game loop
    ALLEGRO_BITMAP *death_bitmap = al_load_bitmap("assets/urdeadfrfr.png");
    int random_offset;
    char * sprite_bird = "assets/birdo.png";  // Path to the bird sprite image
    char * sprite_pipe = "assets/cano.png";
    float contador_segundos=0;
    int contador_3segundos=0;
    int PIPE_SPACE = 160; 
    float PIPE_SPEED = -5;
    float PIPE_SPEED_MAX = -10;  // Maximum speed for pipes
    bool open = true;
    bool playing = false;
    bool dead = false;
    bool death_menu = false;

    vector<game_object*> game_objects;  // Vector to hold game objects
    bird_object* birdo= new bird_object(SCREEN_W/2,SCREEN_H/2,WIDTH_BIRD,HEIGHT_BIRD,sprite_bird,-25,+20,-15);  // Initialize the game object (ball)
    game_objects.push_back(birdo);  
    while (open) {
       // cout << "Waiting for events..." << endl;
    ALLEGRO_EVENT ev;
    PIPE_SPEED = -5;
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_TIMER) {
        contador_segundos+=1.0/FPS;
        al_clear_to_color(al_map_rgba_f(12, 112, 12, 1));
      //  cout<< "Drawing game objects..." << endl;
        game_objects.at(0)->Draw(1);
       // al_draw_textf(font_arial, al_map_rgb(255, 0, 255), SCREEN_W - 80, 20, ALLEGRO_ALIGN_CENTRE, "%d seconds", (int)(al_get_timer_count(timer) / FPS));
        al_flip_display();
    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_SPACE:
                game_objects.at(0)->Jump();
                game_objects.at(0)->Set_y_acelleration(2);
                playing = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                open = false;
                break;
        }
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        open = false;
    }
    //cout << "passing through the main loop" << endl;
    while (playing && open) {
        //cout << "Playing..." << endl;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgba_f(122, 1, 122, 13));
            contador_segundos+=1.0/FPS;
            if (contador_segundos>=2.2){
                contador_3segundos++;
                random_offset = dis(gen);
                game_objects.push_back(new pipe_object(SCREEN_W+250,SCREEN_H/2-108-random_offset,WIDTH_PIPE,HEIGHT_PIPE,sprite_pipe,PIPE_SPEED)); 
                game_objects.push_back(new pipe_object(SCREEN_W+250,SCREEN_H/2-108+HEIGHT_PIPE+PIPE_SPACE-random_offset,WIDTH_PIPE,HEIGHT_PIPE,sprite_pipe,PIPE_SPEED)); 
               // if(PIPE_SPEED>PIPE_SPEED_MAX){
                //    PIPE_SPEED-=0.01;
               //    cout<<"Pipe speed: " << PIPE_SPEED << endl;
              // }
              //  cout<<"Pipe speed: " << PIPE_SPEED << endl;
                contador_segundos=0;
            }
            if (game_objects.size() > 0 && game_objects.at(0)->Get_position()->y > SCREEN_H) {
              //  cout<< "Bird is out of screen, checking for death..." << endl;
              //  cout << "Dead: " << dead << endl;
                //cout<< "Death menu active: " << death_menu << endl;
                if (dead==false&&death_menu==false) {
                //cout << "Bird is dead, setting death state..." << endl;
                dead = true;
                game_objects.at(0)->Set_y_speed(PIPE_SPEED*1.5);
                game_objects.at(0)->Jump();
                }
            }
            if(!dead){
            for(int i = game_objects.size() - 1; i >= 0; i--) {
                game_objects.at(i)->Update(SCREEN_W, SCREEN_H);
                if(game_objects.at(i)->Get_position()->x < -400) {
                    delete game_objects.at(i);
                    game_objects.erase(game_objects.begin() + i);
                    continue;
                }
                if((i!=0)&&(game_objects.at(i)->is_colliding(game_objects.at(0)))) {
                    dead=true;
                    game_objects.at(0)->Set_x_speed(PIPE_SPEED*1.5);
                    game_objects.at(0)->Jump();
                }
                game_objects.at(i)->Draw(1);
                }
            }else{
              //  cout << "Dead: " << dead << endl;
                game_objects.at(0)->Update(SCREEN_W, SCREEN_H);
                for(int i = game_objects.size() - 1; i >= 1; i--) {
                 game_objects.at(i)->Draw(1);
                }
                game_objects.at(0)->Draw_spin(0.1*PIPE_SPEED);
               // cout << "drew at " << game_objects.at(0)->Get_position()->y << "out of"<< SCREEN_H + 100<< endl;
                if(game_objects.at(0)->Get_position()->y >= SCREEN_H + 100) {
               //     cout << "restarting" << dead << endl;
                    death_menu=true;
                    dead=false;
                    playing=false;
                }
            }
            al_flip_display();
         }
            //std::cout << "Game objects count: " << game_objects.size() << std::endl;
     //       al_draw_textf(font_arial, al_map_rgb(255, 0, 255), SCREEN_W - 80, 20, ALLEGRO_ALIGN_CENTRE, "%d seconds", (int)(al_get_timer_count(timer) / FPS));
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    if(!dead){
                    game_objects.at(0)->Jump();
                    }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    open = false;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            playing = false;
            open = false;
        }
        while(death_menu){
         //   cout<< "Death menu active..." << endl;
            al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgba_f(122, 1, 122, 13));
            for(int i = game_objects.size() - 1; i >= 1; i--) {
                 game_objects.at(i)->Draw(1);
                }
            al_draw_scaled_rotated_bitmap(death_bitmap,al_get_bitmap_width(death_bitmap)/2,al_get_bitmap_height(death_bitmap)/2,SCREEN_W/2,SCREEN_H/2,2,2,0,0);
            al_draw_textf(al_create_builtin_font(), al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 2 + 70, ALLEGRO_ALIGN_CENTRE, "Press SPACE to restart or ESC to exit");
            al_flip_display();
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    // Reset the game state
                    for (auto obj : game_objects) {
                        delete obj;
                    }
                    game_objects.clear();
                    birdo = new bird_object(SCREEN_W/2,SCREEN_H/2,WIDTH_BIRD,HEIGHT_BIRD,sprite_bird,-25,+20,-15);
                    game_objects.push_back(birdo);
                    contador_segundos = 0;
                    dead = false;
                    death_menu = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    open = false;
                    death_menu = false;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            open = false;
            death_menu = false;
        }
    }
    //cout<< "Exiting game loop..." << endl;
    }
    }
         // Cleanup resources
    delete birdo;
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
    }
    
// End of main.cpp