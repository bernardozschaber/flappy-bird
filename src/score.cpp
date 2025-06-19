#include "score.hpp"

// Construtor
Score::Score() : current_score(0.0f) {}

// Getter do score
float Score::get_score() const {
    return current_score;
}

// Reseta o score
void Score::reset_score() {
    current_score = 0.0f;
}

// Incrementa o score
void Score::increment_score() {
    current_score += 1.0f;
}

// Setter
void Score::set_score(float new_score) {
    current_score = new_score;
}
