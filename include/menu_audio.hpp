#ifndef MENU_AUDIO_HPP
#define MENU_AUDIO_HPP

#include <vector>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro.h>
#include "button.hpp"
#include "text_box.hpp"

/**
 * @class menu_audio
 * @brief Gerencia o estado de áudio dos efeitos sonoros do menu (mute/unmute)
 */ 
class menu_audio {
public:
    /**
    * @brief Construtor que inicializa o controle de áudio
    * @param bmp_on Sprite do botão de mute ligado
    * @param bmp_off Sprite do botão de mute desligado
    * @param bmp_on_pr Sprite do botão de mute ligado e pressionado
    * @param bmp_off_pr Sprite do botão de mute desligado e pressionado
    * @param key_sample Efeito sonoro das caixas de texto
    * @param click_sample Efeito sonoro de clicar no botão
    * @param x Coordenada x do botão de mute
    * @param y Coordenada y do botão de mute
    * @param w Largura do botão de mute
    * @param h Altura do botão de mute
    */
    menu_audio(ALLEGRO_BITMAP* bmp_on, ALLEGRO_BITMAP* bmp_off, ALLEGRO_BITMAP* bmp_on_pr, ALLEGRO_BITMAP* bmp_off_pr,
        ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample, int x, int y, int w, int h);
    
    /**
    * @brief Registra quais elementos estão sendo controlados 
    * @param tboxes Caixas de texto controladas
    * @param buttons Botões controlados
    */
    void set_sources(const std::vector<text_box*>& tboxes,const std::vector<button*>&  buttons);

    /**
    * @brief Define a posição do botão de mute/unmute
    * @param x Novo x
    * @param y Novo y
    */
    void set_position(int x, int y);

    /**
    * @brief Muta/Desmuta o áudio conforme cliques do mouse
    * @param ev Evento processado
    */
    void handle_event(const ALLEGRO_EVENT& ev);

    /**
    * @brief Verifica o estado de audio do menu
    * @return Booleano que indica se está mutado ou não
    */
    bool is_muted() const;

    /// Desenha o botão na posição correta e com o bitmap correspondente
    void draw();

private:
    /// @name Posição e tamanho do botão
    /// @{
    int x; 
    int y; 
    int width; 
    int height;
    /// @}

    /// @name Bitmaps visuais do botão
    /// @{
    ALLEGRO_BITMAP* bmp_on;
    ALLEGRO_BITMAP* bmp_off;
    ALLEGRO_BITMAP* bmp_on_pr;
    ALLEGRO_BITMAP* bmp_off_pr;
    /// @}

    /// @name Samples originais dos botões e caixas de texto
    /// @{
    ALLEGRO_SAMPLE* key_sample;
    ALLEGRO_SAMPLE* click_sample;
    /// @}

    /// @name Vetores que armazenam os elementos que estão sendo manipulados
    /// @{
    std::vector<text_box*> text_boxes;
    std::vector<button*> buttons;
    /// @}

    bool muted; ///< Indica se o áudio está mutado
    bool pressed; ///< Indica se o botão foi pressionado

    /// Atualiza os samples para nullptr se muted é true, ou restaura os samples originais
    void update_sources();
};

#endif // MENU_AUDIO_HPP
