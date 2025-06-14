#include "registration.hpp"
#include <sstream>
#include <algorithm>
#include <vector>


registration::registration(std::string file){
    this->file = file;

    //Abre o arquivo de banco de dados dos jogadores
    users.open(file, std::ios::in | std::ios::out | std::ios::app);

    //Verifica se foi aberto com sucesso
    if(users.is_open()){
        openfile_check = 1;
    }
}


registration::~registration(){
    //Fecha o arquivo caso ele esteja aberto
    if(users.is_open()) {
        users.close();
    }
}

bool registration::isFileEmpty(){
    //Limpa possíveis flags de erro do stream e verifica se o tamanho do arquivo é nulo
    users.clear();
    users.seekg(0, std::ios::end);
    return users.tellg() == 0;
}

bool registration::isOpenFile(){
    return openfile_check;
}

void registration::new_user(std::string name, std::string password, int score, int games){
    //Insere o novo usuário no final do arquivo
    users.clear();
    users.seekp(0, std::ios::end);

    //Escreve as informações do player no arquivo
    users << score << " " << name << " " << password << " " << games << "\n";

    //Verifica a possibilidade de atualizar o campeão
    if(score > get_max_score()){
        update_champion();
    }
}

std::string registration::get_stats(std::string name){
    std::string word, line;
    std::streampos pos;
    int counter = 0;

    //Retorna uma string vazia caso o arquivo esteja vazio
    if(isFileEmpty()){
        return "";
    }

    //Reposiciona o ponteiro de leitura para o início do arquivo
    users.seekg(0, std::ios::beg);

    //Loop para percorrer todo o arquivo
    while(!users.eof()){
        counter = 0;
        pos = users.tellg();

        //Captura o username do usuário
        while(counter <= 1){
            users >> word;
            counter++;
        }

        //Tenta localizar o username passado como parametro no arquivo
        //Em caso positivo, retorna a linha do mesmo
        if(word == name){
            users.seekg(pos);
            std::getline(users, line);
            return line;
        }
        std::getline(users, line);
    }

    //Retorna string vazia caso não encontre o jogador
    return "";

}

std::multiset<player> registration::get_all(){
    users.clear();
    players.clear();
    users.seekg(0, std::ios::beg);
    int score, games;
    std::string username, line, trash;

    //Adiciona todos os usuários em um set
    while(users.peek() != EOF){
        users >> score;
        users >> username;
        users >> trash;
        users >> games;
        player p = {username, score, games};
        players.insert(p);
        getline(users, line);
    }
    //Retorna a estrutura com os players ordenados pelo nome
    return players;
}

void registration::update(std::string user, int score){
    std::vector<std::string> lines;
    int counter = 0;
    int games, new_score;
    std::string password;

    //Recebe a linha correspondente ao jogador
    std::string line = get_stats(user);

    //Caso não encontre o jogador 
    if(line == ""){
        return;
    }

    //Cria uma stringstream para possibilitar a leitura de dados
    std::stringstream line_user(line);

    //Obtém as informações do jogador
    while(counter < 4){
        counter++;
        if(counter == 1){
            line_user >> new_score;
        }else if(counter == 4){
            line_user >> games;
        }else if(counter == 3){
            line_user >> password;
        }else{
            line_user >> line;
        }
    }

    //Atualiza a pontuação
    new_score = score;
    //Incrementa a quantidade de jogos do jogador
    games++;

    int currentLine = 0;
    //Localizar a linha que deseja mudar
    int targetLine = getline_number(user);

    // Lê todas as linhas do arquivo
    users.clear();
    users.seekg(0, std::ios::beg);
    //Obtém todas as linhas e insere no vector
    while (std::getline(users, line)) {
        if (currentLine == targetLine - 1) {
            // Altere a linha conforme necessário
            line = std::to_string(new_score) + " " + user + " " + password + " " + std::to_string(games);
        }
        lines.push_back(line);
        currentLine++;
    }
    users.close();

    // Escreve de volta no arquivo (sobrescreve o original)
    users.open(file, std::ios::out | std::ios::trunc);
    for (const auto& l : lines) {
        users << l << "\n";
    }

    users.close();
    //Reabre o arquivo
    users.open(file, std::ios::in | std::ios::out);
    //Verifica a possibilidade de atualizar o campeão
    if(score > get_max_score()){
        update_champion();
    }
}

int registration::delete_user(std::string user){
    std::vector<std::string> lines;
    std::string line;
    int currentLine = 0;

    //Localizar a linha que deseja remover
    int targetLine = getline_number(user);

    //Caso não encontre o usuário
    if(targetLine == 0)
            return 0;

    // Lê todas as linhas do arquivo
    users.clear();
    users.seekg(0, std::ios::beg);
    while (std::getline(users, line)) {
        if (currentLine != targetLine - 1) {
            // Não insere a linha que se deseja remover no vetor
            lines.push_back(line);
        }
        currentLine++;
    }
    users.close();

    // Escreve de volta no arquivo (sobrescreve o original)
    users.open(file, std::ios::out | std::ios::trunc);
    for (const auto& l : lines) {
        users << l << "\n";
    }

    users.close();
    //Reabre o arquivo
    users.open(file, std::ios::in | std::ios::out);

    update_champion();
    return 1;
}

int registration::get_max_score(){
    int max_score;

    users.clear();
    //Posiciona o ponteiro de leitura para a linha do campeão
    users.seekg(pos_champion);

    //Leitura da pontuação
    users >> max_score;
    return max_score;
}

void registration::update_champion(){
    std::string line;
    std::streampos pos_max = 0;
    int score;
    score_champion = -1;

    users.clear();
    users.seekg(0, std::ios::beg);

    while (users.peek() != EOF) {
        //Salva a posição do início da linha
        std::streampos pos = users.tellg(); 
        std::getline(users, line);

        //Ignora linhas vazias
        if (line.empty()) continue; 

        std::istringstream iss(line);
        iss >> score;

        if (score > score_champion) {
            score_champion = score;
            //Salva a posição da linha com maior score
            pos_champion = pos; 
        }
    }
}

int registration::getline_number(std::string user){
    std::string word, line;
    std::streampos pos;
    int counter = 0, linenumber = 0;

    users.clear();
    //Reposiciona o ponteiro de leitura para o início do arquivo
    users.seekg(0, std::ios::beg);

    while(!users.eof()){
        counter = 0;
        linenumber++;
        //Salva a posição do início da linha
        pos = users.tellg();

        while(counter <= 1){
            users >> word;
            counter++;
        }

        //Retorna o número da linha
        if(word == user){
            return linenumber;
        }
        std::getline(users, line);
    }

    return 0;
}

std::string registration::get_max_user(){
    std::string user;
    int contador = 0;

    users.clear();
    //Posiciona o ponteiro de leitura para a linha do campeão
    users.seekg(pos_champion);

    //Leitura do usuário com maior pontuação
    while(contador < 2){
        contador++;
        users >> user;
    }

    return user;
}

