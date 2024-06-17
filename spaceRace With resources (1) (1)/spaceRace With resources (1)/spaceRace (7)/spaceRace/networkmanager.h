#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QTimer>
#include <QStringList>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    bool connected;
    QStringList getAvailableGames();
    void sendHandshakeRequest(const QString &hostAddress);
    void sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword, const QString &mapseed);
    void broadcastGameAvailability();
    void disconnect();
    void sendMapSeedToPlayer2(const QString &mapseed);

signals:
    void handshakeRequestReceived(const QString &senderAddress);
    void handshakeAccepted(const QString &codeword, const QString &mapseed);
    void handshakeRejected();
    void connectionError(const QString &message);
    void availableGamesChanged();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QTimer *broadcastTimer;
    QStringList availableGames;
    QString recipientAddress;
    QStringList getLocalIPAddresses();

public slots:
    void startBroadcasting();
    void stopBroadcasting();

};

#endif // NETWORKMANAGER_H
