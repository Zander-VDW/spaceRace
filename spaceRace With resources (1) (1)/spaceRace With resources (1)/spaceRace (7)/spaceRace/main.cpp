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

    int fontId = QFontDatabase::addApplicationFont("://spaceRaceREII313/menus/ROGFont.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont rogFont(fontFamily);
    app.setFont(rogFont);
    QFont font = app.font();

    MainWindow w;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    double percentage = 0.012;
    int pointSize = static_cast<int>(screenWidth * percentage);
    font.setPointSize(pointSize); // Set the font size
    app.setFont(font);


    w.setFixedSize(screenWidth, screenHeight);
    w.show();
    w.showFullScreen();

    return app.exec();
}
