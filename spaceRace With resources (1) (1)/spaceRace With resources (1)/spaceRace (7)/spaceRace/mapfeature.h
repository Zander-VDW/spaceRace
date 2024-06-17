#ifndef MAPFEATURE_H
#define MAPFEATURE_H

#include <QGraphicsItem>

class mapFeature : public QGraphicsItem
{
public:
    mapFeature(const QRectF &bounds, QString seed);
    QRectF boundingRect() const; // Override boundingRect() method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Override paint() method
    QString mapLog;



private:
    QList<QRectF> rectangles;
    QRectF sceneBounds;
    void runCourse();

};

#endif // MAPFEATURE_H
