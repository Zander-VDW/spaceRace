#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QStringList>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QStringList getAvailableGames();
    void sendHandshakeRequest(const QString &hostAddress);
    void sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword);
    void broadcastGameAvailability();
    void disconnect();
    void hostGame();

signals:
    void handshakeRequestReceived(const QString &senderAddress);
    void handshakeAccepted(const QString &codeword);
    void handshakeRejected();
    void connectionError(const QString &message);
    void disconnected(const QString &message);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QTimer *broadcastTimer;
    QStringList availableGames;
    QString recipientAddress;
    bool connected;

};

#endif // NETWORKMANAGER_H
