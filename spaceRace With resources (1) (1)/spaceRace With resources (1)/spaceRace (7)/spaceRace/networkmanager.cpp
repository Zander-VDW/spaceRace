#include "networkmanager.h"
#include <QNetworkDatagram>
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      connected(true),
      udpSocket(new QUdpSocket(this)),
      broadcastTimer(new QTimer(this)),
      recipientAddress("")
{
    bool success = udpSocket->bind(QHostAddress::Any, 12345, QUdpSocket::ShareAddress);
    if (!success) {
        qCritical() << "Failed to bind UDP socket to port 12345.";
    } else {
        qDebug() << "UDP socket successfully bound to port 12345.";
    }

    connect(udpSocket, &QUdpSocket::readyRead, this, &NetworkManager::processPendingDatagrams);
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
    QByteArray data = "2HANDSHAKE_REQUEST";
    qDebug() << "Sending handshake request to" << hostAddress << ":" << data;
    udpSocket->writeDatagram(data, QHostAddress(hostAddress), 12345);
}

void NetworkManager::hostGame()
{
    connected = false;
    qDebug() << "Game hosted. Network disconnected.";
}

void NetworkManager::sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword)
{
    QByteArray data = accepted ? "1HANDSHAKE_ACCEPTED " + codeword.toUtf8() : "1HANDSHAKE_REJECTED";
    qDebug() << "Sending handshake response to" << clientAddress << ":" << data;
    udpSocket->writeDatagram(data, QHostAddress(clientAddress), 12345);

    if (accepted) {
        connected = true;
        recipientAddress = clientAddress;
        broadcastTimer->stop();
        qDebug() << "Handshake accepted. Connection established with" << clientAddress;
    }
}

void NetworkManager::broadcastGameAvailability()
{
    if (!connected) {
        QByteArray data = "GAME_AVAILABLE";
        udpSocket->writeDatagram(data, QHostAddress::Broadcast, 12345);
        qDebug() << "Broadcasting game availability:" << data;
    }
}

void NetworkManager::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString message = QString::fromUtf8(datagram.data());
        QString senderAddress = datagram.senderAddress().toString();
        qDebug() << "Received datagram from" << senderAddress << ":" << message;

        if (!connected || senderAddress == recipientAddress) {
            if (message == "2HANDSHAKE_REQUEST") {
                emit handshakeRequestReceived(senderAddress);
            } else if (message.startsWith("1HANDSHAKE_ACCEPTED")) {
                QString codeword = message.split(' ').last();
                emit handshakeAccepted(codeword);
                connected = true;
                recipientAddress = senderAddress;
                broadcastTimer->stop();
            } else if (message == "1HANDSHAKE_REJECTED") {
                emit handshakeRejected();
            } else if (message == "GAME_AVAILABLE") {
                if (!availableGames.contains(senderAddress)) {
                    availableGames.append(senderAddress);
                }
            } else {
                // Process other messages intended for this recipient
                // Add your specific message handling logic here
            }
        } else {
            emit connectionError("Unexpected message from " + senderAddress);
        }
    }
}

void NetworkManager::disconnect()
{
    if (connected) {
        connected = false;
        recipientAddress = "";
        broadcastTimer->start(3000); // Resume broadcasting
        emit disconnected("Disconnected from the current session.");
        qDebug() << "Disconnected from the current session.";
    }
}
