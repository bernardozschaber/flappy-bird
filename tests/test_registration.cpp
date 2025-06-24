/**
 * @file test_registration.cpp
 * @brief Testes unitários para a classe de registro.
 * @details Valida a criação de jogadores e manipulação dos métodos principais no arquivo.
 */

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "registration.hpp"

//ANTES DE INICIAR OS TESTES, VERIFIQUE SE O ARQUIVO "registro_teste.txt" ESTÁ VAZIO

/**
 * @brief Main com o objetivo de permitir o fechamento instantâneo do programa caso haja algum problema na abertura ou tamanho do arquivo.
 */
int main(int argc, char** argv) {
    doctest::Context context;
    //Qualquer falha de resultado, o programa é abortado
    context.setOption("abort-after", 1); // para na 1ª falha
    context.setOption("exit", true);     // encerra o programa após os testes

    context.applyCommandLine(argc, argv);
    int res = context.run();

    return res;
}


registration registro("../tests/registro_teste.txt"); /**< Instanciação de um objeto da classe de registro. */

/// @test Verifica se o arquivo foi aberto corretamente.
TEST_CASE("Arquivo aberto") {
    REQUIRE(registro.isOpenFile() == 1);
}

/// @test Verifica se o arquivo está vazio.
TEST_CASE("Arquivo vazio") {
    REQUIRE(registro.isFileEmpty() == true);
}

/// @test Testa se o retorno é válido para os jogadores.
TEST_CASE("Retorno da linha dos jogadores"){
    //Arquivo está vazio, logo não tem retorno
    CHECK(registro.get_stats("Maria") == "");

    //Adicionando um nome diferente de Maria
    registro.new_user("Carlos", "flappybird", 24, 2);
    //Verifica se retorna string vazia quando não encontra Maria
    CHECK(registro.get_stats("Maria") == "");

    //Adicionando Maria
    registro.new_user("Maria", "flappybird1", 15, 1);
    //Verifica se retorna a string com as informações dela quando a encontra
    CHECK(registro.get_stats("Maria") == "15 Maria flappybird1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.get_stats("Carlos") == "24 Carlos flappybird 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

    //Adicionando Roberto
    registro.new_user("Roberto", "flappy", 0, 0);
    //Verifica se retorna a string com as informações dela quando a encontra
    CHECK(registro.get_stats("Roberto") == "0 Roberto flappy 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.get_stats("Maria") == "15 Maria flappybird1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.get_stats("Carlos") == "24 Carlos flappybird 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
}

/// @test Testa se o método get_player retorna as informações corretamente.
TEST_CASE("Objeto com as informações dos jogadores"){
    player p;

    //Jogador não está cadastrado
    p = registro.get_player("Renato");
    CHECK(p.username == "");

    //Tentando buscar um jogador que está cadastrado
    p = registro.get_player("Carlos");
    //Retorna as informações do jogador
    CHECK(p.username == "Carlos");
    CHECK(p.score == 24);
    CHECK(p.get_password() == "flappybird");
    CHECK(p.games == 2);
    CHECK(p.jump_count == 0);
    CHECK(p.ground_deaths == 0);
    CHECK(p.pipe_deaths == 0);
}

/// @test Testa a atualização dos jogadores.
TEST_CASE("Atualização dos jogadores"){
    player p;

    //Tentativa de atualizar um player inexistente
    p.username = "Sofia";
    p.score = 20;
    p.jump_count = 3;
    registro.update(p);
    CHECK(registro.get_stats("Sofia") == "");

    //Atualiza o jogador Carlos
    p = registro.get_player("Carlos");
    p.score = 30;
    p.achievements[1] = true;
    p.jump_count = 11;
    p.pipe_deaths++;
    registro.update(p);
    CHECK(registro.get_stats("Carlos") == "30 Carlos flappybird 3 11 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

    //Atualiza a jogadora Maria
    p = registro.get_player("Maria");
    p.score = 45;
    p.achievements[5] = true;
    p.achievements[12] = true;
    p.ground_deaths++;
    p.jump_count = 8;
    registro.update(p);
    CHECK(registro.get_stats("Maria") == "45 Maria flappybird1 2 8 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0");

    //Atualiza o jogador Roberto
    p = registro.get_player("Roberto");
    p.score = 41;
    p.achievements[4] = true;
    p.achievements[15] = true;
    p.achievements[12] = true;
    p.ground_deaths++;
    p.jump_count = 41;
    registro.update(p);
    CHECK(registro.get_stats("Roberto") == "41 Roberto flappy 1 41 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 1");
}

/// @test Testa a remoção de jogadores.
TEST_CASE("Remoção de jogadores"){
    //Sofia não está registrada
    CHECK(registro.get_stats("Sofia") == "");
    //Tentativa de deletá-la
    CHECK(registro.delete_user("Sofia") == 0);

    //Verifica se a captura da linha está sendo da forma correta
    CHECK(registro.get_stats("Carlos") == "30 Carlos flappybird 3 11 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(registro.delete_user("Carlos") == 1);
    CHECK(registro.get_stats("Carlos") == "");
}

/// @test Testa as funções de retorno do jogador com maior score(username e score).
TEST_CASE("Jogador com maior score"){
    player p;
    
    //Adiciona um novo jogador
    registro.new_user("Luiz", "flappybird2", 30, 2);
    //Verifica se a Maria é a jogadora com maior score
    CHECK(registro.get_max_user() == "Maria");
    CHECK(registro.get_max_score() == 45);

    //Deleta Maria(O jogador com maior score deve ser o Roberto)
    registro.delete_user("Maria");
    CHECK(registro.get_max_user() == "Roberto");
    CHECK(registro.get_max_score() == 41);

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

/// @test Testa a função de retorno do multiset para verificar se os jogadores estão listados e posicionados da forma correta dentro do container.
TEST_CASE("Lista dos jogadores ordenados pelo score"){
    std::multiset<player> players;
    //Recebe todos os jogadores
    players = registro.get_all();
    auto it = players.begin();
    //Checa se o tamanho é igual a 4
    CHECK(players.size() == 4);
    //Jogador da primeira posição
    CHECK(it->username == "Rodney");
    CHECK(it->score == 130);
    CHECK(it->games == 15);
    CHECK(it->get_password() == "flappybird4");
    it++;
    //Jogador da segunda posição
    CHECK(it->username == "Fabio");
    CHECK(it->score == 110);
    CHECK(it->games == 21);
    CHECK(it->get_password() == "flappybird3");
    it++;
    //Jogador da terceira posição
    CHECK(it->username == "Roberto");
    CHECK(it->score == 41);
    CHECK(it->games == 1);
    CHECK(it->get_password() == "flappy");
    it++;
    //Jogador da quarta posição
    CHECK(it->username == "Luiz");
    CHECK(it->score == 30);
    CHECK(it->games == 2);
    CHECK(it->get_password() == "flappybird2");

    registro.new_user("Héctor", "flappybird5", 72, 2);
    players.clear();
    players = registro.get_all();
    CHECK(players.size() == 5);
}  

