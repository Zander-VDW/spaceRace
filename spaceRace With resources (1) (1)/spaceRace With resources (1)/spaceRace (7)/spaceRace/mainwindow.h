#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#include <QGraphicsPixmapItem>
#include "playerShip.h"
#include "shipAugment.h"
#include "mapfeature.h"
#include "enemy.h"
#include <QDebug>
#include <QHBoxLayout>

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <QMediaPlayer>
#include <QLabel>
#include <QSoundEffect>

#include "networkmanager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QDateTime>

#include <QLineEdit>
#include <QShowEvent>

struct ScoreEntry {
    QString name;
    int score;
    QDateTime date;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupGameover(int currentScore, const QString &defaultName);
    int buttonWidth;
    int player;
    QString mapSeed;
    QString hostMapGenerator();
    void receiveProjectileData();




private slots:
    void showMainMenu();
    void showMultiplayerMenu();
    void showHostMenu();
    void showJoinMenu();

    void startGame();
    void startMultiplayerGame();

    void changeBackgroundMusic(const QString &filePath);
    void playButtonClickSound();
    void removeBackgroundImage();
    //void acceptPlayer(const QString &player);
    //void rejectPlayer(const QString &player);

    void onHandshakeRequestReceived(const QString &clientAddress);
        void onHandshakeAccepted(const QString &codeword, const QString &mapseed);
        void onHandshakeRejected();
        void onConnectionError(const QString &message);
    void handleAvailableGamesChanged();


private:
        void saveScore();
    void showGameover();
    void setupMainMenu();
    void setupMultiplayerMenu();
    void setupHostMenu();
    void setupJoinMenu();
    void initializeGame();
    void initializeApplication();
    void initializeMultiplayerApplication();

    QString getLocalHostAddress();
    void processJoinRequest();
    void joinRequest(const QString &hostAddress);
    void setupGameover(int currentScore);
    void processScoreEntry(QLineEdit *nameInput, int currentScore, QVector<ScoreEntry> &scores, QLabel *top3ScoresLabel);
    QVector<ScoreEntry> readScoresFromFile(const QString &filePath);
    void saveScoresToFile(const QString &filePath, const QVector<ScoreEntry> &scores);
    void updateTop3ScoresLabel(const QVector<ScoreEntry> &scores, QLabel *top3ScoresLabel);

    QStackedWidget *stackedWidget;
    QWidget *mainMenuWidget;
    QWidget *multiplayerMenuWidget;
    QWidget *hostMenuWidget;
    QWidget *joinMenuWidget;
    QWidget *GameoverWidget;
    QMediaPlayer *mediaPlayer;
    QLabel *backgroundLabel;
    QSoundEffect *buttonClickSound;


    NetworkManager *networkManager;
    QListWidget *gameListWidget;
    QStringList pendingPlayers;
    QString codeword;
    void onGameSelected(const QString &hostAddress);
    void updateGameList();
    bool connectionEstablished;


    //game functionality

        QGraphicsScene scene;
        QGraphicsView *view;
        QTimer timer;

        playerShip *player1Ship;
        enemy *enemy1;
        QPointF enemyTargetPos;
//    void player2mapseed(const QString &codeword, const QString &mapseed);

//protected:
//    void showEvent(QShowEvent *event) override;
//    void hideEvent(QHideEvent *event) override;


};

#endif // MAINWINDOW_H
