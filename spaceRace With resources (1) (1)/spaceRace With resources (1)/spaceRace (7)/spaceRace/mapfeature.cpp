#include "mapfeature.h"
#include <QPainter>
#include <cstdlib>
#include <ctime>
#include <enemy.h>
#include <QString>
#include <iostream>

mapFeature::mapFeature(const QRectF &bounds, QString seed)
    : sceneBounds(bounds)
{
    srand(static_cast<unsigned>(time(0)));
    runCourse();
    mapLog = seed;
    this->runCourse();
}

void mapFeature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::NoPen); // Remove the border around the rectangles
    painter->setBrush(Qt::cyan);
    setZValue(0);
    painter->save();

    QImage tileImage(":/spaceRaceREII313/mapElements/rainbowImages.jpg");
    QBrush brush(tileImage);
    painter->setBrush(brush);

    for (const QRectF &rect : rectangles) {
        painter->drawRect(rect);
    }

    painter->restore();
}

QRectF mapFeature::boundingRect() const {
    return sceneBounds;
}

void mapFeature::runCourse()
{
    QPointF penPoint = QPointF(-150, -150);
    int length = 300;
    QSize size = QSize(300, 300);
    char direction = 'd';
    int random;
    QRectF bounds = boundingRect();

    if(mapLog.contains("HOST")){
        std::cout << "HOSTING PA" << std::endl;
    penPoint = QPointF(-150, -150);

    rectangles.clear(); // Clear previous rectangles if any

    for (int i = 0; i < length; ++i)
    {
        random = rand() % 14 + 1;

        if(random <= 10)
        {
            // No direction change
        }
        else if(random == 11)
        {
            direction = 'w';
        }
        else if (random == 12)
        {
            direction = 'a';
        }
        else if (random == 13)
        {
            direction = 's';
        }
        else if (random == 14)
        {
            direction = 'd';
        }

        QPointF newPoint = penPoint;

        if(direction == 'w')
        {
            newPoint.setY(penPoint.y() - size.height());
        }
        else if (direction == 'a')
        {
            newPoint.setX(penPoint.x() - size.width());
        }
        else if (direction == 's')
        {
            newPoint.setY(penPoint.y() + size.height());
        }
        else if (direction == 'd')
        {
            newPoint.setX(penPoint.x() + size.width());
        }

        // Check if new point is within bounds
        if(bounds.contains(newPoint)) {
            penPoint = newPoint;
            rectangles.append(QRectF(penPoint, size));
            mapLog+=direction;
          //  std::cout << mapLog << std::endl;
        }
        else {
            // Optionally change direction or handle edge case
            // For now, just skip this move
            continue;
        }
    }
    } else {
        std::cout << "USING SEED" << std::endl;
                for (QChar dir : mapLog) {
                    QPointF newPoint = penPoint;

                    if (dir == 'w') {
                        newPoint.setY(penPoint.y() - size.height());
                    }
                    else if (dir == 'a') {
                        newPoint.setX(penPoint.x() - size.width());
                    }
                    else if (dir == 's') {
                        newPoint.setY(penPoint.y() + size.height());
                    }
                    else if (dir == 'd') {
                        newPoint.setX(penPoint.x() + size.width());
                    }

                    // Check if new point is within bounds
                    if (bounds.contains(newPoint)) {
                        penPoint = newPoint;
                        rectangles.append(QRectF(penPoint, size));
                    } else {
                        // Optionally handle out-of-bounds case
                        continue;
                    }
    }

}}
