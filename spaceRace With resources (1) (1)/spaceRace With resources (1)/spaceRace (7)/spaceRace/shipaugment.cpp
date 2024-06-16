// shipAugment.cpp
#include "shipAugment.h"
#include <iostream>

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>


shipAugment::shipAugment()
    : active(false) {
    setFlags(ItemIsMovable | ItemIsSelectable);
    setType(type);
    this->isDraggable = true;
    setZValue(1); // Default zValue, you can change this as needed
    coolDown=0;
    this->activatable=true;
    this->speedBoost=1;
    this->burnTime=5000;
    this->active=false;
}


shipAugment::~shipAugment()
{
    // Clean up resources if necessary
}

void shipAugment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging == false) {
        isDragging = true;
        dragStartPos = event->pos();
    } else {
        isDragging = false;
    }
}

void shipAugment::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (isDragging==true) {
        QPointF newPos = pos() + (event->pos() - dragStartPos);
        setPos(newPos);
    }
}

void shipAugment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging==true) {
        isDragging = false;
    }
}




void shipAugment::setType(QString value)
{
    this->type = value;
    this->MkWhat = 1;

    if (this->type == "Blaster")
    {

            coolDown=1;
            this->burnTime=10000;


    }

    else if (this->type == "Lazer")
    {

    }
    else if (this->type == "Shield")
    {
        coolDown=5000;
        this->burnTime=5000;
    }
    else if (this->type == "Thruster")
    {
        this->coolDown=1000;
        this->speedBoost = 5;
        this->burnTime=2000;
    }

    else if (this->type == "Warp Drive")
    {

    }
}

QString shipAugment::getType()
{
    return this->type;
}

bool shipAugment::getActive()
{
    return this->active;
}

QRectF shipAugment::boundingRect() const
{
    // Return a suitable bounding rectangle for the item
    return QRectF(-50, -50, 100, 100); // Adjust these values as needed
}

void shipAugment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 2));

    int x=-50;
    int y=-50;
    switch (this->assignedSlot) {
    case 1:
        x = -75;
        y = -90;
        break;
    case 2:
        x = -75;
        y = 30;
        break;
    case 3:
        x = 15;
        y = -90;
        break;
    case 4:
        x = 15;
        y = 30;
        break;

    }

    QRectF slotRect(x, y, 60, 60);


    // Load the image
    /*QImage blasterActive = QImage("C:/Users/Dell10th-Gen/Desktop/spaceRaceREII313/blaster_active.jpg");
    QImage blasterIdle = QImage("C:/Users/Dell10th-Gen/Desktop/spaceRaceREII313/blaster_idle.jpg");

    QImage thrusterActive = QImage("C:/Users/Dell10th-Gen/Desktop/spaceRaceREII313/thruster_Active.jpg");
    QImage thrusterIdle = QImage("C:/Users/Dell10th-Gen/Desktop/spaceRaceREII313/thruster_Idle.jpg");*/

    QImage blasterActive = QImage(":/Augments/blaster_active.jpg");
        QImage blasterIdle = QImage(":/Augments/blaster_idle.jpg");

        QImage thrusterActive = QImage(":/Augments/thruster_Active.jpg");
        QImage thrusterIdle = QImage(":/Augments/thruster_Idle.jpg");



    if (blasterActive.isNull() || blasterIdle.isNull() || thrusterIdle.isNull() || thrusterActive.isNull()) {
        std::cout << "Failed to load image file";
    }

    // Calculate the center of the slot
    QPointF center = slotRect.center();

    // Adjust the image position so it is centered within the slot
    QPointF topLeftBlaster(center.x() - blasterIdle.width() / 2, center.y() - blasterIdle.height() / 2);
    QPointF topLeftThruster(center.x() - thrusterIdle.width(), center.y() - thrusterIdle.height()/2);

    if (type == "Shield") {
        painter->setBrush(Qt::cyan);
        painter->drawRect(slotRect);
    } else if (type == "Blaster" && this->active==true) {

        // Draw the image at the adjusted position
        painter->drawImage(topLeftBlaster, blasterActive);

    }else if (type == "Blaster" && this->active==false) {
        painter->drawImage(topLeftBlaster, blasterIdle);

    } else if (type == "Thruster" && this->active==true) {
        painter->drawImage(topLeftThruster, thrusterActive);

    } else if (type == "Thruster" && this->active==false) {
        painter->drawImage(topLeftThruster, thrusterIdle);
    }
}

void shipAugment::Activate()
{
    if(this->activatable==true){
       // std::cout << "Slot " << this->assignedSlot << " ACTIVATED" << std::endl;
        this->active=true;
        //this->activatable=false;

    }
}

void shipAugment::deActivate()
{
    this->active=false;

}

void shipAugment::setSlot(int slotNum)
{
    this->assignedSlot=slotNum;
}

void shipAugment::setDraggable(bool state)
{
    this->isDraggable=state;
}

bool lastActivatable;
void shipAugment::toggleActivatable(bool isActivatable)
{
    if(lastActivatable==isActivatable){
       // std::cout << "Slot " << this->assignedSlot << " RELOADED : " << isActivatable << std::endl;
    }
    this->activatable=isActivatable;
}

