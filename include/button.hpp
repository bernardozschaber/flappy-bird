#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui_object.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

/**
 * @class button
 * @brief Classe que representa os botões da interface do menu: Herda da classe genêrica de objetos de UI
 *
 * Os botões processam cliques do mouse, se estiver dentro de sua área
 */ 
class button : public ui_object {
public:
  /**
  * @brief Construtor que inicializa um botão
  * @param x Coordenada x que inicia a área do botão
  * @param y Coordenada y que inicia a área do botão
  * @param width Largura do botão
  * @param height Altura do botão
  * @param label Texto que aparece no botão
  * @param button_s Efeito sonoro de clicar no botão
  */
  button(int x, int y, int width, int height, const std::string &label, ALLEGRO_SAMPLE* button_s);

  /**
  * @brief Processa eventos de acordo com cliques do mouse
  * @param ev Evento a ser processado
  */
  void handle_event(const ALLEGRO_EVENT &ev) override;

  /**
  * @brief Desenha o botão na tela
  * @param font Fonte utilizada no label
  */
  void draw(ALLEGRO_FONT *font) override;

  /**
  * @brief Indica se o botão foi clicado
  * @return Booleano que indica o estado do clique
  */
  bool was_clicked() const;

  /**
  * @brief Reseta o estado de clique do botão para "false"
  */
  void reset_clicked();

  /**
  * @brief Seta o estado de clique do botão
  * @param set Novo estado do botão
  */
  void set_clicked(const bool set);

  /**
  * @brief Seta o efeito sonoro do botão
  * @param s Novo sample a ser tocado no clique (nullptr para mutar)
  */
  void set_sample(ALLEGRO_SAMPLE* s);

private:
  std::string label; ///< Texto presente no botão
  bool clicked; ///< Indica se o botão foi clicado
  ALLEGRO_SAMPLE* sample_button; ///< Efeito sonoro de clique do botão
};

#endif // BUTTON_HPP
