#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "playerShip.h" // Include the header file for playerShip
#include "shipAugment.h" // Include the header file for shipAugment
#include "mainwindow.h"
#include <mapfeature.h>
#include <enemy.h>
#include <iostream>
#include <QScreen>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    w.setFixedSize(screenWidth, screenHeight);
    w.show();
    w.showFullScreen();

    return app.exec();
}
