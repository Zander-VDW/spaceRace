#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class projectile : public QObject, public QGraphicsItem
{
public:
    projectile(QPointF startPos, qreal angle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int step) override;
    QPointF pos;
    qreal angle;

private:

    qreal speed;
    QTimer collisionTimer;
    bool canCollide;
    void enableCollisions();
};

#endif // PROJECTILE_H
