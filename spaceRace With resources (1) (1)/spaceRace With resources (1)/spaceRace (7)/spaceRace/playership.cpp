// playerShip.cpp

#include "playerShip.h"
#include <QPainter>
#include <cmath> // Include cmath header for M_PI constant
#include <QtCore/qmath.h> // Include qmath.h for Qt mathematical functions
#include <iostream> // Include iostream for std::cout
#include <QtCore/QObject>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "playerShip.h"
#include "shipAugment.h"
#include "projectile.h"
#include <progressbar.h>

int imageAngle;
playerShip::playerShip() : angle(0), pos(0, 0), defaultSpeed(3), currentHealth(1000), maxHealth(1000), isAlive(true) {
    // Initialize ship properties here if needed
    //this->highlightedSlot = 1;

    connect(&moveTimer, &QTimer::timeout, this, &playerShip::moveFunc);
    moveTimer.start(20);

    connect(&shootingTimer, &QTimer::timeout, this, &playerShip::shootBlaster);
    shootingTimer.start(100); //adjusted for firerate

    connect(&slot1BurnTimer, &QTimer::timeout, this, &playerShip::slotOneBurnFunction);
    connect(&slot2BurnTimer, &QTimer::timeout, this, &playerShip::slotTwoBurnFunction);
    connect(&slot3BurnTimer, &QTimer::timeout, this, &playerShip::slotThreeBurnFunction);
    connect(&slot4BurnTimer, &QTimer::timeout, this, &playerShip::slotFourBurnFunction);

    connect(&slot1DelayTimer, &QTimer::timeout, this, &playerShip::slotOneCooldown);
    connect(&slot2DelayTimer, &QTimer::timeout, this, &playerShip::slotTwoCooldown);
    connect(&slot3DelayTimer, &QTimer::timeout, this, &playerShip::slotThreeCooldown);
    connect(&slot4DelayTimer, &QTimer::timeout, this, &playerShip::slotFourCooldown);

    healthBar = new ProgressBar(this);
    healthBar->setColor(Qt::green);
    healthBar->setMaxValue(1000);
    healthBar->setValue(currentHealth);
    healthBar->setPos(-50,50);


    coolDownBar1 = new ProgressBar(this);
    coolDownBar1->setColor(Qt::red);
    coolDownBar1->setMaxValue(3000);
    coolDownBar1->setValue(3000);
    coolDownBar1->setPos(-50,50);

    coolDownBar2 = new ProgressBar(this);
    coolDownBar2->setColor(Qt::red);
    coolDownBar2->setMaxValue(3000);
    coolDownBar2->setValue(3000);
    coolDownBar2->setPos(-50,50);

    coolDownBar3 = new ProgressBar(this);
    coolDownBar3->setColor(Qt::red);
    coolDownBar3->setMaxValue(3000);
    coolDownBar3->setValue(3000);
    coolDownBar3->setPos(-50,50);

    coolDownBar4 = new ProgressBar(this);
    coolDownBar4->setColor(Qt::red);
    coolDownBar4->setMaxValue(3000);
    coolDownBar4->setValue(3000);
    coolDownBar4->setPos(-50,50);

    playerShipImage.load("C:/Users/Dell10th-Gen/Downloads/temporarySlang/ships/playerShip.png");
}

QRectF playerShip::boundingRect() const {
    return QRectF(QPointF(-5000, -5000), QSizeF(10000, 10000));
}


int oldAngle;
void playerShip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    painter->translate(pos);
    painter->rotate(angle);

    painter->setBrush(Qt::red);

    /*for(int i=1; i<5;i++)
    {
        painter->drawRect(slotRect(i));
    }*/

    painter->setBrush(Qt::NoBrush);

    // Draw ship body
    painter->drawRect(QRectF(-30, -30, 60, 60)); // Main body of the ship

    // Draw slots
    QRectF rect1(-75, -90, 60, 60);
        QRectF rect2(-75, 30, 60, 60);
        QRectF rect3(15, -90, 60, 60);
        QRectF rect4(15, 30, 60, 60);

        painter->drawRect(rect1);
        painter->drawRect(rect2);
        painter->drawRect(rect3);
        painter->drawRect(rect4);

        QFont font;
        font.setBold(true);
        font.setPointSize(10);
        painter->setFont(font);
        painter->setPen(Qt::black); // Set the color for the text

        // Draw text inside each rectangle, centered
        painter->drawText(rect1, Qt::TopRightCorner, "1");
        painter->drawText(rect2, Qt::TopRightCorner, "2");
        painter->drawText(rect3, Qt::TopLeftCorner, "3");
        painter->drawText(rect4, Qt::TopRightCorner, "4");
    /*case 1:
            return  // Adjusted for new orientation
        case 2:
            return ; // Adjusted for new orientation
        case 3:
            return ; // Adjusted for new orientation
        case 4:
            return  // Adjusted for new orientation
        default:
            return QRectF();


*/

    // Draw augments in slots
    slotOne.setPos(slotRect(1).center());
    slotTwo.setPos(slotRect(2).center());
    slotThree.setPos(slotRect(3).center());
    slotFour.setPos(slotRect(4).center());

    slotOne.paint(painter, option, widget);
    slotTwo.paint(painter, option, widget);
    slotThree.paint(painter, option, widget);
    slotFour.paint(painter, option, widget);


    // Draw shield if active
    if (slotOne.getType() == "Shield" && slotOne.getActive()) {
        painter->setPen(QPen(Qt::green, 4));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(QRectF(-120, -120, 240, 240));
    }else

        if (slotTwo.getType() == "Shield" && slotTwo.getActive()) {
            painter->setPen(QPen(Qt::yellow, 4));
            painter->setBrush(Qt::NoBrush);
            painter->drawEllipse(QRectF(-120, -120, 240, 240));
        } else
            if (slotThree.getType() == "Shield" && slotThree.getActive()) {
                painter->setPen(QPen(Qt::blue, 4));
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(QRectF(-120, -120, 240, 240));
            } else
                if (slotFour.getType() == "Shield" && slotFour.getActive()) {
                    painter->setPen(QPen(QColor(255,165,0), 4));
                    painter->setBrush(Qt::NoBrush);
                    painter->drawEllipse(QRectF(-120, -120, 240, 240));
                }


    painter->rotate(imageAngle);
    painter->drawImage(-123, -127, playerShipImage); //(-123, -127)
    painter->setBrush(Qt::red);
    //painter->drawEllipse(-12-5, -12-5,10,10); //exactly at pixelcheckpoint (when using screen dimensions)
   // painter->drawEllipse(-5, -5,10,10); //exactly at midpoint

    painter->restore();
    setZValue(2);
}

void playerShip::shootBlaster() {
    if (slotOne.getType() == "Blaster" && slotOne.getActive()) {
        projectile *proj = new projectile(slotRect(1).center(), angle); //can fix the bullet centering here I guess
        scene()->addItem(proj);
    }
    if (slotTwo.getType() == "Blaster" && slotTwo.getActive()) {
        projectile *proj = new projectile(slotRect(2).center(), angle);
        scene()->addItem(proj);
    }
    if (slotThree.getType() == "Blaster" && slotThree.getActive()) {
        projectile *proj = new projectile(slotRect(3).center(), angle);
        scene()->addItem(proj);
    }
    if (slotFour.getType() == "Blaster" && slotFour.getActive()) {
        projectile *proj = new projectile(slotRect(4).center(), angle);
        scene()->addItem(proj);
    }

    //std::cout << "Painting playerShip at position: (" << pos.x() << ", " << pos.y() << ")" << std::endl;
}





void playerShip::keyPressEvent(QKeyEvent *event) {
    if(isAlive){

    // Handle key presses
    switch (event->key()) {
    case Qt::Key_W:
        //pos.setY(pos.y() - speed);
        imageAngle = 0; // Up
        lastDirection='w';
        break;
    case Qt::Key_A:
       // pos.setX(pos.x() - speed);
        imageAngle = 0; // Left
        lastDirection='a';
        break;
    case Qt::Key_S:
        //pos.setY(pos.y() + speed);
        imageAngle = 0; // Down
        lastDirection='s';
        break;
    case Qt::Key_D:
       // pos.setX(pos.x() + speed);
        imageAngle = 0; // Right
        lastDirection='d';
        break;

    case Qt::Key_1:
                if (event->modifiers() & Qt::KeypadModifier) {
                    if (!slotOne.getActive() && slotOne.activatable) {
                        slotOne.Activate();
                        slotOne.toggleActivatable(false);
                        slot1BurnTimer.start(slotOne.burnTime);
                    } else {
                        slotOne.deActivate();
                    }

                    if (slotOne.getType() == "Shield") {
                        //slot1BurnTimer.start(slotOne.burnTime);
                    } else if (slotOne.getType() == "Blaster") {
                        if (!slotOne.isActive()) {
                            shootBlaster();
                        }
                    } else if (slotOne.getType() == "Thruster") {
                        slotOne.Activate();
                        slotOne.toggleActivatable(false);
                        slot1BurnTimer.start(slotOne.burnTime);
                    }
                }
                break;

            case Qt::Key_2:
                if (event->modifiers() & Qt::KeypadModifier) {
                    if (!slotTwo.getActive() && slotTwo.activatable) {
                        slotTwo.Activate();
                        slotTwo.toggleActivatable(false);
                        slot2BurnTimer.start(slotTwo.burnTime);
                    } else {
                        slotTwo.deActivate();
                    }

                    if (slotTwo.getType() == "Shield") {
                        //slot2BurnTimer.start(slotTwo.burnTime);
                    } else if (slotTwo.getType() == "Blaster") {
                        if (!slotTwo.isActive()) {
                            shootBlaster();
                        }
                    } else if (slotTwo.getType() == "Thruster") {
                        slotTwo.Activate();
                        slotTwo.toggleActivatable(false);
                        slot2BurnTimer.start(slotTwo.burnTime);
                    }
                }
                break;

            case Qt::Key_3:
                if (event->modifiers() & Qt::KeypadModifier) {
                    if (!slotThree.getActive() && slotThree.activatable) {
                        slotThree.Activate();
                        slotThree.toggleActivatable(false);
                        slot3BurnTimer.start(slotThree.burnTime);
                    } else {
                        slotThree.deActivate();
                    }

                    if (slotThree.getType() == "Shield") {
                        //slot3BurnTimer.start(slotThree.burnTime);
                    } else if (slotThree.getType() == "Blaster") {
                        if (!slotThree.isActive()) {
                            shootBlaster();
                        }
                    } else if (slotThree.getType() == "Thruster") {
                        slotThree.Activate();
                        slotThree.toggleActivatable(false);
                        slot3BurnTimer.start(slotThree.burnTime);
                    }
                }
                break;

            case Qt::Key_4:
                if (event->modifiers() & Qt::KeypadModifier) {
                    if (!slotFour.getActive() && slotFour.activatable) {
                        slotFour.Activate();
                        slotFour.toggleActivatable(false);
                        slot4BurnTimer.start(slotFour.burnTime);
                    } else {
                        slotFour.deActivate();
                    }

                    if (slotFour.getType() == "Shield") {
                        //slot4BurnTimer.start(slotFour.burnTime);
                    } else if (slotFour.getType() == "Blaster") {
                        if (!slotFour.isActive()) {
                            shootBlaster();
                        }
                    } else if (slotFour.getType() == "Thruster") {
                        slotFour.Activate();
                        slotFour.toggleActivatable(false);
                        slot4BurnTimer.start(slotFour.burnTime);
                    }
                }
                break;

            default:
                QGraphicsItem::keyPressEvent(event);
                break;
        }


    update();
}}



void playerShip::slotOneBurnFunction() {
    // Implementation of slot one burn functionality
    // Reset or stop the timer and deactivate the slot
    std::cout << "Slot 1" << " BURNED" << std::endl;
    slotOne.deActivate();
    slot1BurnTimer.stop();
    slot1DelayTimer.start(slotOne.coolDown); // Assuming a cooldown period of 5 seconds
}

void playerShip::slotTwoBurnFunction() {
    // Implementation of slot two burn functionality
    std::cout << "Slot 2" << " BURNED" << std::endl;
    slotTwo.deActivate();
    slot2BurnTimer.stop();
    slot2DelayTimer.start(slotTwo.coolDown);
}

void playerShip::slotThreeBurnFunction() {
    // Implementation of slot three burn functionality
    std::cout << "Slot 3" << " BURNED" << std::endl;
    slotThree.deActivate();
    slot3BurnTimer.stop();
    slot3DelayTimer.start(slotThree.coolDown);
}

void playerShip::slotFourBurnFunction() {
    // Implementation of slot four burn functionality
    std::cout << "Slot 4" << " BURNED" << std::endl;
    slotFour.deActivate();
    slot4BurnTimer.stop();
    slot4DelayTimer.start(slotFour.coolDown);
}

void playerShip::slotOneCooldown() {
    // Reactivate slot one after cooldown
    std::cout << "Slot 1" << " COOLED" << std::endl;
    slotOne.toggleActivatable(true);
    slot1DelayTimer.stop();
}

void playerShip::slotTwoCooldown() {
    // Reactivate slot two after cooldown
    std::cout << "Slot 2" << " COOLED" << std::endl;
    slotTwo.toggleActivatable(true);
    slot2DelayTimer.stop();
}

void playerShip::slotThreeCooldown() {
    // Reactivate slot three after cooldown
    std::cout << "Slot 3" << " COOLED" << std::endl;
    slotThree.toggleActivatable(true);
    slot3DelayTimer.stop();
}

void playerShip::slotFourCooldown() {
    // Reactivate slot four after cooldown
    std::cout << "Slot 4" << " COOLED" << std::endl;
    slotFour.toggleActivatable(true);
    slot4DelayTimer.stop();
}

//int oldAngle;
QRectF playerShip::slotRect(int slot) {
    QPointF slotPosition;
    qreal offset = 60; // Adjust as necessary for your layout

    // Define slot positions relative to the center of the ship
    switch (slot) {
    case 1:
        slotPosition = QPointF(-offset+15, -offset);
        break;
    case 2:
        slotPosition = QPointF(-offset+15, offset);
        break;
    case 3:
        slotPosition = QPointF(offset-15, -offset);
        break;
    case 4:
        slotPosition = QPointF(offset-15, offset);
        break;
    default:
        return QRectF();
    }

    // Create a transform for the ship's rotation and translation
    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.rotate(angle);

    // Apply the transform to the slot position
    QPointF transformedPosition = transform.map(slotPosition);

    // Define the slot rectangle based on the transformed position
    return QRectF(transformedPosition - QPointF(30, 30), QSizeF(60, 60));
}




void playerShip::checkForCollisions() {
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        shipAugment *augment = dynamic_cast<shipAugment *>(item);
        if (augment) {
            augment->setDraggable(false);

            // Check each slot's rectangle for collision
            for (int i = 1; i <= 4; ++i) {
                if (slotRect(i).contains(augment->pos())) {
                    std::cout << "Collision detected between augment and slot: " << augment->getType().toStdString() << " and slot " << i << std::endl;
                    switch (i) {
                    case 1:
                        slotOne.setSlot(1);
                        slotOne.setType(augment->getType());
                        break;
                    case 2:
                        slotTwo.setSlot(2);
                        slotTwo.setType(augment->getType());
                        break;
                    case 3:
                        slotThree.setSlot(3);
                        slotThree.setType(augment->getType());
                        break;
                    case 4:
                        slotFour.setSlot(4);
                        slotFour.setType(augment->getType());
                        break;
                    }

                    scene()->removeItem(augment);
                   // delete augment;
                    update(); // Update the ship's rendering
                }
            }
        }
    }
}



void playerShip::advance(int step) {
    if (!step) return;
    checkForCollisions();
}

int speed;
int saveNum = 0;
QPointF returnPoint;
void playerShip::moveFunc()
{
    speed = defaultSpeed;
    if (slotOne.getType() == "Thruster" && slotOne.getActive() == true) {
        // Action for slot one
        std::cout << "Thruster Active in Slot 1" << std::endl;
        speed = speed + slotOne.speedBoost;
    }

    if (slotTwo.getType() == "Thruster" && slotTwo.getActive() == true) {
        // Action for slot two
        std::cout << "Thruster Active in Slot 2" << std::endl;
        speed = speed + slotTwo.speedBoost;
    }

    if (slotThree.getType() == "Thruster" && slotThree.getActive() == true) {
        // Action for slot three
        std::cout << "Thruster Active in Slot 3" << std::endl;
        speed = speed + slotThree.speedBoost;
    }

    if (slotFour.getType() == "Thruster" && slotFour.getActive() == true) {
        // Action for slot four
        std::cout << "Thruster Active in Slot 4" << std::endl;
        speed = speed + slotFour.speedBoost;
    }

    //QPointF returnPoint = QPointF(0,0);

    if(isTouchingPath()==true)
    {
    switch (lastDirection) {
    case 'w':
        pos.setY(pos.y() - speed);
        angle = -90; // Up
        break;
    case 'a':
        pos.setX(pos.x() - speed);
        angle = 180; // Left
        break;
    case 's':
        pos.setY(pos.y() + speed);
        angle = 90; // Down
        break;
    case 'd':
        pos.setX(pos.x() + speed);
        angle = 0; // Right
        break;
    }

    saveNum++;
    if(saveNum==10)
    {
       returnPoint.setX(pos.x());
       returnPoint.setY(pos.y());
       saveNum=0;
    }
    } else {
    pos.setX(returnPoint.x());
    pos.setY(returnPoint.y());
    lastDirection=' ';
    }

   /* qreal sceneWidth = scene()->sceneRect().width();
        qreal sceneHeight = scene()->sceneRect().height();
        pos.setX(qBound(0.0, pos.x(), sceneWidth));
        pos.setY(qBound(0.0, pos.y(), sceneHeight));*/
    healthBar->setPos(this->getPosition().x()-50, this->getPosition().y()+100);

    coolDownBar1->setPos(this->getPosition().x()-100, this->getPosition().y()-110);
    coolDownBar2->setPos(this->getPosition().x()-100, this->getPosition().y()-125);
    coolDownBar3->setPos(this->getPosition().x()-100, this->getPosition().y()-140);
    coolDownBar4->setPos(this->getPosition().x()-100, this->getPosition().y()-155);

    coolDownBar1->setMaxValue(2500);
    coolDownBar2->setMaxValue(2500);
    coolDownBar3->setMaxValue(2500);
    coolDownBar4->setMaxValue(2500);


    coolDownBar1->setValue(slot1DelayTimer.remainingTime());
    coolDownBar2->setValue(slot2DelayTimer.remainingTime());
    coolDownBar3->setValue(slot3DelayTimer.remainingTime());
    coolDownBar4->setValue(slot4DelayTimer.remainingTime());

    update();
}

bool playerShip::isTouchingPath() {

  // Get the graphics view associated with the scene
  QGraphicsView *view = scene()->views().first();
   QPoint center(view->width()/2-12, view->height()/2-12);

  //QPoint center(view->width()/2-12-25, view->height()/2-12);

  // Capture an image of the visible area of the scene
  QImage image = view->grab().toImage();

  // Get the color of the pixel at the center of the bounding rectangle
  QColor pixelColor = image.pixelColor(center);

  // Check if the pixel color matches the path color (130, 135, 144)
  std::cout << "Is touching : " << pixelColor.red() << " " << pixelColor.green() << " " << pixelColor.blue() << std::endl;
  /*if(pixelColor==QColor(0, 0, 0))
  {
     std::cout << "POS: Y - > " << this->getPosition().y() << std::endl;
  }*/
  return pixelColor != QColor(0, 0, 0);
}

void playerShip::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
    healthBar->setValue(currentHealth);

    if (currentHealth == 0) {
        // Handle player death
        isAlive=false;
        std::cout << "Player has been destroyed!" << std::endl;
        // Add more code to handle player death, like stopping the game or resetting the level
    }
}




