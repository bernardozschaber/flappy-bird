#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

/**
 * @class ui_object
 * @brief Classe abstrata genêrica de objetos de interface
 *
 * Possui métodos virtuais para serem redefinidos pelos herdeiros e verifica se o mouse está em cima do objeto
 */ 
class ui_object {
public:
  /**
   * @brief Construtor genêrico de objetos de UI
   * @param x Coordenada x que inicia a área do objeto
   * @param y Coordenada y que inicia a área do objeto
   * @param width Largura do objeto
   * @param height Altura do objeto
   */
  ui_object(float x, float y, int width, int height);

  /**
   * @brief Método virtual puro para objetos de UI processarem eventos
   * @param ev Evento a ser processado
   */ 
  virtual void handle_event(const ALLEGRO_EVENT &ev) = 0;

  /**
   * @brief Método virtual puro para desenhar objetos de UI
   * @param font Fonte utilizada nos textos
   */
  virtual void draw(ALLEGRO_FONT *font) = 0;

  /**
  * @brief Get para a coordenada x
  * @return Valor da coordenada x
  */
  float get_x();

  /**
  * @brief Get para a coordenada y
  * @return Valor da coordenada y
  */
  float get_y();

  /**
  * @brief Get para a largura
  * @return Valor da largura
  */
  int get_width();

  /**
  * @brief Get para a altura
  * @return Valor da altura
  */
  int get_height();

  /**
  * @brief Set para a coordenada x
  * @param x Novo valor de x
  */
  void set_x(float x);

  /**
  * @brief Set para a coordenada y
  * @param y Novo valor de y
  */
  void set_y(float y);

  /**
  * @brief Verifica se o mouse está em cima do objeto
  * @param mx Coordenada x da posição do cursor
  * @param my Coordenada y da posição do cursor
  * @return Booleano que indica se o mouse está na área do objeto ou não
  */
  bool contains(int mx, int my) const;

protected:
  float x; ///< Coordenada x do inicio da área do objeto
  float y; ///< Coordenada y do inicio da área do objeto
  int width; ///< Largura do objeto
  int height; ///< Altura do objeto
};

#endif // UIOBJECT_HPP
