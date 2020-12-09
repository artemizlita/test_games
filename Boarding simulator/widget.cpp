#include "widget.h"
#include <cstdlib>
#include <ctime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(40, 40, 642, 600);
    srand((unsigned)time(NULL));
    createUnits();
    createArmies();
    t_animations = new QTimer(this);
    createConnections();
    t_animations->start(200);
}

void Widget::createUnits() {
    actions.resize(4);
    unit_type.resize(4);

    //soldier_1

    unit_type[0].fraction = 1;
    unit_type[0].type = 0;
    unit_type[0].hp = 100;
    unit_type[0].max_hp = 100;
    unit_type[0].attack = 20;
    unit_type[0].state = 0;
    unit_type[0].direction = 2;
    unit_type[0].state = 0;
    unit_type[0].fase = 0;
    unit_type[0].speed = 2;
    unit_type[0].attack_distance = 8;


    actions[0].resize(8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPixmap pix;
            pix.load(QString("textures/soldier_1/%1").arg(i) + QString("/%1").arg(j));
            actions[0][i]<<pix;
        }
    }

    //musketeer_1

    unit_type[1].fraction = 1;
    unit_type[1].type = 1;
    unit_type[1].hp = 80;
    unit_type[1].max_hp = 80;
    unit_type[1].attack = 5;
    unit_type[1].state = 0;
    unit_type[1].direction = 2;
    unit_type[1].state = 0;
    unit_type[1].fase = 0;
    unit_type[1].speed = 2;
    unit_type[1].attack_distance = 40;

    actions[1].resize(8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPixmap pix;
            pix.load(QString("textures/musketeer_1/%1").arg(i) + QString("/%1").arg(j));
            actions[1][i]<<pix;
        }
    }

    //soldier_2

    unit_type[2].fraction = 2;
    unit_type[2].type = 2;
    unit_type[2].hp = 100;
    unit_type[2].max_hp = 100;
    unit_type[2].attack = 20;
    unit_type[2].state = 0;
    unit_type[2].direction = 6;
    unit_type[2].state = 0;
    unit_type[2].fase = 0;
    unit_type[2].speed = 2;
    unit_type[2].attack_distance = 8;

    actions[2].resize(8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPixmap pix;
            pix.load(QString("textures/soldier_2/%1").arg(i) + QString("/%1").arg(j));
            actions[2][i]<<pix;
        }
    }

    //musketeer_2

    unit_type[3].fraction = 2;
    unit_type[3].type = 3;
    unit_type[3].hp = 80;
    unit_type[3].max_hp = 80;
    unit_type[3].attack = 5;
    unit_type[3].state = 0;
    unit_type[3].direction = 6;
    unit_type[3].state = 0;
    unit_type[3].fase = 0;
    unit_type[3].speed = 2;
    unit_type[3].attack_distance = 40;

    actions[3].resize(8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPixmap pix;
            pix.load(QString("textures/musketeer_2/%1").arg(i) + QString("/%1").arg(j));
            actions[3][i]<<pix;
        }
    }
}

void Widget::createArmies() {
    QPixmap f;
    f.load("textures/floor.png");
    //f = f.scaled(200, 175, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    floor = new QLabel(this);
    floor->setGeometry(0, 0, 642, 600);
    floor->setPixmap(f);

    //army_1

    int soldiers_1 = 100;
    int musketeers_1 = 20;

    army_1.resize(soldiers_1 + musketeers_1);

    //army_2

    int soldiers_2 = 100;
    int musketeers_2 = 20;

    army_2.resize(soldiers_2 + musketeers_2);

    num_anim.resize(army_1.size() + army_2.size());
    y_anim.resize(army_1.size() + army_2.size());

    for (int i = 0; i < soldiers_1; ++i) {
        army_1[i] = unit_type[0];
        army_1[i].x = rand() % 20 + 100;
        army_1[i].y = rand() % 450 + 100;
        //army_1[i].x = 200;
        //army_1[i].y = 200;
        QLabel * new_unit = new QLabel(this);
        new_unit->setPixmap(actions[army_1[i].type][army_1[i].direction][army_1[i].state]);
        army_1[i].unit_animation = new_unit;
        num_anim[i] = i;
        y_anim[i] = army_1[i].y;
    }

    for (int i = soldiers_1; i < soldiers_1 + musketeers_1; ++i) {
        army_1[i] = unit_type[1];
        army_1[i].x = rand() % 20 + 100;
        army_1[i].y = rand() % 450 + 100;
        //army_1[i].x = 100;
        //army_1[i].y = 100;
        QLabel * new_unit = new QLabel(this);
        new_unit->setPixmap(actions[army_1[i].type][army_1[i].direction][army_1[i].state]);
        army_1[i].unit_animation = new_unit;
        num_anim[i] = i;
        y_anim[i] = army_1[i].y;
    }

    for (int i = 0; i < soldiers_2; ++i) {
        army_2[i] = unit_type[2];
        army_2[i].x = rand() % 20 + 542;
        army_2[i].y = rand() % 450 + 100;
        //army_2[i].x = 270;
        //army_2[i].y = 250;
        QLabel * new_unit = new QLabel(this);
        new_unit->setPixmap(actions[army_2[i].type][army_2[i].direction][army_2[i].state]);
        army_2[i].unit_animation = new_unit;
        num_anim[i + army_1.size()] = i + army_1.size();
        y_anim[i + army_1.size()] = army_2[i].y;
    }

    for (int i = soldiers_2; i < soldiers_2 + musketeers_2; ++i) {
        army_2[i] = unit_type[3];
        army_2[i].x = rand() % 20 + 542;
        army_2[i].y = rand() % 450 + 100;
        //army_2[i].x = 400;
        //army_2[i].y = 300;
        QLabel * new_unit = new QLabel(this);
        new_unit->setPixmap(actions[army_2[i].type][army_2[i].direction][army_2[i].state]);
        army_2[i].unit_animation = new_unit;
        num_anim[i + army_1.size()] = i + army_1.size();
        y_anim[i + army_1.size()] = army_2[i].y;
    }

    for (int i = 0; i < army_1.size() + army_2.size() - 1; ++i) {
        for (int j = i; j < army_1.size() + army_2.size(); ++j) {
            if (y_anim[i] > y_anim[j]) {
                std::swap(num_anim[i], num_anim[j]);
                std::swap(y_anim[i], y_anim[j]);
            }
        }
    }

    for (int i = 0; i < army_1.size() + army_2.size(); ++i) {
        if (num_anim[i] < army_1.size()) {
            int index = num_anim[i];
            army_1[index].unit_animation->setGeometry(army_1[index].x - 26, army_1[index].y - 48, 54, 54);
            army_1[index].unit_animation->raise();
        } else {
            int index = num_anim[i] - army_1.size();
            army_2[index].unit_animation->setGeometry(army_2[index].x - 26, army_2[index].y - 48, 54, 54);
            army_2[index].unit_animation->raise();
        }
    }
}

void Widget::createConnections()
{
    connect(t_animations, SIGNAL(timeout()), this, SLOT(slotAnimations()));
}

void Widget::slotAnimations() {
    QVector<int> fase_go;
    fase_go<<0<<1<<0<<2;
    QVector<int> fase_fight;
    fase_fight<<3<<3<<4<<3;

    for (int i = 0; i < army_1.size() && army_2.size() > 0; ++i) {
        int min_distance = sqrt(pow(army_1[i].x - army_2[0].x, 2) / 9 + pow(army_1[i].y - army_2[0].y, 2));
        army_1[i].go_enemy = 0;
        for (int j = 1; j < army_2.size(); ++j) {
            int distance = sqrt(pow(army_1[i].x - army_2[j].x, 2) / 9 + pow(army_1[i].y - army_2[j].y, 2));
            if (distance < min_distance) {
                min_distance = distance;
                army_1[i].go_enemy = j;
            }
        }

        for (int j = 0; j < army_1.size(); ++j) {
            if (i != j) {
                double distance1 = sqrt(pow(army_1[i].x - army_1[j].x, 2) / 9 + pow(army_1[i].y - army_1[j].y, 2));
                double x1 = army_1[i].x, y1 = army_1[i].y;
                double x2 = army_1[j].x, y2 = army_1[j].y;
                double cos1 = ((x2 - x1) / 3)/sqrt(pow(x1 - x2, 2) / 9 + pow(y1 - y2, 2));
                double sin1 = (y2 - y1)/sqrt(pow(x1 - x2, 2) / 9 + pow(y1 - y2, 2));
                if (distance1 < 4) {
                    army_1[i].x -= cos1 * (16 - distance1) / 2.0;
                    army_1[i].y -= sin1 * (16 - distance1) / 2.0;
                    army_1[j].x += cos1 * (16 - distance1) / 2.0;
                    army_1[j].y += sin1 * (16 - distance1) / 2.0;
                    army_1[i].unit_animation->setGeometry(army_1[i].x - 26, army_1[i].y - 48, 54, 54);
                    army_1[j].unit_animation->setGeometry(army_1[j].x - 26, army_1[j].y - 48, 54, 54);
                }
            }
        }

        double x = army_1[i].x, y = army_1[i].y;
        double gox = army_2[army_1[i].go_enemy].x, goy = army_2[army_1[i].go_enemy].y;
        double cos = ((gox - x) / 3)/sqrt(pow(x - gox, 2) / 9 + pow(y - goy, 2));
        double sin = (goy - y)/sqrt(pow(x - gox, 2) / 9 + pow(y - goy, 2));

        if (goy - y < 0) {
            if (cos > 0.92) {
                army_1[i].direction = 0;
            } else if (cos <= 0.92 && cos > 0.38) {
                army_1[i].direction = 7;
            } else if (cos <= 0.38 && cos > -0.38) {
                army_1[i].direction = 6;
            } else if (cos <= -0.38 && cos > - 0.92) {
                army_1[i].direction = 5;
            } else if (cos <= -0.92) {
                army_1[i].direction = 4;
            }
        } else {
            if (cos > 0.92) {
                army_1[i].direction = 0;
            } else if (cos <= 0.92 && cos > 0.38) {
                army_1[i].direction = 1;
            } else if (cos <= 0.38 && cos > -0.38) {
                army_1[i].direction = 2;
            } else if (cos <= -0.38 && cos > - 0.92) {
                army_1[i].direction = 3;
            } else if (cos <= -0.92) {
                army_1[i].direction = 4;
            }
        }

        if (min_distance > army_1[i].attack_distance) {
            if (army_1[i].state == 0) {
                army_1[i].x += cos * army_1[i].speed;
                army_1[i].y += sin * army_1[i].speed;
                army_1[i].unit_animation->setPixmap(actions[army_1[i].type][army_1[i].direction][fase_go[army_1[i].fase]]);
                army_1[i].unit_animation->setGeometry(army_1[i].x - 26, army_1[i].y - 48, 54, 54);
                army_1[i].unit_animation->raise();
                army_1[i].fase += 1;
                army_1[i].fase = army_1[i].fase % 4;
            } else {
                army_1[i].state = 0;
                army_1[i].fase = 0;
            }
        } else {
            if (army_1[i].state == 0) {
                army_1[i].state = 1;
                army_1[i].fase = 0;
            } else {
                army_1[i].unit_animation->setPixmap(actions[army_1[i].type][army_1[i].direction][fase_fight[army_1[i].fase]]);
                army_1[i].unit_animation->raise();
                army_1[i].fase += 1;
                army_1[i].fase = army_1[i].fase % 4;
                if (army_1[i].fase == 2) {
                    army_2[army_1[i].go_enemy].hp -= army_1[i].attack;
                    if (army_2[army_1[i].go_enemy].hp <= 0) {
                        delete army_2[army_1[i].go_enemy].unit_animation;
                        army_2.erase(army_2.begin() + army_1[i].go_enemy);
                        if (army_2.size() == 0) {
                            t_animations->stop();
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < army_2.size() && army_1.size() > 0; ++i) {
        int min_distance = sqrt(pow(army_2[i].x - army_1[0].x, 2) / 9 + pow(army_2[i].y - army_1[0].y, 2));
        army_2[i].go_enemy = 0;
        for (int j = 1; j < army_1.size(); ++j) {
            int distance = sqrt(pow(army_2[i].x - army_1[j].x, 2) / 9 + pow(army_2[i].y - army_1[j].y, 2));
            if (distance < min_distance) {
                min_distance = distance;
                army_2[i].go_enemy = j;
            }
        }

        for (int j = 0; j < army_2.size(); ++j) {
            if (i != j) {
                double distance1 = sqrt(pow(army_2[i].x - army_2[j].x, 2) / 9 + pow(army_2[i].y - army_2[j].y, 2));
                double x1 = army_2[i].x, y1 = army_2[i].y;
                double x2 = army_2[j].x, y2 = army_2[j].y;
                double cos1 = ((x2 - x1) / 3)/sqrt(pow(x1 - x2, 2) / 9 + pow(y1 - y2, 2));
                double sin1 = (y2 - y1)/sqrt(pow(x1 - x2, 2) / 9 + pow(y1 - y2, 2));
                if (distance1 < 4) {
                    army_2[i].x -= cos1 * (16 - distance1) / 2.0;
                    army_2[i].y -= sin1 * (16 - distance1) / 2.0;
                    army_2[j].x += cos1 * (16 - distance1) / 2.0;
                    army_2[j].y += sin1 * (16 - distance1) / 2.0;
                    army_2[i].unit_animation->setGeometry(army_2[i].x - 26, army_2[i].y - 48, 54, 54);
                    army_2[j].unit_animation->setGeometry(army_2[j].x - 26, army_2[j].y - 48, 54, 54);
                }
            }
        }

        double x = army_2[i].x, y = army_2[i].y;
        double gox = army_1[army_2[i].go_enemy].x, goy = army_1[army_2[i].go_enemy].y;
        double cos = ((gox - x) / 3)/sqrt(pow(x - gox, 2) / 9 + pow(y - goy, 2));
        double sin = (goy - y)/sqrt(pow(x - gox, 2) / 9 + pow(y - goy, 2));

        if (goy - y < 0) {
            if (cos > 0.92) {
                army_2[i].direction = 0;
            } else if (cos <= 0.92 && cos > 0.38) {
                army_2[i].direction = 7;
            } else if (cos <= 0.38 && cos > -0.38) {
                army_2[i].direction = 6;
            } else if (cos <= -0.38 && cos > - 0.92) {
                army_2[i].direction = 5;
            } else if (cos <= -0.92) {
                army_2[i].direction = 4;
            }
        } else {
            if (cos > 0.92) {
                army_2[i].direction = 0;
            } else if (cos <= 0.92 && cos > 0.38) {
                army_2[i].direction = 1;
            } else if (cos <= 0.38 && cos > -0.38) {
                army_2[i].direction = 2;
            } else if (cos <= -0.38 && cos > - 0.92) {
                army_2[i].direction = 3;
            } else if (cos <= -0.92) {
                army_2[i].direction = 4;
            }
        }

        if (min_distance > army_2[i].attack_distance) {
            if (army_2[i].state == 0) {
                army_2[i].x += cos * army_2[i].speed;
                army_2[i].y += sin * army_2[i].speed;
                army_2[i].unit_animation->setPixmap(actions[army_2[i].type][army_2[i].direction][fase_go[army_2[i].fase]]);
                army_2[i].unit_animation->setGeometry(army_2[i].x - 26, army_2[i].y - 48, 54, 54);
                army_2[i].unit_animation->raise();
                army_2[i].fase +=1;
                army_2[i].fase = army_2[i].fase % 4;
            } else {
                army_2[i].state = 0;
                army_2[i].fase = 0;
            }
        } else {
            if (army_2[i].state == 0) {
                army_2[i].state = 1;
                army_2[i].fase = 0;
            } else {
                army_2[i].unit_animation->setPixmap(actions[army_2[i].type][army_2[i].direction][fase_fight[army_2[i].fase]]);
                army_2[i].unit_animation->raise();
                army_2[i].fase += 1;
                army_2[i].fase = army_2[i].fase % 4;
                if (army_2[i].fase == 2) {
                    army_1[army_2[i].go_enemy].hp -= army_2[i].attack;
                    if (army_1[army_2[i].go_enemy].hp <= 0) {
                        delete army_1[army_2[i].go_enemy].unit_animation;
                        army_1.erase(army_1.begin() + army_2[i].go_enemy);
                        if (army_1.size() == 0) {
                            t_animations->stop();
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < army_1.size() + army_2.size(); ++i) {
        num_anim[i] = i;
        if (i < army_1.size()) {
            y_anim[i] = army_1[i].y;
        } else {
            y_anim[i] = army_2[i - army_1.size()].y;
        }
    }

    for (int i = 0; i < army_1.size() + army_2.size() - 1; ++i) {
        for (int j = i; j < army_1.size() + army_2.size(); ++j) {
            if (y_anim[i] > y_anim[j]) {
                std::swap(num_anim[i], num_anim[j]);
                std::swap(y_anim[i], y_anim[j]);
            }
        }
    }

    for (int i = 0; i < army_1.size() + army_2.size(); ++i) {
        if (num_anim[i] < army_1.size()) {
            int index = num_anim[i];
            army_1[index].unit_animation->raise();
        } else {
            int index = num_anim[i] - army_1.size();
            army_2[index].unit_animation->raise();
        }
    }
}

Widget::~Widget()
{

}
