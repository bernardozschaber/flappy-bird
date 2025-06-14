#ifndef REMOVE_USER_SCREEN_HPP
#define REMOVE_USER_SCREEN_HPP

#include "text_box.hpp"
#include "button.hpp"
#include "registration.hpp"
#include <allegro5/allegro_font.h>
#include <string>

/**
 * Tela para remover um jogador:
 * - Fase 1: entrada do nome e senha, botões “Remover” e “Cancelar”
 * - Fase 2: confirmação, botões “Confirmar” e “Cancelar”
 */
class remove_user_screen {
public:
    remove_user_screen(int screen_w, int screen_h, registration& data_ref, ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample);

    // Trata eventos e atualiza flags internas
    void handle_event(const ALLEGRO_EVENT& ev);

    // Desenha a tela inteira
    void draw(ALLEGRO_FONT* font);

    // Sinaliza retorno ao menu principal
    bool go_to_main_menu() const;

    // Reseta a tela para uso futuro
    void reset();

private:
    // Tamanho da tela
    int screen_width, screen_height;

    // Objeto que manipula o arquivo
    registration& data;

    // Fase 1
    text_box user_box;
    button remove_button;
    button cancel_button;

    // Fase 2
    bool in_confirmation;
    std::string to_remove;
    std::string to_remove_password;
    button confirm_button;
    button cancel_confirm_button;
    text_box password_box;

    // Flags internas
    bool to_menu;
    bool removal_done;
    bool empty_field;
    bool exist_user;
    bool correct_password;
};

#endif // REMOVE_USER_SCREEN_HPP

