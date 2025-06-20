#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "ui_object.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

// Classe que representa caixas de texto do menu: Herda da classe genêrica de objetos de UI
class text_box : public ui_object {
public:
  //Construtor
  text_box(int x, int y, int width, int height, int max_length, ALLEGRO_SAMPLE* key_s);

  // Ativa/Desativa máscara de caracteres (para senhas)
  void set_mask(bool mask_enabled);

  // Define se este campo deve receber eventos de teclado
  void set_active(bool active);
  bool is_active_box() const;

  // Processa apenas eventos relevantes (quando ativo)
  void handle_event(const ALLEGRO_EVENT &ev) override;

  // Desenha a caixa e o texto
  void draw(ALLEGRO_FONT *font) override;

  // Retorna ou seta texto atual da caixa de texto
  std::string get_text() const;
  void set_text(const std::string &t);

  // Seta o efeito sonoro (controlado pelo menu_audio)
  void set_sample(ALLEGRO_SAMPLE* s);

private:
  std::string text; // texto que está no campo
  bool is_active; // true quando clicado/focado
  bool masked; // true para exibir '*' em vez de caracteres
  int max_length; // máximo de caracteres aceitos no campo
  ALLEGRO_SAMPLE* sample_key; // efeito sonoro ao digitar na caixa de texto
};

#endif // TEXT_BOX_HPP
