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
#include <QFontDatabase>
#include <QScreen>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //int fontId = QFontDatabase::addApplicationFont(":/menus/ROGFont.ttf");
    //QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);


    //QFont rogFont(fontFamily);
    //app.setFont(rogFont);
    QFont font = app.font();
    font.setPointSize(25); // Set the font size
    app.setFont(font);

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
