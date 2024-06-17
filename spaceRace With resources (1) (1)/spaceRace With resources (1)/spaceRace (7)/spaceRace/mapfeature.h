#ifndef MAPFEATURE_H
#define MAPFEATURE_H

#include <QGraphicsItem>

class mapFeature : public QGraphicsItem
{
public:
    mapFeature(const QRectF &bounds, bool host);
    QRectF boundingRect() const; // Override boundingRect() method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Override paint() method
    void runCourse();
    QString mapLog;

private:
    QList<QRectF> rectangles;
    QRectF sceneBounds;

};

#endif // MAPFEATURE_H
