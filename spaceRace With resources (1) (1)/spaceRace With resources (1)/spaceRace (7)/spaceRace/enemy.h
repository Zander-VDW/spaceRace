#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsObject>
#include <QTimer>
#include "shipAugment.h"
#include "projectile.h"

class enemy : public QObject, public QGraphicsItem {

public:
    enemy();
    ~enemy() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updatePosition(QPointF playerPos);
    void advance(int step) override;
    void activateAugment();
    void deactivateAugment();
    void shootBlaster();
    void cooldownTimerEvent();
    void updateShootingDirection(qreal angle);
    bool isTouchingPath();



private:
    QPointF target;
    shipAugment augment;
    QTimer burnTimer;
    QTimer cooldownTimer;
    QTimer shootingTimer; // Timer for shooting
    qreal speed;
    QPointF lastPosition;
     qreal movementDirection;
     qreal angle;
};

#endif // ENEMY_H
