#include "mainwindow.h"
#include "networkmanager.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QUrl>
#include <QPixmap>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      connectionEstablished(false)
{
    mediaPlayer = new QMediaPlayer(this);
    buttonClickSound = new QSoundEffect(this);

    stackedWidget = new QStackedWidget(this);
    mainMenuWidget = new QWidget(this);
    multiplayerMenuWidget = new QWidget(this);
    hostMenuWidget = new QWidget(this);
    joinMenuWidget = new QWidget(this);
    backgroundLabel = new QLabel(this);
    gameListWidget = new QListWidget(joinMenuWidget);
    GameoverWidget = new QWidget(this);
    networkManager = new NetworkManager(this);

    QPixmap backgroundPixmap(":/menus/mainmenuscreen.jpg");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setFixedSize(600, 600);
    backgroundLabel->lower();

    setCentralWidget(stackedWidget);

    setupMainMenu();
    setupMultiplayerMenu();
    setupHostMenu();
    setupJoinMenu();
    setupGameover(6000);

    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(multiplayerMenuWidget);
    stackedWidget->addWidget(hostMenuWidget);
    stackedWidget->addWidget(joinMenuWidget);
    stackedWidget->addWidget(GameoverWidget);

    showMainMenu();
    //showGameover();

    changeBackgroundMusic("qrc:/menus/background.mp3");
    buttonClickSound->setSource(QUrl(":/menus/buttonclick.mp3"));
    buttonClickSound->setVolume(1.00);

    // Connect network manager signals
    connect(networkManager, &NetworkManager::handshakeRequestReceived, this, &MainWindow::onHandshakeRequestReceived);
    connect(networkManager, &NetworkManager::handshakeAccepted, this, &MainWindow::onHandshakeAccepted);
    connect(networkManager, &NetworkManager::handshakeRejected, this, &MainWindow::onHandshakeRejected);
    connect(networkManager, &NetworkManager::connectionError, this, &MainWindow::onConnectionError);
    connect(networkManager, &NetworkManager::disconnected, this, &MainWindow::onDisconnected);
}

void MainWindow::setupGameover(int currentScore)
{
    // Clear any existing layout and widgets
    QLayout *existingLayout = GameoverWidget->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    // Load and display the picture at the top
    QLabel *pictureLabel = new QLabel(GameoverWidget);
    QPixmap picture(":/Augments/blaster_active.jpg"); // Adjust the path to your picture
    pictureLabel->setPixmap(picture);
    pictureLabel->setAlignment(Qt::AlignCenter);

    // Read scores from a text file
    QVector<ScoreEntry> scores = readScoresFromFile(":/menus/scores.txt");
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry &a, const ScoreEntry &b) {
        return a.score > b.score;
    });

    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout(GameoverWidget);
    layout->addWidget(pictureLabel);

    // Input for player name
    QLabel *nameLabel = new QLabel("Enter your name:", GameoverWidget);
    QLineEdit *nameInput = new QLineEdit(GameoverWidget);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);

    // Display the top 3 highest scores
    QLabel *top3ScoresLabel = new QLabel(GameoverWidget);
    updateTop3ScoresLabel(scores, top3ScoresLabel); // Helper function to update scores label
    layout->addWidget(top3ScoresLabel);

    // Add Play Again and Return to Main Menu buttons
    QPushButton *playAgainButton = new QPushButton("Play Again", GameoverWidget);
    QPushButton *returnToMainMenuButton = new QPushButton("Return to Main Menu", GameoverWidget);
    layout->addWidget(playAgainButton);
    layout->addWidget(returnToMainMenuButton);

    // Connect buttons to their respective slots
    connect(playAgainButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(playAgainButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
    connect(returnToMainMenuButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(returnToMainMenuButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);

    // Save score when the player enters their name
    connect(nameInput, &QLineEdit::editingFinished, this, [this, nameInput, currentScore, &scores, top3ScoresLabel]() mutable {
        QString playerName = nameInput->text();
        if (!playerName.isEmpty()) {
            ScoreEntry newScore = { playerName, currentScore, QDateTime::currentDateTime() };
            scores.append(newScore);
            std::sort(scores.begin(), scores.end(), [](const ScoreEntry &a, const ScoreEntry &b) {
                return a.score > b.score;
            });
            if (scores.size() > 10) {
                scores.resize(10);
            }
            saveScoresToFile(":/menus/scores.txt", scores);
            updateTop3ScoresLabel(scores, top3ScoresLabel); // Update displayed scores
        }
    });
}

void MainWindow::updateTop3ScoresLabel(const QVector<ScoreEntry> &scores, QLabel *top3ScoresLabel)
{
    QString top3Text = "Top 3 Scores:\n";
    for (int i = 0; i < std::min(3, scores.size()); ++i) {
        top3Text += QString::number(i + 1) + ": " + scores[i].name + " - " + QString::number(scores[i].score) + " (" + scores[i].dateTime.toString() + ")\n";
    }
    top3ScoresLabel->setText(top3Text);
    top3ScoresLabel->setAlignment(Qt::AlignCenter);
}

QVector<ScoreEntry> MainWindow::readScoresFromFile(const QString &filePath)
{
    QVector<ScoreEntry> scores;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3) {
                ScoreEntry entry = { parts[0], parts[1].toInt(), QDateTime::fromString(parts[2]) };
                scores.append(entry);
            }
        }
        file.close();
    } else {
        qWarning() << "Could not open file" << filePath;
    }
    return scores;
}

void MainWindow::saveScoresToFile(const QString &filePath, const QVector<ScoreEntry> &scores)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const ScoreEntry &entry : scores) {
            out << entry.name << "," << entry.score << "," << entry.dateTime.toString() << "\n";
        }
        file.close();
    } else {
        qWarning() << "Could not open file" << filePath;
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupHostMenu()
{
    QVBoxLayout *layout = new QVBoxLayout(hostMenuWidget);

    for (const QString &player : pendingPlayers) {
        QPushButton *acceptButton = new QPushButton("Accept " + player, hostMenuWidget);
        QPushButton *rejectButton = new QPushButton("Reject " + player, hostMenuWidget);

        layout->addWidget(acceptButton);
        layout->addWidget(rejectButton);

        connect(acceptButton, &QPushButton::clicked, [this, player]() { acceptPlayer(player); });
        connect(rejectButton, &QPushButton::clicked, [this, player]() { rejectPlayer(player); });
    }

    QPushButton *backButton = new QPushButton("Back", hostMenuWidget);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &MainWindow::showMultiplayerMenu);
}

void MainWindow::setupJoinMenu()
{
    QPushButton *backButton = new QPushButton("Back", joinMenuWidget);
    QPushButton *refreshButton = new QPushButton("Refresh", joinMenuWidget);

    QVBoxLayout *layout = new QVBoxLayout(joinMenuWidget);
    layout->addWidget(gameListWidget);
    layout->addWidget(refreshButton);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &MainWindow::showMultiplayerMenu);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateGameList);
}

void MainWindow::updateGameList()
{
    gameListWidget->clear();
    QStringList availableGames = networkManager->getAvailableGames();
    gameListWidget->addItems(availableGames);

    connect(gameListWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        onGameSelected(item->text());
    });
}

void MainWindow::onGameSelected(const QString &hostAddress)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Join Game", "Do you want to join the game hosted by " + hostAddress + "?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        networkManager->sendHandshakeRequest(hostAddress);
    }
}

void MainWindow::acceptPlayer(const QString &player)
{
    QString codeword = QDateTime::currentDateTime().toString(Qt::ISODate);
    networkManager->sendHandshakeResponse(player, true, codeword);
    this->codeword = codeword;
    connectionEstablished = true; // Set the flag to true
}

void MainWindow::rejectPlayer(const QString &player)
{
    networkManager->sendHandshakeResponse(player, false, QString());
}

void MainWindow::onHandshakeRequestReceived(const QString &clientAddress)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "New Player Request", "Do you want to accept the player from " + clientAddress + "?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString codeword = QDateTime::currentDateTime().toString(Qt::ISODate);
        networkManager->sendHandshakeResponse(clientAddress, true, codeword);
        this->codeword = codeword;
        connectionEstablished = true; // Set the flag to true
    } else {
        networkManager->sendHandshakeResponse(clientAddress, false, QString());
    }
}

void MainWindow::onHandshakeAccepted(const QString &codeword)
{
    this->codeword = codeword;
    connectionEstablished = true; // Set the flag to true
    QMessageBox::information(this, "Handshake", "Connection established. You are now connected.");
}

void MainWindow::onHandshakeRejected()
{
    QMessageBox::information(this, "Handshake", "Connection rejected by the host.");
}

void MainWindow::onConnectionError(const QString &message)
{
    connectionEstablished = false; // Set the flag to false
    QMessageBox::critical(this, "Connection Error", message);
}

void MainWindow::onDisconnected(const QString &message)
{
    connectionEstablished = false; // Set the flag to false
    QMessageBox::warning(this, "Disconnected", message);
}

void MainWindow::showMultiplayerMenu()
{
    stackedWidget->setCurrentWidget(multiplayerMenuWidget);
}

void MainWindow::showGameover()
{
    stackedWidget->setCurrentWidget(GameoverWidget);
}

void MainWindow::showMainMenu()
{
   stackedWidget->setCurrentWidget(mainMenuWidget);
}

void MainWindow::showHostMenu()
{
    stackedWidget->setCurrentWidget(hostMenuWidget);
}

void MainWindow::showJoinMenu()
{
    stackedWidget->setCurrentWidget(joinMenuWidget);
    updateGameList();
}

void MainWindow::setupMainMenu()
{
    QPushButton *singlePlayerButton = new QPushButton("Single", mainMenuWidget);
    QPushButton *multiplayerButton = new QPushButton("Multiplayer", mainMenuWidget);

    QVBoxLayout *layout = new QVBoxLayout(mainMenuWidget);
    layout->addWidget(singlePlayerButton);
    layout->addWidget(multiplayerButton);

    connect(singlePlayerButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(singlePlayerButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
    connect(multiplayerButton, &QPushButton::clicked, this, &MainWindow::showMultiplayerMenu);
    connect(multiplayerButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
}

void MainWindow::setupMultiplayerMenu()
{
    QPushButton *hostButton = new QPushButton("Host", multiplayerMenuWidget);
    QPushButton *joinButton = new QPushButton("Join", multiplayerMenuWidget);
    QPushButton *backButton = new QPushButton("Back", multiplayerMenuWidget);

    QVBoxLayout *layout = new QVBoxLayout(multiplayerMenuWidget);
    layout->addWidget(hostButton);
    layout->addWidget(joinButton);
    layout->addWidget(backButton);

    connect(hostButton, &QPushButton::clicked, this, &MainWindow::showHostMenu);
    connect(hostButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
    connect(joinButton, &QPushButton::clicked, this, &MainWindow::showJoinMenu);
    connect(joinButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::playButtonClickSound);
}

void MainWindow::startGame()
{
    removeBackgroundImage();
    stackedWidget->hide();
    QWidget *gameCentralWidget = new QWidget();
    setCentralWidget(gameCentralWidget);
    initializeGame();
}

void MainWindow::initializeGame()
{
    //initialiseApplication();
    showGameover();
}

void MainWindow::changeBackgroundMusic(const QString &filePath)
{
    mediaPlayer->setMedia(QUrl(filePath));
    mediaPlayer->setVolume(0);
    mediaPlayer->play();
}

void MainWindow::playButtonClickSound()
{
    buttonClickSound->play();
}

void MainWindow::removeBackgroundImage()
{
    backgroundLabel->clear();
}


void MainWindow::initializeApplication()
{

    QImage asteroidTiles = QImage("C:/Users/Dell10th-Gen/Downloads/temporarySlang/mapElements/customAsteroidBack.png");

    if (asteroidTiles.isNull()) {
        qDebug() << "Failed to load background image file";
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
