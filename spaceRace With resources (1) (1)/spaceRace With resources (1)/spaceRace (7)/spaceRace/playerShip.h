// playerShip.h

#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <shipAugment.h>
#include <QGraphicsItem>
#include <QKeyEvent> // Include QKeyEvent for handling key events
#include <QTimer>
#include <QtCore/QObject>
#include <progressbar.h>

class playerShip : public QObject, public QGraphicsItem
{
public:
    playerShip();

    QRectF boundingRect() const override; // Override boundingRect() method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // Override paint() method
    void updatePosition(); // Method to update ship's position
    void keyPressEvent(QKeyEvent *event) override;
    QPointF getPosition() const { return pos; }
    void updateSlot(QString value);
    void advance(int phase) override;
    void takeDamage(int damage);

private:
    void checkForCollisions();
    QRectF slotRect(int slot);

    qreal angle; // Ship's angle
    QPointF pos; // Ship's position
    qreal defaultSpeed; // Ship's default speed

    shipAugment slotOne;
    shipAugment slotTwo;
    shipAugment slotThree;
    shipAugment slotFour;

    QRectF slotRect1;
    QRectF slotRect2;
    QRectF slotRect3;
    QRectF slotRect4;



    //        int highlightedSlot;
    QTimer moveTimer;
    QTimer burnTimer;
    QTimer shootingTimer;

    QTimer slot1DelayTimer;
    QTimer slot2DelayTimer;
    QTimer slot3DelayTimer;
    QTimer slot4DelayTimer;

    QTimer slot1BurnTimer;
    QTimer slot2BurnTimer;
    QTimer slot3BurnTimer;
    QTimer slot4BurnTimer;

    QImage blasterActive;
    QImage blasterIdle;

    QImage thrusterActive;
    QImage thrusterIdle;

    char lastDirection;

    bool isTouchingPath();

    int currentHealth;
    int maxHealth;

    ProgressBar* healthBar;
    ProgressBar* coolDownBar1;
    ProgressBar* coolDownBar2;
    ProgressBar* coolDownBar3;
    ProgressBar* coolDownBar4;

    bool isAlive;



private slots:
    void moveFunc();

    void slotOneBurnFunction();
    void slotTwoBurnFunction();
    void slotThreeBurnFunction();
    void slotFourBurnFunction();

    void shootBlaster();
    void slotOneCooldown();
    void slotTwoCooldown();
    void slotThreeCooldown();
    void slotFourCooldown();
};

#endif // PLAYERSHIP_H
