#include "remove_user_screen.hpp"
#include <allegro5/allegro_primitives.h>
#include <sstream>

remove_user_screen::remove_user_screen(int sw, int sh, registration& data_ref, ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample):
    screen_width(sw), screen_height(sh), data(data_ref), 
    user_box(sw/2 - 150, 200, 300, 40, 18, key_sample), password_box(sw/2 - 150, 330, 300, 40, 18, key_sample),
    remove_button(sw/2 - 110, 275, 100, 40, "Remover", click_sample), cancel_button(sw/2 + 10, 275, 100, 40, "Cancelar", click_sample),
    confirm_button(sw/2 - 110, 405, 100, 40, "Confirmar", click_sample), cancel_confirm_button(sw/2 + 10, 405, 100, 40, "Cancelar", click_sample),
    to_menu(false), removal_done(false), empty_field(false), exist_user(true), in_confirmation(false), correct_password(true) {
    password_box.set_mask(true);
    password_box.set_active(false);
    user_box.set_active(false);
}

void remove_user_screen::handle_event(const ALLEGRO_EVENT& ev) {
    // ESC volta ao menu
    if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE && !in_confirmation) {
        to_menu = true;
        return;
    }
    if (!removal_done){
        if (!in_confirmation) {
            // fase 1
            if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
                user_box.handle_event(ev);
            }
            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
                int mx = ev.mouse.x, my = ev.mouse.y;
                bool f = user_box.contains(mx,my);
                user_box.set_active(f);

                remove_button.handle_event(ev);
                cancel_button.handle_event(ev);

                if (remove_button.was_clicked()) {
                    remove_button.reset_clicked();
                    to_remove = user_box.get_text();
                    if (to_remove.empty()) {
                        empty_field = true;
                        exist_user = true; //Evita sobrepor mensagens de erro
                    } else {
                        std::string aux = data.get_stats(to_remove);
                        if (aux == "") {
                            exist_user = false;
                            empty_field = false; //Evita sobrepor mensagens de erro
                            user_box.set_text("");
                        } else {
                            std::istringstream iss(aux);
                            empty_field = false;
                            exist_user = true;
                            int aux_score;
                            iss >> aux_score;
                            iss >> aux;
                            iss >> to_remove_password;
                            in_confirmation = true;
                            password_box.set_text("");
                            password_box.set_active(true);
                        }
                    }
                }
                if (cancel_button.was_clicked()) {
                    cancel_button.reset_clicked();
                    to_menu = true;
                }
            }

            if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ENTER && user_box.is_active_box()) {
                remove_button.reset_clicked();
                to_remove = user_box.get_text();
                if (to_remove.empty()) {
                    empty_field = true;
                    exist_user = true; //Evita sobrepor mensagens de erro
                } else {
                    std::string aux = data.get_stats(to_remove);
                    if (aux == "") {
                        exist_user = false;
                        empty_field = false; //Evita sobrepor mensagens de erro
                        user_box.set_text("");
                    } else {
                        std::istringstream iss(aux);
                        empty_field = false;
                        exist_user = true;
                        int aux_score;
                        iss >> aux_score;
                        iss >> aux;
                        iss >> to_remove_password;
                        in_confirmation = true;
                        password_box.set_text("");
                        password_box.set_active(true);
                    }
                }
            }
        } else {
            // fase 2: confirmação
        if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
                password_box.handle_event(ev);
            } 

            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1) {
                int mx = ev.mouse.x, my = ev.mouse.y;

                // foco senha
                bool focus = password_box.contains(mx,my);
                password_box.set_active(focus); 

                confirm_button.handle_event(ev);
                cancel_confirm_button.handle_event(ev);

                if (confirm_button.was_clicked()) {
                    confirm_button.reset_clicked();
                    std::string pwd = password_box.get_text();

                    if (to_remove_password != pwd) {
                        correct_password = false;
                        password_box.set_text("");
                    } else {
                        correct_password = true;
                        data.delete_user(to_remove);
                        removal_done = true;
                        in_confirmation = false;
                    }
                }
                if (cancel_confirm_button.was_clicked()) {
                    cancel_confirm_button.reset_clicked();
                    in_confirmation = false;
                    correct_password = true;
                    user_box.set_text("");
                }
            }

            if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER:
                        if (password_box.is_active_box()) {
                            confirm_button.reset_clicked();
                            std::string pwd = password_box.get_text();

                            if (to_remove_password != pwd) {
                                correct_password = false;
                                password_box.set_text("");
                            } else {
                                correct_password = true;
                                data.delete_user(to_remove);
                                removal_done = true;
                                in_confirmation = false;
                            }
                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        in_confirmation = false;
                        correct_password = true;
                        user_box.set_text("");
                        break;
                    default: break;
                }
            }
        }
    }
}

void remove_user_screen::draw(ALLEGRO_FONT* font) {
    if (removal_done) {
        // Mensagem final
        std::string msg = "Usuário \"" + to_remove + "\" removido.";
        int tw = al_get_text_width(font, msg.c_str());
        al_draw_text(font, al_map_rgb(255,255,0), (screen_width - tw)/2, 280, 0, msg.c_str());
        std::string warning = "< Pressione ESC para voltar ao menu >";
        int ww = al_get_text_width(font, warning.c_str());
        al_draw_text(font, al_map_rgb(255,255,255), (screen_width - ww)/2, 310, 0, warning.c_str());
        return;
    } 

    else if (!in_confirmation) {
        // fase 1
        al_draw_text(font, al_map_rgb(255,255,255), screen_width/2 - 150, 170, 0, "Usuário a ser removido:");
        user_box.draw(font);
        remove_button.draw(font);
        cancel_button.draw(font);
            
        if (!exist_user) {
        al_draw_text(font, al_map_rgb(252,23,35), screen_width/2 - 150, 245, 0, "Usuário inexistente!");
        }
        if (empty_field) {
        al_draw_text(font, al_map_rgb(252,23,35), screen_width/2 - 150, 245, 0, "O campo está vazio!");
        }

    } else {
        // fase 2: confirmação
        int y0 = 220;
        std::string part1 = "O usuário: ";
        std::string name = "\"" + to_remove + "\"";
        std::string part2 = " será removido. Você tem certeza?";
        int x0 = screen_width/2 - 250;
        // desenha part1
        al_draw_text(font, al_map_rgb(255,255,255), x0, y0, 0, part1.c_str());
        int w1 = al_get_text_width(font, part1.c_str());
        // desenha name em amarelo
        al_draw_text(font, al_map_rgb(255,255,0), x0 + w1, y0, 0, name.c_str());
        int w2 = al_get_text_width(font, name.c_str());
        // desenha part2
        al_draw_text(font, al_map_rgb(255,255,255),
                     x0 + w1 + w2, y0, 0, part2.c_str());
        
        // Caixa de senha
        al_draw_text(font, al_map_rgb(255,255,255), screen_width/2 - 150, 300, 0, "Confirme a senha:");
        password_box.draw(font); 

        // Mensagem de erro de senha inválida
        if (!correct_password) {
            al_draw_text(font, al_map_rgb(252, 23, 35), screen_width/2 - 150, 370, 0, "Senha incorreta!");
        }

        // Subtítulo
        std::string sub = "(essa ação não pode ser desfeita)";
        int sub_w = al_get_text_width(font, sub.c_str());
        al_draw_text(font, al_map_rgb(255,255,0), (screen_width - sub_w)/2, 500, 0, sub.c_str());

        // Botões
        confirm_button.draw(font);
        cancel_confirm_button.draw(font);
    }
}

void remove_user_screen::reset() {
    in_confirmation = false;
    to_menu = false;
    removal_done = false;
    exist_user = true;
    empty_field = false;
    correct_password = true;
    to_remove.clear();
    user_box.set_text("");
    user_box.set_active(false);
    password_box.set_text("");
    password_box.set_active(false);
}

bool remove_user_screen::go_to_main_menu() const { 
  return to_menu; 
}

