// shipAugment.h
#ifndef SHIPAUGMENT_H
#define SHIPAUGMENT_H

#include <QString>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsItem>

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QTimer>

#include <progressbar.h>

class shipAugment : public QGraphicsItem // Inherit from QGraphicsItem
{
public:
    shipAugment();
    virtual ~shipAugment();

    void setType(QString value);
    QString getType();
    bool getActive();
    QRectF boundingRect() const override; // Declare boundingRect
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // Declare paint

    void Activate();
    void deActivate();

    void setSlot(int slotNum);

    void setDraggable(bool state);

    void toggleActivatable(bool isActivatable);

    int coolDown;

    bool activatable;

    int burnTime;

    int speedBoost;

    double damage;
    double fireRate;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString type;
    QString blasterType;
    int MkWhat;

    double damageReduction;

    bool active;

    bool isDragging;
    QPointF dragStartPos;

    int assignedSlot;
    bool isDraggable =true;

    QImage blasterActive;
        QImage blasterIdle;
        QImage thrusterActive;
        QImage thrusterIdle;



};

#endif // SHIPAUGMENT_H
