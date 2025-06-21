#ifndef MENU_AUDIO_HPP
#define MENU_AUDIO_HPP

#include <vector>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro.h>
#include "button.hpp"
#include "text_box.hpp"

//Gerencia o estado de áudio do menu (mute/unmute), efeitos sonoros e música de fundo. 
class menu_audio {
public:
    // Construtor
    menu_audio(ALLEGRO_BITMAP* bmp_on, ALLEGRO_BITMAP* bmp_off, ALLEGRO_BITMAP* bmp_on_pr, ALLEGRO_BITMAP* bmp_off_pr,
        ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample, int x, int y, int w, int h);
    
    // Registra quais elementos estão sendo controlados
    void set_sources(const std::vector<text_box*>& tboxes,const std::vector<button*>&  buttons);

    // Define a posição do botão de mute/unmute
    void set_position(int x, int y);

    // Lida com cliques do mouse no botão de mute/unmute
    void handle_event(const ALLEGRO_EVENT& ev);

    // Desenha o botão na posição correta e com o bitmap correspondente
    void draw();

private:
    // Posição e tamanho do botão
    int x, y, width, height;

    // Bitmaps visuais do botão
    ALLEGRO_BITMAP* bmp_on;
    ALLEGRO_BITMAP* bmp_off;
    ALLEGRO_BITMAP* bmp_on_pr;
    ALLEGRO_BITMAP* bmp_off_pr;

    // Samples originais dos botões e caixas de texto
    ALLEGRO_SAMPLE* key_sample;
    ALLEGRO_SAMPLE* click_sample;

    // Vetores que armazenam os elementos que estão sendo manipulados
    std::vector<text_box*> text_boxes;
    std::vector<button*> buttons;

    // Flags internas
    bool muted; // Indica se o áudio está mutado
    bool pressed; // Indica se o botão foi pressionado

    // Atualiza os samples para nullptr se muted é true, ou restaura os samples originais
    void update_sources();
};

#endif // MENU_AUDIO_HPP
