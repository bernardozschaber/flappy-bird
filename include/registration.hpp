#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP
#include <fstream>
#include <string>
#include <vector>

struct player{
  std::string username;
  int score, games;
};

class registration {
private:
  std::fstream users;
  std::string file;
  bool openfile_check = 0;
  std::streampos pos_champion;
  int score_champion = 0;
  std::vector<player> players;


//score, username, password, games 
public:
  registration(std::string arquivo);

  bool isFileEmpty();

  int getline_number(std::string user);

  void new_user(std::string name, std::string password, int score, int games);

  std::string get_stats(std::string name); // retorna "null" se não existe

  std::vector<player> get_all(); //resgata as informações de todos os jogadores, exceto senha

  void update(std::string user, int score);

  void delete_user(std::string user);

  int get_max_score();

  std::string get_max_user();

  void update_champion();

  bool isOpenFile(){
    return openfile_check;
  }

  ~registration();
};

#endif // REGISTRATION_HPP
