#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtWidgets>
#include"unit.h"

class Widget : public QWidget, public unit
{
    Q_OBJECT
    QLabel *floor, *instructions;
    QVector<unit> units, army_1, army_2;
    QVector<int> index, target_x, target_y;
    QVector<double> arrow_x, arrow_y;
    QVector<QLabel *> animations, hp;
    QVector<QLabel *> arrows;
    QVector<QVector<QPixmap> > actions;
    QVector<QPixmap> arrow_states, hp_states;
    QPixmap f;
    QTimer *t_animations;
    QVector<int> paints;
    int type = 0;
public:
    Widget(QWidget *parent = 0);
    void loadPixmaps();
    void createFloor();
    void createUnits();
    void createArmies();
    void createConnections();
    ~Widget();
public slots:
    void slotAnimations();
};

#endif // WIDGET_H
