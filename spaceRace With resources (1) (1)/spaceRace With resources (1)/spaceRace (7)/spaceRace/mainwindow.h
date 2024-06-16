#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "playerShip.h"
#include "shipAugment.h"
#include "mapfeature.h"
#include "enemy.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initializeApplication();
    void MainMenu();

    QGraphicsScene scene;
    QGraphicsView *view;
    QTimer timer;

    playerShip *player1Ship;
    enemy *enemy1;
    QPointF enemyTargetPos;
};

#endif // MAINWINDOW_H
