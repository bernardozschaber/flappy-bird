#ifndef SCORE_HPP
#define SCORE_HPP

class Score {
private:
    float current_score;

public:
    Score(); 

    float get_score() const;

    void reset_score();

    void increment_score_standard_pipe();

    void increment_score_golden_pipe();

    void set_score(float new_score);
};

#endif // SCORE_HPP
