#ifndef UNIT_H
#define UNIT_H

using namespace std;

class unit {
public:
    int fraction;
    int type;
    int attack_radius;
    int unit_size;
    int attack;
    int hp, max_hp;
    int speed;
    int step;
    int cooldown;
    bool fight;
    double mod_speed;
    double x, y;
    double gox, goy;
    short int action;
    int direction;
};

#endif // UNIT_H
