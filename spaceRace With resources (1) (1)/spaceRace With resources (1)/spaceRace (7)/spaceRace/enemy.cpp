#include "enemy.h"
#include <QPainter>
#include <cmath>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
//ENEMY AI HANDLER
bool alive=true;
enemy::enemy()
    : speed(1), angle(0), health(1000)
{
    // Initialize timers
    connect(&shootingTimer, &QTimer::timeout, this, &enemy::shootBlaster);
    connect(&cooldownTimer, &QTimer::timeout, this, &enemy::cooldownTimerEvent);


    shootingTimer.start(500); // Adjust shooting interval as needed

    // Initialize progress bars
        healthBar = new ProgressBar(this);
        healthBar->setColor(Qt::green);
        healthBar->setMaxValue(1000);
        healthBar->setValue(health);
        healthBar->setPos(-50,50);

    // Initialize augment properties (assuming augment is initialized appropriately)
    augment.setType("Blaster"); // Example type
    augment.setActive(true);    // Example active state
}

enemy::~enemy()
{
    // Cleanup if necessary
}

QRectF enemy::boundingRect() const
{
    return QRectF(-40, -40, 80, 80); // Adjust the bounding rect as necessary
}

void enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->translate(QPointF(0, 0));
    painter->rotate(angle);

    painter->save();

    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(boundingRect()); // Draw a simple blue ellipse centered at (0, 0)
    painter->restore();

    setZValue(1);

    painter->setBrush(Qt::red);

    augment.paint(painter, option, widget);
    // painter->drawEllipse(50, 10, 10, 10);
}

int DirectionReg = 100;
bool lostTrack = false;
int trackLoop = 1;
QPointF direction = QPointF(1, 1);
QPointF forbiddenDirection;
bool xAllowed = true;
bool yAllowed = true;

void enemy::updatePosition(QPointF playerPos)
{
    if (alive==true){
    // Check if the enemy is currently touching the path
    bool onPath = isTouchingPath();

    // Calculate the direction vector from the enemy to the player

    // Normalize the direction vector


    trackLoop--;

    if (lostTrack == true) {
        trackLoop = 100;
        lostTrack = false;
    }


    if (trackLoop < 1) {
        if (!onPath) {
            lostTrack = true;
            moveBy(10*-direction.x(), 10*-direction.y());
            if (xAllowed) {
                direction.setY(0.0);
                direction.setX((direction.x() > 0 ? 1 : -1) * speed);
            } else {
                direction.setY((direction.y() > 0 ? 1 : -1) * speed);
                direction.setX(0.0);
            }
        } else {
            direction = playerPos - pos();
            qreal distance = std::hypot(direction.x(), direction.y());
            if (distance > 0.0) {
                direction /= distance;
            }


            qreal distanceToPlayer = std::hypot(playerPos.x() - pos().x(), playerPos.y() - pos().y());
            if (distanceToPlayer > 400)
            {

                // Constrain movement to cardinal directions
                if (std::abs(direction.x()) > std::abs(direction.y())) {
                    xAllowed = false;
                    yAllowed = true;
                    direction.setY(0.0);
                    direction.setX((direction.x() > 0 ? 1 : -1) * speed);
                } else {
                    yAllowed = false;
                    xAllowed = true;
                    direction.setX(0.0);
                    direction.setY((direction.y() > 0 ? 1 : -1) * speed);
                }

            }/* else
            {
                if (std::abs(direction.x()) < std::abs(direction.y())) {
                    xAllowed = false;
                    yAllowed = true;
                    direction.setY(0.0);
                    direction.setX((direction.x() > 0 ? 1 : -1) * speed);
                } else {
                    yAllowed = false;
                    xAllowed = true;
                    direction.setX(0.0);
                    direction.setY((direction.y() > 0 ? 1 : -1) * speed);
                }

                if (std::abs(direction.x()) == std::abs(direction.y())) {
                        xAllowed = false;
                        yAllowed = true;
                        direction.setY(0.0);
                        direction.setX((direction.x() > 0 ? 1 : -1));
                    } else {
                        yAllowed = false;
                        xAllowed = true;
                        direction.setX(0.0);
                        direction.setY((direction.y() > 0 ? 1 : -1));
                }
            }*/
        }}


    moveBy(direction.x(), direction.y());

    // Update angle for shooting, constrained to cardinal directions
    if (std::abs(direction.x()) > std::abs(direction.y())) {
        if (direction.x() > 0) {
            angle = 0; // Right
        } else {
            angle = 180; // Left
        }
    } else {
        if (direction.y() > 0) {
            angle = 90; // Down
        } else {
            angle = -90; // Up
        }
    }

    qreal distanceToPlayer = std::hypot(playerPos.x() - pos().x(), playerPos.y() - pos().y());

    if (distanceToPlayer < 400 && augment.getType() == "Blaster") {
        activateAugment(); // You may want to modify this based on your game logic
    } else {
        deactivateAugment();
    }

    // Trigger shooting based on a condition (e.g., augment is active)
    // shootBlaster();
}
}

void enemy::takeDamage(int damage) {

    health -= damage;
    healthBar->setValue(health);

    if (health <= 0) {
        die();
        healthBar->setValue(0);
    }
}

void enemy::die() {
    augment.setDraggable(true);
    alive=false;
}

void enemy::advance(int step)
{
    if (!step) return;
    update();
}

void enemy::shootBlaster()
{
    if (augment.getActive() && alive==true) {
        // Create projectile at current position with specified angle
        projectile *proj = new projectile(QPointF(pos().x()-50,pos().y()-50), angle);
        scene()->addItem(proj);
    }
}

void enemy::activateAugment() {
    if (augment.activatable) {
        augment.Activate();
        burnTimer.start(augment.burnTime);
        augment.toggleActivatable(false);
        cooldownTimer.start(augment.coolDown);
    }
}

void enemy::deactivateAugment() {
    augment.deActivate();
    burnTimer.start(augment.burnTime);
    // augment.toggleActivatable(true);
}

bool enemy::isTouchingPath() {
    QGraphicsView *view = scene()->views().first();

    // Get the position of the enemy in the scene
    QPointF scenePos = mapToScene(QPointF(0, 0));

    // Convert scene position to view position
    QPoint viewPos = view->mapFromScene(scenePos);

    // Ensure the view position is within the bounds of the view (optional)
    if (viewPos.x() < 0 || viewPos.y() < 0 ||
            viewPos.x() >= view->width() || viewPos.y() >= view->height()) {
        std::cout << "Out of view bounds" << std::endl;
        speed = 0;
        return false; // Out of view bounds, assume not touching path
    } else {
        speed = 1;
    }

    // Capture the screen and get the pixel color at the enemy's position
    QImage image = view->grab().toImage();

    // Ensure viewPos is valid within the image bounds
    if (viewPos.x() >= image.width() || viewPos.y() >= image.height()) {
        std::cout << "View position out of image bounds" << std::endl;
        return false;
    }

    QColor pixelColor = image.pixelColor(viewPos);

    // Adjust the path color condition based on your game's path color
    bool touching = (pixelColor != QColor(0, 0, 0)); // Check against path color

    //std::cout << "Pixel Color: " << pixelColor.red() << ", " << pixelColor.green() << ", " << pixelColor.blue() << std::endl;
    //std::cout << "Is touching path: " << touching << std::endl;

    return touching;
}

void enemy::cooldownTimerEvent()
{
    augment.activatable = true;
}
