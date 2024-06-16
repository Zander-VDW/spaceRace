#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QStringList>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QStringList getAvailableGames();

public slots:
    void sendHandshakeRequest(const QString &hostAddress);
    void sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword);
    void broadcastGameAvailability();

signals:
    void handshakeRequestReceived(const QString &clientAddress);
    void handshakeAccepted(const QString &codeword);
    void handshakeRejected();
    void connectionError(const QString &message);
    void disconnected(const QString &message);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QStringList availableGames;
};

#endif // NETWORKMANAGER_H
