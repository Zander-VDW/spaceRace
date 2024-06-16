#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QScreen>  // Include QScreen header for screen resolution
#include "playerShip.h"
#include "shipAugment.h"
#include "mainwindow.h"
#include <mapfeature.h>
#include <enemy.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), view(new QGraphicsView(this)), player1Ship(new playerShip()), enemy1(new enemy())
{
    // MainMenu();

    initializeApplication();
}

MainWindow::~MainWindow()
{
    // Qt automatically handles deletion of child objects.
}

void MainWindow::MainMenu(){


}



void MainWindow::initializeApplication()
{

    QImage asteroidTiles = QImage("C:/Users/Dell10th-Gen/Downloads/temporarySlang/mapElements/customAsteroidBack.png");

    if (asteroidTiles.isNull()) {
        std::cout << "Failed to load background image file";
    }

    QBrush backgroundBrush(Qt::black);//asteroidTiles
    scene.setBackgroundBrush(backgroundBrush);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    scene.setSceneRect(-5000, -5000, 10000, 10000);

    // Add a few elements to the scene (for testing purposes)
    scene.addRect(500, 500, 200, 200, QPen(Qt::blue), QBrush(Qt::blue));
    scene.addEllipse(800, 800, 100, 100, QPen(Qt::red), QBrush(Qt::red));
    scene.addRect(0, 100, 50, 100, QPen(Qt::green), QBrush(Qt::green));
    scene.addRect(-300, -300, 500, 500, QPen(QColor(0, 0, 128)), QBrush(QColor(0, 0, 128)));

    // Create an instance of the playerShip class
    player1Ship->setFlag(QGraphicsItem::ItemClipsToShape, false);
    player1Ship->setFlag(QGraphicsItem::ItemClipsChildrenToShape, false);
    scene.addItem(player1Ship);

    mapFeature *feature1 = new mapFeature(scene.sceneRect());
    scene.addItem(feature1);

    enemyTargetPos = player1Ship->getPosition();

    enemy1->setPos(100, 100);
    scene.addItem(enemy1);

    // Create and add shipAugment instances
    shipAugment *augment1 = new shipAugment();
    augment1->setPos(-200, 0);
    augment1->setType("Shield");
    scene.addItem(augment1);

    shipAugment *augment2 = new shipAugment();
    augment2->setPos(-200, -100);
    augment2->setType("Blaster");
    scene.addItem(augment2);

    shipAugment *augment3 = new shipAugment();
    augment3->setPos(-200, 100);
    augment3->setType("Thruster");
    scene.addItem(augment3);

    shipAugment *augment4 = new shipAugment();
    augment4->setPos(-200, 110);
    augment4->setType("Thruster");
    scene.addItem(augment4);

    shipAugment *augment5 = new shipAugment();
    augment5->setPos(-200, 110);
    augment5->setType("Blaster");
    scene.addItem(augment5);

    // Set focus to the playerShip item
    player1Ship->setFlag(QGraphicsItem::ItemIsFocusable);
    player1Ship->setPos(0,0);
    player1Ship->setFocus();

    // Create a QGraphicsView and set the scene
    view->setScene(&scene);
    view->setWindowTitle("Space Battle Adventure Bonanza"); // Set window title

    // Set the initial view size
    const int viewWidth = screenWidth;
    const int viewHeight = screenHeight;
    view->resize(viewWidth, viewHeight); // Set window size
    view->centerOn(player1Ship->getPosition());

    timer.setInterval(1); // Update every millisecond

    connect(&timer, &QTimer::timeout, this, [this]() {
        scene.advance(); // Call advance to drive animation and collision detection
        enemy1->updatePosition(enemyTargetPos);
        enemyTargetPos = player1Ship->getPosition();
        view->centerOn(player1Ship->getPosition());
        scene.update();
        //std::cout << "playerShip Position: " << player1Ship->pos().x() << ", " << player1Ship->pos().y() << std::endl;
    });
    timer.start();

    view->show();
}
