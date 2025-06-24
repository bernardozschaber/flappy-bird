/**
 * @file test_main_menu.cpp
 * @brief Testes unitários para o menu principal
 * @details Valida o funcionamento dos processos de login, registro, listagem e remoção, e o funcionamento dos objetos de UI utilizados
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "ui_object.hpp"
#include "text_box.hpp"
#include "button.hpp"
#include "menu_audio.hpp"
#include "registration.hpp"
#include "login_screen.hpp"
#include "register_screen.hpp"
#include "remove_user_screen.hpp"
#include "player_list_screen.hpp"

/// @struct EnsureDummyFile
/// @brief Garante que "jogadores_teste.txt" exista com dados iniciais para login, registro e remoção.
/// - Simula dados de jogadores para teste
static struct EnsureDummyFile {
    EnsureDummyFile() {
        std::ofstream f("../tests/jogadores_teste.txt", std::ios::trunc);
        // usuário válido para login
        f << "0 user pass 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
        // usuário existente para registro falhar
        f << "0 exists 123 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
        // usuário para remoção
        f << "0 del secret 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    }
} _ensure_dummy_file;

/// @struct AllegroInit
/// @brief Garante inicialização do Allegro para os testes
struct AllegroInit {
    AllegroInit() {
        al_init();
        al_install_keyboard();
        al_install_mouse();
        al_install_audio();
        al_init_acodec_addon();
        al_reserve_samples(4);
    }
} _allegro_init;

/// @name Helpers para simular eventos do Allegro
/// @{
static ALLEGRO_EVENT make_key_char_event(int keycode, int unichar) {
    ALLEGRO_EVENT ev{};
    ev.type                 = ALLEGRO_EVENT_KEY_CHAR;
    ev.keyboard.keycode     = keycode;
    ev.keyboard.unichar     = unichar;
    return ev;
}

static ALLEGRO_EVENT make_key_down_event(int keycode) {
    ALLEGRO_EVENT ev{};
    ev.type               = ALLEGRO_EVENT_KEY_DOWN;
    ev.keyboard.keycode   = keycode;
    return ev;
}

static ALLEGRO_EVENT make_key_up_event(int keycode) {
    ALLEGRO_EVENT ev{};
    ev.type               = ALLEGRO_EVENT_KEY_UP;
    ev.keyboard.keycode   = keycode;
    return ev;
}

static ALLEGRO_EVENT make_mouse_event(int type, int x, int y) {
    ALLEGRO_EVENT ev{};
    ev.type        = type;
    ev.mouse.x     = x;
    ev.mouse.y     = y;
    ev.mouse.button= 1;
    return ev;
}
/// @}

// -----------------------------------------------------------------------------
// TEST_CASES
// -----------------------------------------------------------------------------

registration reg("../tests/jogadores_teste.txt");

/// @test Verifica se objetos de UI estão identificando cliques corretamente
TEST_CASE("ui_object::contains() detecta corretamente pontos dentro/fora") {
    // Struct derivada de ui_object para viabilizar testes:
    // ui_object é abstrata, logo, não pode ser instanciada
    struct D : ui_object {
        D(): ui_object(10,20,30,40) {}
        void handle_event(const ALLEGRO_EVENT&) override {}
        void draw(ALLEGRO_FONT*) override {}
    } d;

    // Pontos nos limites da área
    CHECK( d.contains(10,20) );
    CHECK( d.contains(40,60) );

    // Ponto no meio da área
    CHECK( d.contains(20,30) );

    // Pontos fora da área
    CHECK_FALSE( d.contains(9,20) );
    CHECK_FALSE( d.contains(10,61) );
}

/// @test Verifica o comportamento das caixas de texto, como tamanho máximo, exclusão de caracteres e somente inclusão de ASCII válido
TEST_CASE("text_box: aceita só ASCII 33–127, respeita max_length e backspace") {
    text_box tb(0,0,100,20,3,nullptr);
    tb.set_active(true);

    // Espaço e tab são ignorados
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_SPACE,' '));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_TAB,'\t'));
    CHECK( tb.get_text().empty() );

    // Inserir três caracteres válidos
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_A,'A'));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_B,'B'));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_C,'C'));
    CHECK( tb.get_text() == "ABC" );

    // Exceder o comprimento máximo deve ser ignorado
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_D,'D'));
    CHECK( tb.get_text() == "ABC" );

    // Backspace deve remover caracteres até esvaziar
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_BACKSPACE,8));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_BACKSPACE,8));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_BACKSPACE,8));
    CHECK( tb.get_text().empty() );
}

/// @test Verifica se a máscara de senha preserva o texto
TEST_CASE("text_box: masking preserva texto interno") {
    text_box tb(0,0,100,20,5,nullptr);
    tb.set_active(true);

    tb.handle_event(make_key_char_event(ALLEGRO_KEY_A,'A'));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_B,'B'));
    tb.set_mask(true);

    // O texto interno continua intacto
    CHECK( tb.get_text() == "AB" );
}

/// @test Verifica se os botões identificam cliques corretos e se o reset funciona
TEST_CASE("button: clicável apenas dentro da área e reset funciona") {
    button b(5,5,50,20,"OK", nullptr);

    // Clique fora não dispara
    b.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,0,0));
    CHECK_FALSE(b.was_clicked());

    // Clique dentro dispara flag
    b.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,6,6));
    CHECK(b.was_clicked());

    // Reset limpa a flag
    b.reset_clicked();
    CHECK_FALSE(b.was_clicked());
}

/// @test Verifica o comportamento do áudio do menu
TEST_CASE("menu_audio: toggle mute/unmute e update_sources()") {
    menu_audio ma(nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,0,0,16,16);
    text_box tb(0,0,50,20,5,nullptr);
    button  bt(0,0,50,20,"X",nullptr);

    // Registrar fontes e checar flag inicial
    ma.set_sources({&tb},{&bt});
    CHECK_FALSE(ma.is_muted());

    // Clique para mutar
    ma.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,1,1));
    ma.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_UP,1,1));
    CHECK(ma.is_muted());

    // Clique para desmutar
    ma.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,1,1));
    ma.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_UP,1,1));
    CHECK_FALSE(ma.is_muted());

    // Após mutar, digitar em text_box não crasha
    tb.set_active(true);
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_A,'A'));
    CHECK(tb.get_text() == "A");
}

/// @test Verifica funcionamento da tela de login
TEST_CASE("login_screen: fluxo de login, navegação e reset") {
    login_screen ls(800,600, reg, nullptr,nullptr);

    // Login incorreto: user='u', pass='x'
    auto& ut = *ls.get_text_boxes()[0];
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    ls.handle_event(make_key_char_event(ALLEGRO_KEY_U,'u'));
    auto& pt = *ls.get_text_boxes()[1];
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    ls.handle_event(make_key_char_event(ALLEGRO_KEY_X,'x'));
    auto& bl = *ls.get_buttons()[0];
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bl.get_x()+1,bl.get_y()+1));
    CHECK_FALSE(ls.login_done());

    ls.reset();

    // Login correto: user="user", pass="pass"
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("user"))
        ls.handle_event(make_key_char_event(c,c));
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    for(char c: std::string("pass"))
        ls.handle_event(make_key_char_event(c,c));
    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bl.get_x()+1,bl.get_y()+1));
    CHECK(ls.login_done());

    ls.reset();

    // Botões de navegação: registrar, listar, remover
    auto& br    = *ls.get_buttons()[1];
    auto& blist = *ls.get_buttons()[2];
    auto& brem  = *ls.get_buttons()[3];

    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,br.get_x()+1,br.get_y()+1));
    CHECK(ls.go_to_register_screen());
    ls.reset();

    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,blist.get_x()+1,blist.get_y()+1));
    CHECK(ls.go_to_player_list());
    ls.reset();

    ls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,brem.get_x()+1,brem.get_y()+1));
    CHECK(ls.go_to_remove_screen());
}

///@ test Verifica funcionamento da tela de registro
TEST_CASE("register_screen: sucesso, falha, ESC e reset") {
    auto all = reg.get_all();
    register_screen rs(800,600, reg, all, nullptr,nullptr);

    // Sem dados → não completa
    auto& btnc = *rs.get_buttons()[0];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK_FALSE(rs.registration_complete());

    // Fluxo válido: nome="new", senha="pass", confirma senha="pass"
    auto& ut = *rs.get_text_boxes()[0];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("new")) rs.handle_event(make_key_char_event(c,c));
    auto& pt = *rs.get_text_boxes()[1];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    auto& cpt = *rs.get_text_boxes()[2];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,cpt.get_x()+1,cpt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK(rs.registration_complete());

    // Testa reset da tela de registro
    rs.reset();
    CHECK_FALSE(rs.registration_complete());

    // Falha registro se senha != confirmação da senha
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("new2")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,cpt.get_x()+1,cpt.get_y()+1));
    for(char c: std::string("diffpass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK_FALSE(rs.registration_complete());
    rs.reset();

    // Falha ao tentar registrar "exists"
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("exists")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,cpt.get_x()+1,cpt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK_FALSE(rs.registration_complete());

    // ESC volta ao login
    rs.handle_event(make_key_up_event(ALLEGRO_KEY_ESCAPE));
    CHECK(rs.go_to_login_screen());
    rs.reset();

    // Botão de cancelar volta ao login
    auto& btcal = *rs.get_buttons()[1];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btcal.get_x()+1,btcal.get_y()+1));
    CHECK(rs.go_to_login_screen());
    
}

/// @test Verifica funcionamento da tela de remoção
TEST_CASE("remove_user_screen: remoção com confirmação de senha e reset") {
    auto all = reg.get_all();
    remove_user_screen rus(800,600, reg, all, nullptr,nullptr);

    // Não passa para confirmação se usuário não existe
    auto& ut = *rus.get_text_boxes()[0];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("noexist")) rus.handle_event(make_key_char_event(c,c));
    auto& brem = *rus.get_buttons()[0];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,brem.get_x()+1,brem.get_y()+1));
    CHECK_FALSE(rus.is_in_confirmation());

    // Teste reset da tela de remoção
    rus.reset();
    CHECK_FALSE(rus.go_to_main_menu());

    // Fase 1: digita "del" e clica Remover
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("del")) rus.handle_event(make_key_char_event(c,c));
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,brem.get_x()+1,brem.get_y()+1));
    CHECK(rus.is_in_confirmation());

    // Fase 2: senha incorreta → remoção não concluída
    auto& pw = *rus.get_text_boxes()[1];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pw.get_x()+1,pw.get_y()+1));
    rus.handle_event(make_key_char_event(ALLEGRO_KEY_X,'x'));
    auto& bconf = *rus.get_buttons()[2];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bconf.get_x()+1,bconf.get_y()+1));
    CHECK_FALSE(rus.is_removal_done());

    // Senha correta → remove e volta
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pw.get_x()+1,pw.get_y()+1));
    rus.handle_event(make_key_char_event(ALLEGRO_KEY_BACKSPACE,8));
    for(char c: std::string("secret")) rus.handle_event(make_key_char_event(c,c));
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bconf.get_x()+1,bconf.get_y()+1));
    CHECK(rus.is_removal_done());

    rus.reset();

    // ESC volta ao login
    rus.handle_event(make_key_up_event(ALLEGRO_KEY_ESCAPE));
    CHECK(rus.go_to_main_menu());
    rus.reset();

    // Botão de cancelar volta ao login
    auto& btcal = *rus.get_buttons()[1];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btcal.get_x()+1,btcal.get_y()+1));
    CHECK(rus.go_to_main_menu());

}

/// @test Verifica funcionamento da tela de listagem
TEST_CASE("player_list_screen: navegação de páginas e ESC") {
    std::multiset<player> ms;
    for(int i=0; i < 16;i++) {
        std::string name = "p" + std::to_string(i);
        ms.insert(player(name,"123",i*2,i+1));
    }
    player_list_screen pls(800,600,nullptr,nullptr,ms,reg);

    auto& back = *pls.get_buttons()[0];
    auto& next = *pls.get_buttons()[1];
    auto& menu = *pls.get_buttons()[2];

    // Avança uma página
    pls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,next.get_x()+1,next.get_y()+1));
    CHECK(pls.get_current_page() == 1);

    // Volta uma página
    pls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,back.get_x()+1,back.get_y()+1));
    CHECK(pls.get_current_page() == 0);

    // ESC volta ao menu
    pls.handle_event(make_key_up_event(ALLEGRO_KEY_ESCAPE));
    CHECK(pls.go_to_main_menu());
    pls.reset();

    // Botão de menu volta ao login
    pls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,menu.get_x()+1,menu.get_y()+1));
    CHECK(pls.go_to_main_menu());

}
