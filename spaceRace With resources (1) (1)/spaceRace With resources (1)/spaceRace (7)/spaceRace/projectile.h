#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QPainter>

class projectile : public QGraphicsItem {
public:
    projectile(QPointF startPos, qreal angle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int step) override;

private:
    QPointF pos;
    qreal angle;
    qreal speed;
};

#endif // PROJECTILE_H
