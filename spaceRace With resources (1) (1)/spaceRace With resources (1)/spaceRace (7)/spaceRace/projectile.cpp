#include "projectile.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cmath>
#include <QtCore/qmath.h>
#include <playerShip.h>
#include <QTimer>
#include <QObject>

projectile::projectile(QPointF startPos, qreal angle)
    : pos(startPos), angle(angle), speed(10) {
    setPos(pos), setZValue(0); // Ensure this aligns the projectile's position properly

    // Initialize timer with a 1 second delay (1000 milliseconds)
    collisionTimer.setSingleShot(true);
    collisionTimer.setInterval(500); // 1000 milliseconds = 1 second

    // Connect timer to slot to enable collisions after timeout
    connect(&collisionTimer, &QTimer::timeout, this, &projectile::enableCollisions);
    collisionTimer.start(); // Start the timer
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

    if (canCollide) {
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


    // Check for collisions with the player ship only if collisions are enabled

        QList<QGraphicsItem *> colliding_items = collidingItems; // Use the previously obtained list of colliding items
        for (QGraphicsItem *item : colliding_items) {
            playerShip *player = dynamic_cast<playerShip *>(item);
            if (player) {
                // Check for collision based on shape of player ship
                QPainterPath playerPath;

                playerPath.addEllipse(player->getPosition(), 100, 100); // Assuming player ship is circular; adjust as per actual shape
                if (playerPath.contains(pos)) {
                    player->takeDamage(10); // Adjust the damage value as needed
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
            }
        }
    }

}

void projectile::enableCollisions() {
    canCollide = true;
}
