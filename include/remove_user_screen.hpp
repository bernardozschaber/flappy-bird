#ifndef REMOVE_USER_SCREEN_HPP
#define REMOVE_USER_SCREEN_HPP

#include "text_box.hpp"
#include "button.hpp"
#include "registration.hpp"
#include <allegro5/allegro_font.h>
#include <string>

/*
 * Tela para remover um jogador:
 * - Fase 1: entrada do nome do usuário a ser removido
 * - Fase 2: confirmação com a senha para certeza da exclusão
 */
class remove_user_screen {
public:
    // Construtor
    remove_user_screen(int screen_w, int screen_h, registration& data_ref, std::multiset<player> &players, ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample);

    // Trata eventos e atualiza flags internas
    void handle_event(const ALLEGRO_EVENT& ev);

    // Desenha a tela inteira
    void draw(ALLEGRO_FONT* font);

    // Sinaliza retorno ao menu principal
    bool go_to_main_menu() const;

    // Getters dos vetores dos elementos de UI para manipulação de audio
    const std::vector<text_box*>& get_text_boxes() const;
    const std::vector<button*>&  get_buttons() const;

    // Reseta a tela para uso futuro
    void reset();

private:
    // Tamanho da tela
    int screen_width, screen_height;

    // Objeto que manipula o arquivo
    registration& data;
    std::multiset<player> &players;

    // Fase 1
    text_box user_box;
    button remove_button;
    button cancel_button;

    // Fase 2
    bool in_confirmation; // indica se está na fase 2 de confirmação
    std::string to_remove; // usuário que vai ser removido
    std::string to_remove_password; // senha do usuário a ser removido
    button confirm_button;
    button cancel_confirm_button;
    text_box password_box;

    // Vetores de elementos de UI para manipulação de audio
    std::vector<text_box*> text_boxes;
    std::vector<button*> buttons;

    // Flags internas
    bool to_menu; // Indica se deve voltar ao menu principal
    bool removal_done; // Indica se a remoção foi concluída
    bool empty_field; // true para erro de campo vazio
    bool exist_user; // false para erro de usuário não existente
    bool correct_password; // false para erro de senha incorreta
};

#endif // REMOVE_USER_SCREEN_HPP

