#ifndef MOVING_BUTTON_HPP
#define MOVING_BUTTON_HPP
#include "ui_object.hpp"

/**
 * @class moving_button
 * @brief Classe que representa um botão que se pode se mover na tela: Herda da classe genérica de objetos de UI
 * 
 * Os botões processam cliques do mouse, se estiver dentro de sua área.
 */
class moving_button : public ui_object {
    float vel_x = 0;                    ///< Velocidade horizontal do botão
    float vel_y = 0;                    ///< Velocidade vertical do botão
    float acel_x = 0;                   ///< Aceleração horizontal do botão
    float acel_y = 0;                   ///< Aceleração vertical do botão
    float transparacy = 1;              ///< Transparência do botão (0.0 a 1.0)
    bool is_being_pressed = false;      ///< Indica se o botão está sendo pressionado
    ALLEGRO_BITMAP* sprite;             ///< Bitmap(sprite) do botão

    public:
    /**
     * @brief Construtor da classe moving_button
     * @param x Posição X do botão
     * @param y Posição Y do botão
     * @param Bitmap Bitmap(sprite) do botão
     */
    moving_button(float x, float y, ALLEGRO_BITMAP* Bitmap);

    /**
     * @brief Desenha o botão na tela
     */
    void draw();
    
    /**
     * @brief Desenha o botão na tela com escala
     * @param scale Fator de escala para desenhar o botão
     */
    void draw(float scale);

    /**
     * @brief Seta uma nova velocidade para o botão
     * @param vx Velocidade horizontal do botão
     * @param vy Velocidade vertical do botão
     */
    void set_velocity(float vx, float vy);

    /**
     * @brief Seta uma nova aceleração para o botão
     * @param ax Aceleração horizontal do botão
     * @param ay Aceleração vertical do botão
     */
    void set_acceleration(float ax, float ay);
    
    /**
     * @brief Retorna a velocidade vertical do botão
     * @return Velocidade vertical do botão
     */
    float get_velocity_y();

    /**
     * @brief Retorna a velocidade horizontal do botão
     * @return Velocidade horizontal do botão
     */
    float get_velocity_x();
    
    /**
     * @brief Seta o bitmap do botão
     * @param bitmap Bitmap(sprite) do botão
     */
    void set_bitmap(ALLEGRO_BITMAP* bitmap);

    /**
     * @brief Verifica se o botão contém um clique do mouse
     * @param mouse_x Posição X do mouse
     * @param mouse_y Posição Y do mouse
     */
    bool contains_click(float mouse_x, float mouse_y);

    /**
     * @brief Seta o botão como apertado ou não
     * @param pressed True caso queira que o botão esteja pressionado, false caso contrário
     */
    void set_pressed(bool pressed);

    /**
     * @brief Retorna se o botão está sendo pressionado
     * @return True caso esteja sendo pressionado, false caso contrário
     */
    bool is_pressed();

    /**
     * @brief Atualiza a posição do botão com base na velocidade e aceleração
     */
    void Update();

    /**
     * @brief Não faz nada, mas precisa estar definido por causa da herança
     */
    void handle_event(const ALLEGRO_EVENT &ev);

    /**
     * @brief Não faz nada, mas precisa estar definido por causa da herança
     */
    void draw(ALLEGRO_FONT *font);
};

#endif