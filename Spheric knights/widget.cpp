#include "widget.h"
#include "unit.h"
#include <cstdlib>
#include <ctime>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(40, 40, 640, 860);
    srand((unsigned)time(NULL));
    loadPixmaps();
    createFloor();
    createArmies();
    createUnits();
    createConnections();
    instructions = new QLabel(this);
    instructions->setGeometry(10, 10, 500, 30);
    instructions->setStyleSheet("font-size: 12px");
    instructions->setText("F1 - Держать позицию; F2 - За мной; F3 - В атаку; 0 - все; 1 - мечники; 3 - лучники");
    t_animations->start(10);
}

void Widget::loadPixmaps() {
    f.load("Resources/floor.png");
    actions.resize(8);
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/human_dragon_child/%1.png").arg(i));
        actions[0]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/human_warrior/%1.png").arg(i));
        actions[1]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/human_rider/%1.png").arg(i));
        actions[2]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/human_archer/%1.png").arg(i));
        actions[3]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/dead_dragon_child/%1.png").arg(i));
        actions[4]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/dead_warrior/%1.png").arg(i));
        actions[5]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/dead_rider/%1.png").arg(i));
        actions[6]<<pix;
    }
    for (int i = 0; i < 28; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/dead_archer/%1.png").arg(i));
        actions[7]<<pix;
    }
    for (int i = 0; i < 4; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/arrow%1.png").arg(i));
        arrow_states<<pix;
    }
    for (int i = 0; i < 11; ++i) {
        QPixmap pix;
        pix.load(QString("Resources/hp%1.png").arg(i));
        hp_states<<pix;
    }
}

void Widget::createFloor()
{
    floor = new QLabel(this);
    floor->setGeometry(0, 0, 640, 860);
    floor->setPixmap(f);
    animations.resize(1);
    t_animations = new QTimer;
    paints<<0<<1<<0<<2;
}

void Widget::createArmies()
{
    unit dragon_child, warrior, rider, archer;
    dragon_child.type = 0;
    dragon_child.hp = 200;
    dragon_child.max_hp = 200;
    dragon_child.attack = 10;
    dragon_child.attack_radius = 25;
    dragon_child.unit_size = 10;
    dragon_child.speed = 30;
    dragon_child.mod_speed = 30;
    dragon_child.cooldown = 0;

    warrior.type = 1;
    warrior.hp = 100;
    warrior.max_hp = 100;
    warrior.attack = 10;
    warrior.attack_radius = 25;
    warrior.unit_size = 10;
    warrior.speed = 8;
    warrior.mod_speed = 8;
    warrior.cooldown = 0;

    rider.type = 2;
    rider.hp = 150;
    rider.max_hp = 150;
    rider.attack = 20;
    rider.attack_radius = 40;
    rider.unit_size = 10;
    rider.speed = 30;
    rider.mod_speed = 30;
    rider.cooldown = 0;

    archer.type = 3;
    archer.hp = 50;
    archer.max_hp = 50;
    archer.attack = 5;
    archer.attack_radius = 300;
    archer.unit_size = 10;
    archer.speed = 10;
    archer.mod_speed = 10;
    archer.cooldown = 0;

    army_1.resize(20);
    army_2.resize(20);
    for (int i = 0; i < army_1.size(); ++i) {
        int r = rand() % 3;
        army_1[i] = r ? warrior : archer;
        //army_1[i] = archer;
    }

    for (int i = 0; i < army_2.size(); ++i) {
        int r = rand() % 3;
        army_2[i] = r ? warrior : archer;
        //army_2[i] = warrior;
    }

    units.resize(1);
    units[0] = dragon_child;
}

void Widget::createUnits() {
    int size = army_1.size() + army_2.size() + 1;
    units.resize(size);
    animations.resize(size);
    hp.resize(size);
    index.resize(size);
    target_x.resize(size);
    target_y.resize(size);
    arrow_x.resize(size);
    arrow_y.resize(size);

    arrows.resize(size);
    for (int i = 0; i < arrows.size(); ++i) {
        QLabel *l = new QLabel(this);
        arrows[i] = l;
    }

    units[0].x = 200;
    units[0].y = 50;
    units[0].gox = 200;
    units[0].goy = 50;
    units[0].fraction = 0;
    units[0].direction = 0;
    units[0].action = 1;
    units[0].step = 0;
    units[0].fight = 0;
    QLabel *l = new QLabel(this);
    animations[0] = l;
    QLabel *h = new QLabel(this);
    hp[0] = h;
    index[0] = 0;

    for (int i = 1; i < army_1.size() + 1; ++i) {
        units[i] = army_1[i - 1];
        units[i].x = 100 + 21 * i;
        units[i].y = 100;
        units[i].gox = 100 + 21 * i;
        units[i].goy = 100;
        units[i].fraction = 0;
        units[i].direction = 0;
        units[i].action = 2;
        units[i].step = 0;
        units[0].fight = 0;
        index[i] = i;
        QLabel *l = new QLabel(this);
        animations[i] = l;
        QLabel *h = new QLabel(this);
        hp[i] = h;
    }
    for (int i = army_1.size() + 1; i < army_1.size() + army_2.size() + 1; ++i) {
        units[i] = army_2[i - 1 - army_1.size()];
        units[i].x = 100 + 21 * (i - army_1.size());
        units[i].y = 800;
        units[i].gox = 100 + 21 * (i - army_1.size());
        units[i].goy = 800;
        units[i].fraction = 1;
        units[i].direction = 0;
        units[i].action = 2;
        units[i].step = 0;
        units[0].fight = 0;
        index[i] = i;
        QLabel *l = new QLabel(this);
        animations[i] = l;
        QLabel *h = new QLabel(this);
        hp[i] = h;
    }
}

void Widget::createConnections()
{
    connect(t_animations, SIGNAL(timeout()), this, SLOT(slotAnimations()));
}

void Widget::slotAnimations() {
    if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_LEFT)) {
        units[0].gox = units[0].x - sqrt(2) / 2 * units[0].speed / 30.0;
        units[0].goy = units[0].y - sqrt(2) / 2 * units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_LEFT)) {
        units[0].gox = units[0].x - sqrt(2) / 2 * units[0].speed / 30.0;
        units[0].goy = units[0].y + sqrt(2) / 2 * units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_RIGHT)) {
        units[0].gox = units[0].x + sqrt(2) / 2 * units[0].speed / 30.0;
        units[0].goy = units[0].y - sqrt(2) / 2 * units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_RIGHT)) {
        units[0].gox = units[0].x + sqrt(2) / 2 * units[0].speed / 30.0;
        units[0].goy = units[0].y + sqrt(2) / 2 * units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_UP)) {
        units[0].goy = units[0].y - units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_DOWN)) {
        units[0].goy = units[0].y + units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_LEFT)) {
        units[0].gox = units[0].x - units[0].speed / 30.0;
    } else if (GetAsyncKeyState(VK_RIGHT)) {
        units[0].gox = units[0].x + units[0].speed / 30.0;
    }
    if (GetAsyncKeyState(VK_F1)) {
        for (int i = 0; i < units.size(); ++i){
            if (units[i].fraction == 0 && i != 0) {
                if (type == 0) {
                    units[i].action = 0;
                } else if (units[i].type == type) {
                    units[i].action = 0;
                }
            }
        }
    } else if (GetAsyncKeyState(VK_F2)) {
        for (int i = 1; i < units.size(); ++i){
            if (units[i].fraction == 0 && i != 0) {
                if (type == 0) {
                    units[i].action = 1;
                } else if (units[i].type == type) {
                    units[i].action = 1;
                }
            }
        }
    } else if (GetAsyncKeyState(VK_F3)) {
        for (int i = 1; i < units.size(); ++i){
            if (units[i].fraction == 0 && i != 0) {
                if (type == 0) {
                    units[i].action = 2;
                } else if (units[i].type == type) {
                    units[i].action = 2;
                }
            }
        }
    } else if (GetAsyncKeyState(0x30)) {
        type = 0;
    } else if (GetAsyncKeyState(0x31)) {
        type = 1;
    } else if (GetAsyncKeyState(0x33)) {
        type = 3;
    }

    for (int i = 0; i < units.size() - 1; ++i) {
        for (int j = i + 1; j < units.size(); ++j) {
            if (units[index[i]].y > units[index[j]].y) {
                swap(index[i], index[j]);
            }
        }
    }

    floor->raise();
    instructions->raise();

    for (int k = 0; k < units.size(); ++k) {
        int i = index[k];
        int size = units[i].unit_size * 32 / 10;

        units[i].step += 1;
        units[i].step %= 80;
        if (units[i].cooldown > 0) {
            --units[i].cooldown;
        }

        if (i != 0) {
            if (units[i].action == 0) {
                if (units[i].fraction == 0) {
                    units[i].gox = units[i].x;
                    units[i].goy = units[i].y;
                }
            }

            if (units[i].action == 1) {
                if (units[i].fraction == 0) {
                    units[i].gox = units[0].x;
                    units[i].goy = units[0].y;
                }
            }

            if (units[i].action == 2) {
                double distance = 2000;
                for (int j = 0; j < units.size(); ++j) {
                    if (units[j].fraction != units[i].fraction && units[i].fight == 0) {
                        if (distance > sqrt((units[i].x - units[j].x) * (units[i].x - units[j].x) + (units[i].y - units[j].y) * (units[i].y - units[j].y))) {
                            distance = sqrt((units[i].x - units[j].x) * (units[i].x - units[j].x) + (units[i].y - units[j].y) * (units[i].y - units[j].y));
                            units[i].gox = units[j].x;
                            units[i].goy = units[j].y;
                        }
                    }
                }
            }
        }

        animations[i]->raise();
        hp[i]->raise();
        double x = units[i].x, y = units[i].y;
        double gx = units[i].gox, gy = units[i].goy;
        if (!(x == gx && y == gy) && units[i].fight == 0) {
            if (units[i].fight == 1) {
                units[i].step = 1;
            }
            double cos = (gx - x) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));
            double sin = (gy - y) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));
            if (units[i].step == 1 && i != 0) {
                units[i].mod_speed = (i == 0) ? 30 : units[i].speed - 5 + rand() % 10;
            }
            units[i].x += units[i].mod_speed * cos / 80;
            units[i].y += units[i].mod_speed * sin / 80;
            if ((x - gx) * (units[i].x - gx) < 0 || (y - gy) * (units[i].y - gy) < 0) {
                units[i].x = gx;
                units[i].y = gy;
            }
            int cx = round(x), cy = round(y);
            hp[i]->setGeometry(cx - 5, cy - size - 3, 20, 2);
            animations[i]->setGeometry(cx - size / 2, cy - size, size, size);
            if (cos >= - sqrt(3)/2 && cos <= sqrt(3)/2 && sin < 0) {
                animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][6 + paints[units[i].step/20]]);
                units[i].direction = 2;
            } else if (cos >= - sqrt(3)/2 && cos <= sqrt(3)/2 && sin > 0) {
                animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][paints[units[i].step/20]]);
                units[i].direction = 0;
            } else if (cos > 0) {
                animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][3 + paints[units[i].step/20]]);
                units[i].direction = 1;
            } else {
                animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][9 + paints[units[i].step/20]]);
                units[i].direction = 3;
            }
        } else {
            int cx = round(x), cy = round(y);
            hp[i]->setGeometry(cx - 5, cy - size - 3, 20, 2);
            animations[i]->setGeometry(cx - size / 2, cy - size, size, size);
            animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][3 * units[i].direction]);
        }

        for (int j = 0; j < units.size(); ++j) {
            if (i != j) {
                double distance = sqrt((units[i].x - units[j].x) * (units[i].x - units[j].x) + (units[i].y - units[j].y) * (units[i].y - units[j].y));
                if (distance < units[i].unit_size + units[j].unit_size) {
                    double cos1 = (units[i].x - units[j].x) / distance;
                    double sin1 = (units[i].y - units[j].y) / distance;
                    units[i].x += (units[i].unit_size + units[j].unit_size - distance) * cos1 / 2.0;
                    units[i].y += (units[i].unit_size + units[j].unit_size - distance) * sin1 / 2.0;
                    units[j].x -= (units[i].unit_size + units[j].unit_size - distance) * cos1 / 2.0;
                    units[j].y -= (units[i].unit_size + units[j].unit_size - distance) * sin1 / 2.0;
                }
            }
        }

        int nn = i;
        int distance = 2000;

        for (int j = 0; j < units.size(); ++j) {
            if (units[j].fraction != units[i].fraction) {
                if (distance > sqrt((units[i].x - units[j].x) * (units[i].x - units[j].x) + (units[i].y - units[j].y) * (units[i].y - units[j].y))) {
                    distance = sqrt((units[i].x - units[j].x) * (units[i].x - units[j].x) + (units[i].y - units[j].y) * (units[i].y - units[j].y));
                    nn = j;
                }
            }
        }

        if (units[i].attack_radius > distance && units[i].action != 1) {
            if (units[i].cooldown == 0) {
                if (units[i].fight == 0) {
                    units[i].step = 1;
                }
                units[i].gox = units[i].x;
                units[i].goy = units[i].y;
                units[i].fight = 1;
                int xi = units[i].x, yi = units[i].y, xj = units[nn].x, yj = units[nn].y;
                double cos = (xj - xi) / sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
                double sin = (yj - yi) / sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
                if (cos >= - sqrt(3)/2 && cos <= sqrt(3)/2 && sin < 0) {
                    units[i].direction = 2;
                    animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][20 + units[i].step/20]);
                } else if (cos >= - sqrt(3)/2 && cos <= sqrt(3)/2 && sin > 0) {
                    units[i].direction = 0;
                    animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][12 + units[i].step/20]);
                } else if (cos > 0) {
                    units[i].direction = 1;
                    animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][16 + units[i].step/20]);
                } else {
                    units[i].direction = 3;
                    animations[i]->setPixmap(actions[units[i].fraction * 4 + units[i].type][24 + units[i].step/20]);
                }
                if (units[i].type == 1 || units[i].type == 2) {
                    if (units[i].step == 0) {
                        units[nn].hp -= (8 + rand() % 5) / 10.0 * units[i].attack;
                        if (units[nn].hp < 0) {
                            units[nn].hp = 0;
                        }
                    }
                } else if (units[i].type == 3) {
                    if (units[i].step == 0) {
                        int r = distance / 10;
                        int x = units[nn].x, y = units[nn].y;
                        int gx = units[nn].gox, gy = units[nn].goy;
                        int speed = units[nn].speed;
                        double cos1 = ((gx - x) == 0) ? 0 : (gx - x) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));
                        double sin1 = ((gy - y) == 0) ? 0 : (gy - y) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));
                        arrow_x[i] = units[i].x - 6;
                        arrow_y[i] = units[i].y - 3;
                        target_x[i] = units[nn].x + distance * cos1 * speed / 80 - r / 2 + rand() % r;
                        target_y[i] = units[nn].y + distance * sin1 * speed / 80 - r / 2 + rand() % r;
                        arrows[i]->setGeometry(units[i].x - 6, units[i].y - 16, 12, 6);
                        arrows[i]->setPixmap(arrow_states[units[i].direction]);
                        units[i].cooldown = 200;
                    }
                }
            }
        } else {
            units[i].fight = 0;
        }
        hp[i]->setPixmap(hp_states[units[i].hp * 10 / units[i].max_hp]);
    }

    for (int i = 0; i < arrows.size(); ++i) {
        double x = arrow_x[i], gx = target_x[i];
        double y = arrow_y[i], gy = target_y[i];
        double cos = (gx - x) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));
        double sin = (gy - y) / sqrt((gx - x) * (gx - x) + (gy - y) * (gy - y));

        arrows[i]->raise();

        if (arrow_x[i] == target_x[i] && arrow_y[i] == target_y[i]) {
            for (int j = 0; j < units.size(); ++j) {
                double r = sqrt((units[j].x - gx) * (units[j].x - gx) + (units[j].y - gy) * (units[j].y - gy));
                if (r < units[j].unit_size) {
                    units[j].hp -= (8 + rand() % 5) / 10.0 * units[i].attack;
                    if (units[j].hp < 0) {
                        units[j].hp = 0;
                    }
                }
            }
            arrow_x[i] = -20;
            arrow_y[i] = -20;
            target_x[i] = -20;
            target_y[i] = -20;
            arrows[i]->setGeometry(-20, -20, 12, 6);
        } else {
            arrow_x[i] = x + cos * 2;
            arrow_y[i] = y + sin * 2;
            if ((x - gx) * (arrow_x[i] - gx) < 0 || (y - gy) * (arrow_y[i] - gy) < 0) {
                arrow_x[i] = gx;
                arrow_y[i] = gy;
            }
            int cx = round(arrow_x[i]), cy = round(arrow_y[i]);
            arrows[i]->setGeometry(cx - 6, cy - 16, 12, 6);
        }
    }

    for (int i = 0; i < units.size(); ++i) {
        if (units[i].hp == 0) {
            for (int j = 0; j < index.size(); ++j) {
                if (index[j] == i) {
                    index.erase(index.begin() + j);
                    --j;
                } else if (index[j] > i) {
                    --index[j];
                }
            }
            animations.erase(animations.begin() + i);
            hp.erase(hp.begin() + i);
            units.erase(units.begin() + i);

            arrows.erase(arrows.begin() + i);
            target_x.erase(target_x.begin() + i);
            target_y.erase(target_y.begin() + i);
            arrow_x.erase(arrow_x.begin() + i);
            arrow_y.erase(arrow_y.begin() + i);
            --i;
        }
    }
}

Widget::~Widget()
{

}
