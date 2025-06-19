#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <optional>

//Struct com informações dos jogadores para auxiliar na lista de retorno  
struct player{
  std::string username = "";
  int score = 0, games = 0;
  std::vector<bool> achievements;

  //Sobrecarga no operador < para colocar em ordem descrescente de score dentro do container multiset
  bool operator < (const player& otherplayer) const{
    return score > otherplayer.score;
  }
};

class registration {
private:
  //Variável que permitirá acesso ao arquivo
  std::fstream users;

  std::string file;

  //Flag para checagem de abertura do arquivo
  bool openfile_check = false;

  //Armazena posição do jogador com maior score
  std::streampos pos_champion;

  //Maior score do jogo
  int score_champion = 0;

  //Armazena informações dos jogadores registrados
  std::multiset<player> players;
  
  //Retorna a linha do jogador correspondente do .txt
  int getline_number(std::string user);

public:
  //Construtor da classe
  registration(std::string arquivo);

  //Verifica se o arquivo está vazio
  bool isFileEmpty();

  //Realiza o cadastro do jogador
  void new_user(std::string name, std::string password, int score, int games);

  //Captura a linha com as infos do jogador
  std::string get_stats(const std::string& name);

  //Captura as informações do usuário e retorna o objeto preenchido
  player get_player(const std::string& name);

  //Resgata as informações de todos os jogadores, exceto senha
  std::multiset<player> get_all();

  //Atualiza as informações do usuário
  void update(player& player_stats);

  //Deleta o jogador
  int delete_user(std::string user);

  //Obtém o maior score do jogo
  int get_max_score();

  //Obtém o username do campeão
  std::string get_max_user();

  //Atualiza o novo campeão
  void update_champion();

  //Verifica se o arquivo está aberto
  bool isOpenFile();

  //Destrutor da classe
  ~registration();
};

#endif // REGISTRATION_HPP
