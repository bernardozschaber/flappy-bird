#include "registration.hpp"
#include <sstream>
#include <iostream>

registration::registration(std::string file){
    this->file = file;
    users.open(file, std::ios::in | std::ios::out);
    if(users.is_open()){
        openfile_check = 1;
    }
}

registration::~registration(){
    if(users.is_open()) {
        users.close();
    }
}

bool registration::isFileEmpty(){
    users.clear();
    users.seekg(0, std::ios::end);
    return users.tellg() == 0;
}

std::fstream registration::get_users(){
}

void registration::new_user(std::string name, std::string password, int score, int games){
    users.clear();
    users.seekp(0, std::ios::end);
    users << score << " " << name << " " << password << " " << games << "\n";
    if(score > get_max_score()){
        update_champion();
    }
}

std::string registration::get_stats(std::string name){
    std::string word, line;
    std::streampos pos;
    int counter = 0, find = 0;
    if(isFileEmpty()){
        return "";
    }
    users.seekg(0, std::ios::beg);
    while(!users.eof()){
        counter = 0;
        
        pos = users.tellg();
        while(counter <= 1){
            users >> word;
            counter++;
        }
        if(word == name){
            find = 1;
            users.seekg(pos);
            std::getline(users, line);
            return line;
        }
        std::getline(users, line);
    }
    return "";

}

std::vector<player> registration::get_all(){
    users.clear();
    users.seekg(0, std::ios::beg);
    int score, games;
    std::string username, line, trash;
    while(users.peek() != EOF){
        users >> score;
        std::cout << score << std::endl;
        users >> username;
        users >> trash;
        users >> games;
        player p = {username, score, games};
        players.push_back(p);
        getline(users, line);
    }
    return players;
}

void registration::update(std::string user, int score){
    std::vector<std::string> lines;
    int counter = 0;
    std::string games, current_score, password;
    std::string line = get_stats(user); 

    std::stringstream line_user(line);
    int scoreint, gamesint;
    while(counter < 4){
        counter++;
        if(counter == 1){
            line_user >> current_score;
            scoreint = std::stoi(current_score);
        }else if(counter == 4){
            line_user >> games;
            gamesint = std::stoi(games);
        }else if(counter == 3){
            line_user >> password;
        }else{
            line_user >> line;
        }
    }
    scoreint = score;
    gamesint += 1;
    int currentLine = 0;
    //Localizar a linha que deseja mudar
    int targetLine = getline_number(user);
    // Lê todas as linhas do arquivo
    users.clear();
    users.seekg(0, std::ios::beg);
    while (std::getline(users, line)) {
        if (currentLine == targetLine - 1) {
            // Altere a linha conforme necessário
            line = std::to_string(scoreint) + " " + user + " " + password + " " + std::to_string(gamesint);
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
    users.open(file, std::ios::in | std::ios::out);
    if(score > get_max_score()){
        update_champion();
    }
}

void registration::delete_user(std::string user){
    std::vector<std::string> lines;
    std::string line;
    int currentLine = 0;
    //Localizar a linha que deseja remover
    int targetLine = getline_number(user);
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
    users.open(file, std::ios::in | std::ios::out);
    update_champion();
}

int registration::get_max_score(){
    int max_score;
    users.clear();
    users.seekg(pos_champion);
    users >> max_score;
    return max_score;
}

void registration::update_champion() {
    std::string line;
    std::streampos pos_max = 0;
    int score;
    score_champion = -1; // ou 0, para reiniciar

    users.clear();
    users.seekg(0, std::ios::beg);

    while (users.peek() != EOF) {
        std::streampos pos = users.tellg(); // salva a posição do início da linha

        std::getline(users, line);

        if (line.empty()) continue; // ignora linhas vazias

        std::istringstream iss(line);
        iss >> score;

        if (score > score_champion) {
            score_champion = score;
            pos_champion = pos; // salva a posição da linha com maior score
        }
    }
}

int registration::getline_number(std::string user){
    users.clear();
    users.seekg(0, std::ios::beg);
    std::string word, line;
    std::streampos pos;
    int counter = 0, find = 0, linenumber = 0;
    while(!users.eof()){
        counter = 0;
        linenumber++;
        pos = users.tellg();
        while(counter <= 1){
            users >> word;
            counter++;
        }
        if(word == user){
            find = 1;
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
    users.seekg(pos_champion);
    while(contador < 2){
        contador++;
        users >> user;
    }
    return user;
}

// void registration::update_champion(){
//     std::string user_champion;
//     user_champion = get_max_user();
//     this->user_champion = user_champion;
// }