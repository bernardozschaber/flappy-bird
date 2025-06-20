#include "score.hpp"


Score::Score() : current_score(0.0f) {}


float Score::get_score() const {
    return current_score;
}


void Score::reset_score() {
    current_score = 0.0f;
}

void Score::increment_score_standard_pipe() {
    current_score=current_score+0.5;
}

void Score::increment_score_golden_pipe() {
    current_score=current_score+1.5;
}


void Score::set_score(float new_score) {
    current_score = new_score;
}
