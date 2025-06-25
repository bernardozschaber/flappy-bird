#include "menu.hpp"

menu::menu(const int SCREEN_W, const int SCREEN_H, registration &data):
    sample_button(al_load_sample("../assets/audio/button_press.wav")), sample_key(al_load_sample("../assets/audio/keyboard_key.wav")),
    background_menu(al_load_bitmap("../assets/scenario/background_login.png")), crown(al_load_bitmap("../assets/UI/crown-2.png")), ico_on(al_load_bitmap("../assets/UI/sound_on.png")), ico_off(al_load_bitmap("../assets/UI/sound_off.png")),
    ico_on_press(al_load_bitmap("../assets/UI/sound_on_pressed.png")), ico_off_press(al_load_bitmap("../assets/UI/sound_off_pressed.png")), main_menu_title(al_load_bitmap("../assets/UI/main_menu_title_text.png")),
    pixel_sans(al_load_ttf_font("../assets/fonts/pixelify_sans.ttf", 20, 0)), current(SCREEN_LOGIN),
    audio_ctrl(ico_on,ico_off,ico_on_press,ico_off_press,sample_key,sample_button,40, 40, al_get_bitmap_width(ico_on), al_get_bitmap_height(ico_on)), 
    login_scr(SCREEN_W, SCREEN_H, data, sample_key, sample_button), register_scr(SCREEN_W, SCREEN_H, data, players, sample_key, sample_button),
    list_scr(SCREEN_W, SCREEN_H, sample_button, crown, players, data), rm_scr(SCREEN_W, SCREEN_H, data, players,sample_key, sample_button), players(data.get_all()) {}

menu::~menu() {
    al_destroy_sample(sample_key);
    al_destroy_sample(sample_button);
    al_destroy_bitmap(background_menu);
    al_destroy_bitmap(crown);
    al_destroy_font(pixel_sans);
}

void menu::handle_event(const ALLEGRO_EVENT &event, bool &is_open, states* state) {
    // Encaminha evento de acordo com a tela atual
    if (current == SCREEN_LOGIN) {
        // ESC no menu fecha o programa
        if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            is_open = false;
            state->open = false;
            return;
        }

        login_scr.handle_event(event);

        // Atualiza estados do main para iniciar o jogo
        if(login_scr.login_done()){
            state->home_screen = true;
            return;
        }    

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
        
        // Atualiza fontes de audio e posição do botão de mute
        audio_ctrl.set_sources(login_scr.get_text_boxes(),login_scr.get_buttons());
        audio_ctrl.set_position(40,40);
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

        // Atualiza fontes de audio e posição do botão de mute
        audio_ctrl.set_sources(register_scr.get_text_boxes(),register_scr.get_buttons());
        audio_ctrl.set_position(40,40);
    } 
    else if (current == SCREEN_LIST) {
        list_scr.handle_event(event);

        // Se clicou em "Menu" → volta ao login
        if (list_scr.go_to_main_menu()) {
            list_scr.reset();
            current = SCREEN_LOGIN;
        }
        // Atualiza fontes de audio e posição do botão de mute
        std::vector<text_box*> null = {}; // Tela de listagem não possui caixas de texto
        audio_ctrl.set_sources(null,list_scr.get_buttons());
        audio_ctrl.set_position(1000,1000); // Retira botão de mute da tela
    }
    else if (current == SCREEN_REMOVE) {
        rm_scr.handle_event(event);

        // Se clicou em "Cancelar" ou remoção concluída → volta ao login
        if (rm_scr.go_to_main_menu()) {
            rm_scr.reset();
            current = SCREEN_LOGIN;
        }
        // Atualiza fontes de audio e posição do botão de mute
        audio_ctrl.set_sources(rm_scr.get_text_boxes(),rm_scr.get_buttons());
        audio_ctrl.set_position(40,40);
    }
    
    // Manipula o áudio
    audio_ctrl.handle_event(event);
}

void menu::draw(const int SCREEN_W, const int SCREEN_H, const ALLEGRO_EVENT &event) {
    // A cada tick do timer, redesenha tudo
    if (event.type == ALLEGRO_EVENT_TIMER) {
        // Desenha fundo preto em caso de falha de carregar o background
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
            if (main_menu_title) {
                al_draw_scaled_bitmap(
                main_menu_title,
                0,0, al_get_bitmap_width(main_menu_title), al_get_bitmap_height(main_menu_title), 
                ((SCREEN_W - al_get_bitmap_width(main_menu_title)) / 2), 100, 450, 100, 0);
            }
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
        // Desenho do botão de mute
        audio_ctrl.draw();

        al_flip_display(); 
    }
}

bool menu::is_login_done() const { return login_scr.login_done(); }

player menu::get_logged_user() { return login_scr.get_logged_user(); }

void menu::set_players(const std::multiset<player> new_players) {
    players.clear();
    players = new_players;
}

void menu::reset() {
    login_scr.reset();
    register_scr.reset();
    list_scr.reset();
    rm_scr.reset();
    current = SCREEN_LOGIN;
}
