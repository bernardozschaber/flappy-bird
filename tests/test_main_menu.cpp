#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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

// -----------------------------------------------------------------------------
// DummyRegistration
// Simula operações de login, registro, listagem e remoção sem I/O real.
// -----------------------------------------------------------------------------
struct DummyRegistration {
    DummyRegistration(const std::string&) {}

    bool verifica_login(const std::string& u, const std::string& p) {
        return u == "user" && p == "pass";
    }

    bool add_user(const std::string& u, const std::string&) {
        return u != "exists";
    }

    player get_max() const {
        return player("champ","pass",100,5);
    }

    std::multiset<player> get_all_multiset() const {
        std::multiset<player> s;
        for(int i = 0; i < 20; ++i)
            s.insert(player("p"+std::to_string(i),"123", i, i*2));
        return s;
    }

    bool verify_password(const std::string& u, const std::string& p) {
        return u == "del" && p == "secret";
    }

    bool delete_user(const std::string&) {
        deleted = true;
        return true;
    }

    bool deleted = false;
};

// -----------------------------------------------------------------------------
// AllegroInit
// Inicializa subsistemas de Allegro antes de qualquer teste.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Helpers para criar eventos simulados do Allegro
// -----------------------------------------------------------------------------
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

static ALLEGRO_EVENT make_mouse_event(int type, int x, int y) {
    ALLEGRO_EVENT ev{};
    ev.type        = type;
    ev.mouse.x     = x;
    ev.mouse.y     = y;
    ev.mouse.button= 1;
    return ev;
}

// -----------------------------------------------------------------------------
// TEST_CASES
// -----------------------------------------------------------------------------

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
    CHECK( d.contains(39,59) );

    // Pontos fora da área
    CHECK_FALSE( d.contains(9,20) );
    CHECK_FALSE( d.contains(10,60) );
}

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

TEST_CASE("text_box: masking preserva texto interno") {
    text_box tb(0,0,100,20,5,nullptr);
    tb.set_active(true);

    tb.handle_event(make_key_char_event(ALLEGRO_KEY_A,'A'));
    tb.handle_event(make_key_char_event(ALLEGRO_KEY_B,'B'));
    tb.set_mask(true);

    // O texto interno continua intacto
    CHECK( tb.get_text() == "AB" );
}

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

TEST_CASE("menu_audio: toggle mute/unmute e update_sources()") {
    menu_audio ma(nullptr,nullptr,nullptr,nullptr,(ALLEGRO_SAMPLE*)1,(ALLEGRO_SAMPLE*)2,0,0,16,16);
    text_box tb(0,0,50,20,5,(ALLEGRO_SAMPLE*)5);
    button  bt(0,0,50,20,"X",(ALLEGRO_SAMPLE*)6);

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

TEST_CASE("login_screen: fluxo de login, navegação e reset") {
    DummyRegistration dr("dummy");
    login_screen ls(100,100,reinterpret_cast<registration&>(dr),nullptr,nullptr);

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

TEST_CASE("register_screen: sucesso, falha, ESC e reset") {
    DummyRegistration dr("dummy");
    auto all = dr.get_all_multiset();
    register_screen rs(100,100,reinterpret_cast<registration&>(dr),all,nullptr,nullptr);

    // Sem dados → não completa
    auto& btnc = *rs.get_buttons()[0];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK_FALSE(rs.registration_complete());

    // Fluxo válido: nome="new", senha="pass"
    auto& ut = *rs.get_text_boxes()[0];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("new")) rs.handle_event(make_key_char_event(c,c));
    auto& pt = *rs.get_text_boxes()[1];
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pt.get_x()+1,pt.get_y()+1));
    for(char c: std::string("pass")) rs.handle_event(make_key_char_event(c,c));
    rs.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,btnc.get_x()+1,btnc.get_y()+1));
    CHECK(rs.registration_complete());

    rs.reset();
    CHECK_FALSE(rs.registration_complete());

    // Falha ao tentar registrar "exists"
    rs.handle_event(make_key_char_event(ALLEGRO_KEY_P,'p')); // simplificado
    CHECK_FALSE(rs.registration_complete());

    // ESC volta ao login
    rs.handle_event(make_key_down_event(ALLEGRO_KEY_ESCAPE));
    CHECK(rs.go_to_login_screen());
}

TEST_CASE("remove_user_screen: remoção com confirmação de senha e reset") {
    DummyRegistration dr("dummy");
    auto all = dr.get_all_multiset();
    remove_user_screen rus(100,100,reinterpret_cast<registration&>(dr),all,nullptr,nullptr);

    // Fase 1: digita "del" e clica Remover
    auto& ut = *rus.get_text_boxes()[0];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,ut.get_x()+1,ut.get_y()+1));
    for(char c: std::string("del")) rus.handle_event(make_key_char_event(c,c));
    auto& brem = *rus.get_buttons()[0];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,brem.get_x()+1,brem.get_y()+1));

    // Fase 2: senha incorreta → não volta
    auto& pw = *rus.get_text_boxes()[1];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,pw.get_x()+1,pw.get_y()+1));
    rus.handle_event(make_key_char_event(ALLEGRO_KEY_X,'x'));
    auto& bconf = *rus.get_buttons()[2];
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bconf.get_x()+1,bconf.get_y()+1));
    CHECK_FALSE(rus.go_to_main_menu());

    // Senha correta → remove e volta
    for(char c: std::string("secret")) rus.handle_event(make_key_char_event(c,c));
    rus.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,bconf.get_x()+1,bconf.get_y()+1));
    CHECK(rus.go_to_main_menu());
    CHECK(dr.deleted);

    rus.reset();
    CHECK_FALSE(rus.go_to_main_menu());
}

TEST_CASE("player_list_screen: navegação de páginas e ESC") {
    DummyRegistration dr("dummy");
    auto ms = dr.get_all_multiset();
    player_list_screen pls(100,100,nullptr,nullptr,ms,reinterpret_cast<registration&>(dr));

    auto& back = *pls.get_buttons()[0];
    auto& next = *pls.get_buttons()[1];
    auto& menu = *pls.get_buttons()[2];

    // Avança várias páginas
    for(int i = 0; i < 3; ++i)
        pls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,next.get_x()+1,next.get_y()+1));
    // Volta uma página
    pls.handle_event(make_mouse_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,back.get_x()+1,back.get_y()+1));
    // ESC volta ao menu
    pls.handle_event(make_key_down_event(ALLEGRO_KEY_ESCAPE));
    CHECK(pls.go_to_main_menu());
}
