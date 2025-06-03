#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "ui_object.hpp"
#include <string>

class text_box : public ui_object {
public:
  text_box(int x, int y, int width, int height);

  // Ativa/Desativa máscara de caracteres (para senhas)
  void set_mask(bool mask_enabled) { masked = mask_enabled; }

  // Define se este campo deve receber eventos de teclado
  void set_active(bool active) { is_active = active; }
  bool is_active_box() const { return is_active; }

  // Processa apenas eventos relevantes (quando ativo)
  void handle_event(const ALLEGRO_EVENT &ev) override;

  // Desenha a caixa e o texto
  void draw(ALLEGRO_FONT *font) override;

  // Retorna texto atual do campo
  std::string get_text() const { return text; }
  void set_text(const std::string &t) { text = t; }

private:
  std::string text;
  bool is_active; // true quando clicado/focado
  bool masked;    // true para exibir '*' em vez de caracteres
};

#endif // TEXT_BOX_HPP
