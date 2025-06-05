#ifndef SCENARIO_HPP
#define SCENARIO_HPP

class scenario {
private:
    int score;

public:
    scenario(); 

    int get_score() const;

    void reset_score();

    void increment_score();

    void set_score(int new_score);

};


#endif // SCENARIO_HPP