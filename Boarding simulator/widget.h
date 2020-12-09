#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

using namespace std;

class unit {
public:
    int fraction;
    int type;
    int hp, max_hp;
    int attack;
    int state, fase;
    double x, y;
    int go_enemy;
    int direction;
    int speed;
    int attack_distance;
    QLabel *unit_animation;
};

class Widget : public QWidget
{
    Q_OBJECT
    QLabel *floor;
    //QVector<QLabel *> unit_animations;
    QVector<int> num_anim, y_anim;
    QVector<unit> unit_type, army_1, army_2;
    QTimer *t_animations;
    QVector<QVector<QVector<QPixmap> > > actions;
public:
    Widget(QWidget *parent = 0);
    void createUnits();
    void createArmies();
    void createConnections();
    ~Widget();
public slots:
    void slotAnimations();
};

#endif // WIDGET_H
