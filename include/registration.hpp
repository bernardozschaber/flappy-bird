#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP
#include <fstream>
#include <string>

class registration {
private:
  std::fstream users;
  std::fstream champion;

public:
  registration(std::string arquivo, std::string champion);

  std::fstream get_users();
  std::fstream get_champion();

  void new_user(std::string name);
  // void list_users();
  std::string get_stats(std::string name); // retorna "null" se não existe

  int update(std::string user, int score);

  int get_max_score();
  std::string get_max_user();
};

#endif // REGISTRATION_HPP
