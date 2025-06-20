#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "registration.hpp"

//ANTES DE INICIAR OS TESTES DEIXE O ARQUIVO .TXT VAZIO

//Main para definir flags 
int main(int argc, char** argv) {
    doctest::Context context;
    //Qualquer falha de resultado, o programa é abortado
    context.setOption("abort-after", 1); // para na 1ª falha
    context.setOption("exit", true);     // encerra o programa após os testes

    context.applyCommandLine(argc, argv);
    int res = context.run();

    return res;
}

//Arquivo vazio
registration registro("jogadores.txt");

TEST_CASE("testing if file is open") {
    REQUIRE(registro.isOpenFile() == 1);
}

TEST_CASE("testing if file is empty") {
    REQUIRE(registro.isFileEmpty() == true);
}

TEST_CASE("testing if return of get_stats is correct"){
    //Arquivo está vazio, logo não tem retorno
    CHECK(registro.get_stats("Maria") == "");

    //Adicionando um nome diferente de Maria
    registro.new_user("Carlos", "flappybird", 24, 2);
    //Verifica se retorna string vazia quando não encontra Maria
    CHECK(registro.get_stats("Maria") == "");

    //Adicionando Maria
    registro.new_user("Maria", "flappybird1", 15, 1);
    //Verifica se retorna a string com as informações dela quando a encontra
    CHECK(registro.get_stats("Maria") == "15 Maria flappybird1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.get_stats("Carlos") == "24 Carlos flappybird 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
}

TEST_CASE("testing if return of get_player is correct"){
    player p;

    //Jogador não está cadastrado
    p = registro.get_player("Renato");
    CHECK(p.username == "");

    //Tentando buscar um jogador que está cadastrado
    p = registro.get_player("Carlos");
    //Retorna as informações do jogador
    CHECK(p.username == "Carlos");
    CHECK(p.score == 24);
    CHECK(p.password == "flappybird");
    CHECK(p.games == 2);
}

TEST_CASE("update method is working correctly?"){
    player p;

    //Tentativa de atualizar um player inexistente
    p.username = "Sofia";
    p.score = 20;
    registro.update(p);
    CHECK(registro.get_stats("Sofia") == "");

    //Atualiza o jogador Carlos
    p = registro.get_player("Carlos");
    p.score = 30;
    p.achievements[1] = true;
    registro.update(p);
    CHECK(registro.get_stats("Carlos") == "30 Carlos flappybird 3 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

    //Atualiza a jogadora Maria
    p = registro.get_player("Maria");
    p.score = 45;
    p.achievements[5] = true;
    p.achievements[12] = true;
    registro.update(p);
    CHECK(registro.get_stats("Maria") == "45 Maria flappybird1 2 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0");
}

TEST_CASE("delete_user method is working correctly?"){
    //Sofia não está registrada
    CHECK(registro.get_stats("Sofia") == "");
    //Tentativa de deletá-la
    CHECK(registro.delete_user("Sofia") == 0);

    //Verifica se a captura da linha está sendo da forma correta
    CHECK(registro.get_stats("Carlos") == "30 Carlos flappybird 3 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.delete_user("Carlos") == 1);
    CHECK(registro.get_stats("Carlos") == "");
}

TEST_CASE("method of best player(get_max_user() e get_max_score())"){
    player p;
    
    //Adiciona um novo jogador
    registro.new_user("Luiz", "flappybird2", 30, 2);
    //Verifica se a Maria é a jogadora com maior score
    CHECK(registro.get_max_user() == "Maria");
    CHECK(registro.get_max_score() == 45);

    //Deleta Maria(O jogador com maior score deve ser o Carlos)
    registro.delete_user("Maria");
    CHECK(registro.get_max_user() == "Luiz");
    CHECK(registro.get_max_score() == 30);

    //Adiciona um novo usuário com o maior score do jogo
    registro.new_user("Fabio", "flappybird3", 110, 21);
    //(O jogador com maior score deve ser o Fabio)
    CHECK(registro.get_max_user() == "Fabio");
    CHECK(registro.get_max_score() == 110);

    //Adiciona um novo usuário com o mesmo score do maior do jogo
    registro.new_user("Rodney", "flappybird4", 110, 14);
    CHECK(registro.get_max_user() == "Fabio");
    CHECK(registro.get_max_score() == 110);

    //Atualiza o jogador Rodney
    p = registro.get_player("Rodney");
    p.score = 130;
    registro.update(p);
    //Ele deve ser o jogador com maior score
    CHECK(registro.get_max_user() == "Rodney");
    CHECK(registro.get_max_score() == 130);

}

TEST_CASE("show all players registered sorting by score"){
    std::multiset<player> players;
    //Recebe todos os jogadores
    players = registro.get_all();
    auto it = players.begin();
    //Checa se o tamanho é igual a 3
    CHECK(players.size() == 3);
    //Jogador da primeira posição
    CHECK(it->username == "Rodney");
    CHECK(it->score == 130);
    CHECK(it->games == 15);
    it++;
    CHECK(it->username == "Fabio");
    CHECK(it->score == 110);
    CHECK(it->games == 21);
    it++;
    CHECK(it->username == "Luiz");
    CHECK(it->score == 30);
    CHECK(it->games == 2);

    registro.new_user("Héctor", "flappybird5", 72, 2);
    players.clear();
    players = registro.get_all();
    CHECK(players.size() == 4);
}  

