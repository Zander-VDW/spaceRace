#include "projectile.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cmath>
#include <QtCore/qmath.h>

projectile::projectile(QPointF startPos, qreal angle)
    : pos(startPos), angle(angle), speed(5) {
    setPos(pos), setZValue(0); // Ensure this aligns the projectile's position properly
}

QRectF projectile::boundingRect() const {
    return QRectF(-10, -10, 20, 20); // Centered bounding box around (0,0)
}

void projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::red);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
}

void projectile::advance(int step) {
    if (!step) return;
    // Move the projectile in the direction of the angle
    pos += QPointF(speed * qCos(angle * M_PI / 180), speed * qSin(angle * M_PI / 180));
    setPos(pos);

    // Check if the projectile is out of bounds and remove it
    if (!scene()->sceneRect().contains(pos)) {
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Check for collisions with enemies
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        enemy *e = dynamic_cast<enemy *>(item);
        if (e) {
            e->takeDamage(10); // Adjust the damage value as needed
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
