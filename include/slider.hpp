#ifndef SLIDER_HPP
#define SLIDER_HPP
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "ui_object.hpp"

/**
 * @class slider
 * @brief Classe que representa os sliders da tela de configuração: Herda da classe gênerica de objetos de UI
 * 
 * O slider processa quando o mouse é pressionado se estiver dentro de sua área e segue, com o indicador, a coordenada x do mouse (dentro de seu escopo), calculando também o valor adequado para armazenar.
 */
class slider: public ui_object{
    private:
        ALLEGRO_FONT* up_heaval;
        ALLEGRO_FONT* departure;
        ALLEGRO_BITMAP* show;
        ALLEGRO_BITMAP* back[2];
        ALLEGRO_BITMAP* indicator[2];
        bool is_pressed;
        float pos_indicator;
        float variation;
        bool show_number;
        float disp_h;
        float disp_v;
        float scale;
        float min_value;
        float max_value;
        float value;
        bool is_int;

    public:
      /**
      * @brief Construtor que inicializa o slider
      * @param back_sprite Sprite da parte de trás do slider
      * @param indicator_sprite Sprite do indicador que mostra em que parte do slider esta
      * @param show Sprite da parte de trás do display do valor
      * @param x Coordenada x que inicia a posição do centro do slider
      * @param y Coordenada y que inicia a posição do centro do slider
      * @param variation_ Tamanho usavel para deslize do sprite do slider
      * @param show_number_ Bool que decide se o número vai ser mostrado ou não
      * @param disp_h_ Diferença horizontal do centro do slider para o local em que o valor sera imprimido
      * @param disp_v_ Diferença vertical do centro do slider para o local em que o valor sera imprimido
      * @param scale_ Proporção que o slider sera desenhado
      * @param is_int_ Bool que decide se o valor armazenado sera int (1) ou um float com uma casa decimal (0)
      */
        slider(ALLEGRO_BITMAP** back_sprite, ALLEGRO_BITMAP** indicator_sprite, ALLEGRO_BITMAP* show, float x, float y, float variation_, bool show_number_, float disp_h_, float disp_v_, float scale_, float min_value_, float max_value_, float value_, bool is_int_);
        
        /**
        * @brief Destrutor que deleta o slider
        */
        ~slider();

        /**
        * @brief Desenha o slider na tela com um nome em cima
        * @param nome Texto que aparecerá em cima do slider
        */
        void draw(std::string nome);
        
        /**
        * @brief Atualiza o valor e posição do indicador/slider de acordo com o comportamento do mouse do usuário
        * @param mouse_is_down Bool que fala se o mouse está pressionado
        * @param mouse_just_released Bool que fala se o mouse acabou de ser liberado
        * @param x_at_down Coordenada X do ultimo clique do mouse
        * @param y_at_down Coordenada Y do ultimo clique do mouse
        * @param x_now Coordenada X do mouse nesse exato momento
        */
        void update(bool mouse_is_down, bool mouse_just_released, int x_at_down, int y_at_down, int x_now);
        
        /**
        * @brief Muda a váriavel Bool de pressionamento de acordo com o parâmetro
        * @param is_pressed Novo valor da Bool de estado pressionamento
        */
        void set_pressed(bool is_pressed);
        
        /**
        * @brief Retorna se o ponto x,y esta dentro da área do indicador
        * @param x Coordenada X do ponto analisado
        * @param y Coordenada Y do ponto analisado
        */
        bool cointains_indicator(float x, float y);
        
        /**
        * @brief Retorna se o ponto x,y esta dentro da área da parte de trás do slider
        * @param x Coordenada X do ponto analisado
        * @param y Coordenada Y do ponto analisado
        */
        bool cointains_back(float x, float y);
        
        /**
        * @brief Atribui o bitmap passado como parameto para a parte de trás do slider 
        * @param new_back_bitmap Novo bitmap da parte de trás do slider
        */
        void set_bitmap_back(ALLEGRO_BITMAP* new_back_bitmap);
        
        /**
        * @brief Atribui o bitmap passado como parameto para o indicator slider 
        * @param new_indicator_bitmap Novo bitmap do indicator slider
        */
        void set_bitmap_indicator(ALLEGRO_BITMAP* new_indicator_bitmap);
        
        /**
        * @brief Retorna o valor armazenado no slider
        */
        float get_value();
        
        /**
        * @brief Não faz nada, mas precisa estar definido por causa da herança
        */
        void handle_event(const ALLEGRO_EVENT &ev)override {return;}
        
        /**
        * @brief Não faz nada, mas precisa estar definido por causa da herança
        */
        void draw(ALLEGRO_FONT *font)override{return;}

};
#endif