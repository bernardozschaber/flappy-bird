/**
 * @file registration.hpp
 * @brief Declaração da classe de registro para execução de diversos comandos no arquivo txt
 * 
 * Este arquivo contém a definição da classe de registro, responsável pelo armazenamento, captura e atualização dos dados dos jogadores
 * Inclui métodos principais para o manejamento do arquivo durante o jogo
 */

#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <fstream>
#include <string>
#include <set>
#include <vector>

/**
 * @struct player
 * @brief Struct que representa um jogador.
 * 
 * A struct player gerencia os dados de um jogador, como 
 * nome de usuário, pontuação, número de partidas jogadas, password, conquistas e variáveis auxiliares de conquista.
 */ 
struct player{

private: 
  std::string password = "";  /**< Senha do jogador. */
  
public:
  std::string username = "";  /**< Nome de usuário do jogador. */
  int score = 0;              /**< Pontuação atual do jogador. */  
  int games = 0;              /**< Quantidade de jogos jogados. */
  std::vector<bool> achievements; /**< Conquistas desbloqueadas pelo jogador. */

 /**
  * @brief Variáveis auxiliares para o desbloqueio de determinadas conquistas.
  */
  int jump_count = 0, ground_deaths = 0, pipe_deaths = 0;
  
 /**
  * @brief Construtor padrão.
  */
  player(){}

 /**
  * @brief Construtor que inicializa o jogador com todos os atributos da struct.
  * @param username Nome do jogador.
  * @param password Senha do jogador.
  * @param score Pontuação inicial.
  * @param games Número inicial de jogos.
  * @param jump_count Número de pulos executados pelo jogador.
  * @param ground_deaths Número de mortes no chão.
  * @param pipe_deaths Número de mortes no cano.
  */
  player(const std::string& username, const std::string& password, int score, int games, int jump_count, int ground_deaths, int pipe_deaths) : username(username), score(score), games(games), password(password), jump_count(jump_count), ground_deaths(ground_deaths), pipe_deaths(pipe_deaths) {}

  /**
  * @brief Construtor que inicializa o jogador com username, password, score e games.
  * @param username Nome do jogador.
  * @param password Senha do jogador.
  * @param score Pontuação inicial.
  * @param games Número inicial de jogos.
  */
  player(const std::string& username, const std::string& password, int score, int games) : username(username), password(password), score(score), games(games) {}

  /**
  * @brief Sobrecarga no operador < para colocar em ordem descrescente de score dentro do container multiset
  * @param otherplayer Objeto do tipo player de outro jogador.
  * @return Maior score dentre os scores comparados.
  */
  bool operator < (const player& otherplayer) const{
    return score > otherplayer.score;
  }

  /**
  * @brief Obtém a senha do jogador.
  * @return Senha do jogador.
  */
  std::string get_password() const{
    return password;
  }
  
};

/**
 * @class registration
 * @brief Classe que realiza operações dentro do arquivo.
 * 
 * A classe registration permite inserções, remoções, atualizações, captura de dados dos jogadores que estarão presentes no arquivo.
 */ 
class registration {
private:
  std::fstream users; /**< Variável que permitirá acesso ao arquivo. */

  std::string file; /**< Nome do arquivo. */

  bool openfile_check = false;  /**< Flag para checagem de abertura do arquivo. */

  std::streampos pos_champion;  /**< Armazena a posição do ponteiro de leitura onde se localiza o jogador com maior score. */

  int score_champion = 0; /**< Maior score do jogo. */
  
 /**
  * @brief Retorna a linha do jogador correspondente.
  * @param user Nome do usuário.
  * @return Número da linha do jogador no arquivo.
  */
  int getline_number(std::string user);

public:
 /**
  * @brief Construtor da classe.
  * @param arquivo Nome do arquivo.
  */
  registration(std::string arquivo);

 /**
  * @brief Verifica se o arquivo está vazio.
  * @return Booleano representando se o arquivo está vazio(true) ou false.
  */
  bool isFileEmpty();

 /**
  * @brief Cadastra um novo jogador.
  * @param name Nome do jogador.
  * @param password Senha do jogador.
  * @param score Pontuação inicial do jogador.
  * @param games Jogos jogados.
  */
  void new_user(std::string name, std::string password, int score, int games);

 /**
  * @brief Captura a linha do jogador no arquivo.
  * @param name Nome do jogador.
  * @return Linha com as informações do jogador.
  */
  std::string get_stats(const std::string& name);

 /**
  * @brief Captura as informações do jogador no arquivo.
  * @param name Nome do jogador.
  * @return Objeto com as todas as informações do jogador.
  */
  player get_player(const std::string& name);

 /**
  * @brief Resgata as informações de todos os jogadores, exceto senha.
  * @return Container Multiset ordenado pela pontuação de todos os jogadores.
  */
  std::multiset<player> get_all();

 /**
  * @brief Atualiza o arquivo com as informações de determinado jogador.
  * @param player_stats Objeto player com as informações do jogador a serem atualizadas.
  */
  void update(player& player_stats);

 /**
  * @brief Deleta o jogador.
  * @param user Nome do jogador.
  * @return Inteiro identificando se a exclusão foi bem sucedida(1) ou não (0).
  */
  int delete_user(std::string user);

 /**
  * @brief Obtém a maior pontuação do jogo.
  * @return Maior pontuação do jogo.
  */
  int get_max_score();

 /**
  * @brief Obtém o username do jogador com maior pontuação do jogo.
  * @return Username do jogador.
  */
  std::string get_max_user();

 /**
  * @brief Atualiza a posição do "possível" novo campeão após operações no arquivo.
  */
  void update_champion();

 /**
  * @brief Verifica se o arquivo está aberto.
  * @return Confirmação(true) ou false.
  */
  bool isOpenFile();

 /**
  * @brief Destrutor da classe que realiza o fechamento do arquivo(se for necessário).
  */
  ~registration();
};

#endif // REGISTRATION_HPP
