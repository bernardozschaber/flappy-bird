#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP
#include <fstream>
#include <string>
#include <vector>

//Struct com informações dos jogadores para auxiliar na lista de retorno  
struct player{
  std::string username;
  int score, games;
};

class registration {
private:
  //Variável que permitirá acesso ao arquivo
  std::fstream users;

  std::string file;

  //Flag para checagem de abertura do arquivo
  bool openfile_check;

  //Armazena posição do jogador com maior score
  std::streampos pos_champion;

  //Maior score do jogo
  int score_champion = 0;

  //Armazena informações dos jogadores registrados
  std::vector<player> players;
  
  //Função auxiliar para ordenação dos usernames em ordem alfabética
  static bool compare_username(const player& r1, const player& r2);
  
  //Atualiza o novo campeão
  void update_champion();

  //Retorna a linha do jogador correspondente do .txt
  int getline_number(std::string user);

public:
  registration(std::string arquivo);

  //Verifica se o arquivo está vazio
  bool isFileEmpty();

  //Realiza o cadastro do jogador
  void new_user(std::string name, std::string password, int score, int games);

  //Captura a linha com as infos do jogador
  std::string get_stats(std::string name);

  //Resgata as informações de todos os jogadores, exceto senha
  std::vector<player> get_all();

  //Atualiza o score do jogador
  void update(std::string user, int score);

  //Deleta o jogador
  void delete_user(std::string user);

  //Obtém o maior score do jogo
  int get_max_score();

  //Obtém o username do campeão
  std::string get_max_user();

  //Verifica se o arquivo está aberto
  bool isOpenFile(){
    return openfile_check;
  }

  //Destrutor da classe
  ~registration();
};

#endif // REGISTRATION_HPP
