#include "scenario.hpp"

// Construtor (opcional, caso não tenha)
scenario::scenario() : score(0) {}

// Getter do score
int scenario::get_score() const {
    return score;
}

// Reseta o score
void scenario::reset_score() {
    score = 0;
}

// Incrementa o score
void scenario::increment_score() {
    score++;
}

// Setter (opcional)
void scenario::set_score(int new_score) {
    score = new_score;
}
