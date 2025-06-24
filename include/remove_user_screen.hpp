#ifndef REMOVE_USER_SCREEN_HPP
#define REMOVE_USER_SCREEN_HPP

#include "text_box.hpp"
#include "button.hpp"
#include "registration.hpp"
#include <allegro5/allegro_font.h>
#include <string>

/** 
 * @class remove_user_screen
 * @brief Tela que lida com a remoção de jogadores
 *
 * - Fase 1: entrada do nome do usuário a ser removido
 * - Fase 2: confirmação com a senha para certeza da exclusão
 */
class remove_user_screen {
public:
    /**
    * @brief Construtor que inicializa a tela de remoção
    * @param screen_w Largura da tela
    * @param screen_h Altura da tela
    * @param data_ref Referência ao objeto que manipula os arquivos
    * @param players Multiset com todos os players registrados para atualizar em caso de remoção
    * @param key_sample Efeito sonoro das caixas de texto
    * @param click_sample Efeito sonoro dos botões
    */
    remove_user_screen(int screen_w, int screen_h, registration& data_ref, std::multiset<player> &players, ALLEGRO_SAMPLE* key_sample, ALLEGRO_SAMPLE* click_sample);

    /**
    * @brief Trata eventos e atualiza flags internas
    * @param ev Evento tratado
    */
    void handle_event(const ALLEGRO_EVENT& ev);

    /**
    * @brief Desenha a tela e seus componentes
    * @param font Fonte utilizada
    */
    void draw(ALLEGRO_FONT* font);

    /**
    * @brief Indica se deve voltar à tela de login
    * @return Booleano que indica o estado da volta
    */
    bool go_to_main_menu() const;

    /**
    * @brief Get do vetor com ponteiros para as caixas de texto para testes e manipulação de áudio
    * @return Vetor com os ponteiros
    */
    const std::vector<text_box*>& get_text_boxes() const;

    /**
    * @brief Get do vetor com ponteiros para os botões para testes e manipulação de áudio
    * @return Vetor com os ponteiros
    */
    const std::vector<button*>&  get_buttons() const;

    /**
    * @brief Indica a fase que a remoção está
    * @return Booleano que indica se está na fase 2: confirmação
    */
    bool is_in_confirmation() const;

    /**
    * @brief Indica se a remoção foi concluída
    * @return Booleano que indica o estado da remoção
    */
    bool is_removal_done() const;    

    /// Reseta a tela para uso futuro
    void reset();

private:
    /// @name Tamanho da tela
    /// @{
    int screen_width; 
    int screen_height;
    /// @}

    /// Referência ao objeto que manipula o arquivo
    registration& data;

    /// Multiset com todos os jogadores registrados
    std::multiset<player> &players;

    /// @name Fase 1
    /// @{
    text_box user_box;
    button remove_button;
    button cancel_button;
    /// @}

    /// @name Fase 2
    /// @{
    bool in_confirmation; ///< indica se está na fase 2 de confirmação
    std::string to_remove; ///< usuário que vai ser removido
    std::string to_remove_password; ///< senha do usuário a ser removido
    button confirm_button;
    button cancel_confirm_button;
    text_box password_box;
    /// @}

    /// @name Vetores de elementos de UI para manipulação de audio e testes
    /// @{
    std::vector<text_box*> text_boxes;
    std::vector<button*> buttons;
    /// @}

    /// @name Flags internas
    /// @{
    bool to_menu; ///< Indica se deve voltar ao menu principal
    bool removal_done; ///< Indica se a remoção foi concluída
    bool empty_field; ///< true para erro de campo vazio
    bool exist_user; ///< false para erro de usuário não existente
    bool correct_password; ///< false para erro de senha incorreta
    /// @}
};

#endif // REMOVE_USER_SCREEN_HPP

