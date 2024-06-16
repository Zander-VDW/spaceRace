#include "networkmanager.h"
#include <QNetworkDatagram>
#include <QTimer>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      udpSocket(new QUdpSocket(this))
{
    udpSocket->bind(QHostAddress::Any, 12345, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &NetworkManager::processPendingDatagrams);

    // Periodically broadcast game availability
    QTimer *broadcastTimer = new QTimer(this);
    connect(broadcastTimer, &QTimer::timeout, this, &NetworkManager::broadcastGameAvailability);
    broadcastTimer->start(3000); // Broadcast every 3 seconds
}

NetworkManager::~NetworkManager()
{
}

QStringList NetworkManager::getAvailableGames()
{
    return availableGames;
}

void NetworkManager::sendHandshakeRequest(const QString &hostAddress)
{
    QByteArray data = "HANDSHAKE_REQUEST";
    qDebug() << data;
    udpSocket->writeDatagram(data, QHostAddress(hostAddress), 12345);
}

void NetworkManager::sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword)
{
    QByteArray data = accepted ? "HANDSHAKE_ACCEPTED " + codeword.toUtf8() : "HANDSHAKE_REJECTED";
    qDebug() << data;
    udpSocket->writeDatagram(data, QHostAddress(clientAddress), 12345);
}

void NetworkManager::broadcastGameAvailability()
{
    QByteArray data = "GAME_AVAILABLE";
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, 12345);
}

void NetworkManager::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString message = QString::fromUtf8(datagram.data());

        if (message == "HANDSHAKE_REQUEST") {
            emit handshakeRequestReceived(datagram.senderAddress().toString());
        } else if (message.startsWith("HANDSHAKE_ACCEPTED")) {
            QString codeword = message.split(' ').last();
            emit handshakeAccepted(codeword);
            qDebug() << codeword;
        } else if (message == "HANDSHAKE_REJECTED") {
            emit handshakeRejected();
        } else if (message == "GAME_AVAILABLE") {
            QString hostAddress = datagram.senderAddress().toString();
            if (!availableGames.contains(hostAddress)) {
                availableGames.append(hostAddress);
            }
        }
    }
}
