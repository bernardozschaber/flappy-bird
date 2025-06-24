#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "ui_object.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

/**
 * @class text_box
 * @brief Classe que representa caixas de texto do menu: Herda da classe genêrica de objetos de UI
 *
 * Caixas de texto se ativam conforme cliques do mouse e processam teclas digitadas, se ativas.
 */ 
class text_box : public ui_object {
public:
  /**
  * @brief Construtor que inicializa uma caixa de texto
  * @param x Coordenada x que inicia a área da caixa
  * @param y Coordenada y que inicia a área da caixa
  * @param width Largura da caixa
  * @param height Altura da caixa
  * @param max_length Quantidade máxima de caracteres aceitos na caixa
  * @param key_s Efeito sonoro de digitar na caixa
  */
  text_box(int x, int y, int width, int height, int max_length, ALLEGRO_SAMPLE* key_s);

  /**
  * @brief Ativa/Desativa máscara de caracteres (para senhas)
  * @param mask_enabled Booleano que indica a ativação da máscara
  */
  void set_mask(bool mask_enabled);

  /**
  * @brief Define se a caixa de texto está ativa
  * @param active Define o estado de ativação da caixa
  */
  void set_active(bool active);

  /**
  * @brief Indica o estado de ativação da caixa
  * @return Booleano que indica o estado
  */
  bool is_active_box() const;

  /**
  * @brief Processa apenas eventos relevantes (quando ativo)
  * @param ev Evento a ser processado
  */
  void handle_event(const ALLEGRO_EVENT &ev) override;

  /**
  * @brief Desenha a caixa e seu texto
  * @param font Fonte utilizada no texto
  */
  void draw(ALLEGRO_FONT *font) override;

  /**
  * @brief Seta o texto da caixa
  * @param t Novo texto da caixa
  */
  void set_text(const std::string &t);

  /**
  * @brief Get do texto da caixa
  * @return Texto da caixa
  */
  std::string get_text() const;

  /**
  * @brief Seta o efeito sonoro (controlado pelo menu_audio)
  * @param s Novo sample (nullptr para mutar)
  */
  void set_sample(ALLEGRO_SAMPLE* s);

private:
  std::string text; ///< texto que está no campo
  bool is_active; ///< true quando clicado/focado
  bool masked; ///< true para exibir '*' em vez de caracteres
  int max_length; ///< máximo de caracteres aceitos no campo
  ALLEGRO_SAMPLE* sample_key; ///< efeito sonoro ao digitar na caixa de texto
};

#endif // TEXT_BOX_HPP
