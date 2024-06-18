#include "networkmanager.h"
#include <QNetworkDatagram>
#include <QDebug>
#include <QDataStream>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      connected(false),
      udpSocket(new QUdpSocket(this)),
      broadcastTimer(new QTimer(this))
{
    bool success = udpSocket->bind(QHostAddress::Any, 12345, QUdpSocket::ShareAddress);
    if (!success) {
        qCritical() << "Failed to bind UDP socket to port 12345.";
    } else {
        qDebug() << "UDP socket successfully bound to port 12345.";
    }

    connect(udpSocket, &QUdpSocket::readyRead, this, &NetworkManager::processPendingDatagrams);
    connect(broadcastTimer, &QTimer::timeout, this, &NetworkManager::broadcastGameAvailability);
}

NetworkManager::~NetworkManager()
{
}

QStringList NetworkManager::getAvailableGames()
{
    return availableGames;
}

QStringList NetworkManager::getLocalIPAddresses()
{
    QStringList ipAddresses;
    const QList<QHostAddress> &allAddresses = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : allAddresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol || address.protocol() == QAbstractSocket::IPv6Protocol) {
            ipAddresses << address.toString();
        }
    }
    return ipAddresses;
}


void NetworkManager::sendHandshakeRequest(const QString &hostAddress)
{
    QByteArray data = "2HANDSHAKE_REQUEST";
    qDebug() << "Sending handshake request to" << hostAddress << ":" << data;
    udpSocket->writeDatagram(data, QHostAddress(hostAddress), 12345);


}



void NetworkManager::sendHandshakeResponse(const QString &clientAddress, bool accepted, const QString &codeword, const QString &mapseed)
{
    QByteArray data = accepted ? "1HANDSHAKE_ACCEPTED " + codeword.toUtf8() + " " + mapseed.toUtf8() : "1HANDSHAKE_REJECTED";
    qDebug() << "Sending handshake response to" << clientAddress << ":" << data;
    udpSocket->writeDatagram(data, QHostAddress(clientAddress), 12345);

    if (accepted) {
        connected = true;
        recipientAddress = clientAddress;
        broadcastTimer->stop();
        qDebug() << "Handshake accepted. Connection established with" << clientAddress;
    }
}

void NetworkManager::startBroadcasting()
{
    if (!broadcastTimer->isActive()) {
        qDebug() << "Starting broadcast timer.";
        broadcastTimer->start(3000); // Broadcast every 3 seconds
    }
}

void NetworkManager::stopBroadcasting()
{
    if (broadcastTimer->isActive()) {
        qDebug() << "Stopping broadcast timer.";
        broadcastTimer->stop();
    }
}


void NetworkManager::broadcastGameAvailability()
{

        QByteArray data = "GAME_AVAILABLE";
        udpSocket->writeDatagram(data, QHostAddress::Broadcast, 12345);
        qDebug() << "Broadcasting game availability:" << data;

}


void NetworkManager::sendMapSeedToPlayer2(const QString &mapseed)
{
    QByteArray data =  mapseed.toUtf8();
    udpSocket->writeDatagram(data, QHostAddress(recipientAddress), 12345);
    qDebug() << "Sending map seed data to Player 2:" << mapseed;
}

//QString projectileSendData;
//void NetworkManager::sendProjectileData(QString &projectileData) //////////////////////////////////////////////////////////NETWORK STUFF 1
//{
//    QByteArray data =  projectileData.toUtf8();
//    udpSocket->writeDatagram(data, QHostAddress(recipientAddress), 12345);
//    qDebug() << "Sending map seed data to Player 2:" << projectileSendData;
//}

void NetworkManager::sendProjectileData(QString &projectileData) {
    QByteArray data = projectileData.toUtf8();
    udpSocket->writeDatagram(data, QHostAddress(recipientAddress), 12345);
    qDebug() << "Sending projectile data to Player 2:" << projectileData;
}

void NetworkManager::sendzandersuperfunctionDatatootherplayer(const QString &data)
{
    QByteArray data2 = data.toUtf8();
    udpSocket->writeDatagram(data2, QHostAddress(recipientAddress), 12345);
}


void NetworkManager::processPendingDatagrams()
{
    // Get local IP addresses once
    static QStringList localIPAddresses = getLocalIPAddresses();

    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString message = QString::fromUtf8(datagram.data());
        QString senderAddress = datagram.senderAddress().toString();
         QByteArray receivedData = datagram.data();

        qDebug() << "Received datagram from" << senderAddress << ":" << message;

        // Handle IPv6-mapped IPv4 addresses
        QHostAddress address(senderAddress);
        if (address.protocol() == QAbstractSocket::IPv6Protocol) {
            // Convert IPv6-mapped IPv4 address to IPv4 address
            address = QHostAddress(address.toIPv4Address());
        }
        QString correctedAddress = address.toString();

        // Skip processing if the datagram is from one of the local IP addresses
        if (localIPAddresses.contains(correctedAddress)) {
            qDebug() << "Skipping datagram from local address" << correctedAddress;
            continue;
        }

        if (!connected) {
            if (message == "GAME_AVAILABLE") {
                qDebug() << "Handling GAME_AVAILABLE message";
                if (!availableGames.contains(correctedAddress)) {
                    availableGames.append(correctedAddress);
                    emit availableGamesChanged();
                }
            } else if (message == "2HANDSHAKE_REQUEST") {
                qDebug() << "Handling 2HANDSHAKE_REQUEST message";
                emit handshakeRequestReceived(senderAddress);
            } else if (message.startsWith("1HANDSHAKE_ACCEPTED")) {
                qDebug() << "Handling 1HANDSHAKE_ACCEPTED message";
                QStringList parts = message.split(' ');
                if (parts.size() >= 3) {
                    QString codeworddata = parts[1];
                    QString mapseeddata = parts[2];
                    qDebug() << "Handshake accepted with codeword:" << codeworddata << "and mapseed:" << mapseeddata;
                    broadcastTimer->stop();
                    emit handshakeAccepted(codeworddata, mapseeddata);
                    connected = true;
                    recipientAddress = senderAddress;
                    qDebug() << "Broadcast timer stopped";
                }
            } else if (message == "1HANDSHAKE_REJECTED") {
                qDebug() << "Handling 1HANDSHAKE_REJECTED message";
                emit handshakeRejected();
            }} else {

                if (message.contains("zandersuperfunctionDataRecieved")){
                    emit zandersuperfunctionDataRecieved(message);
                }
                qDebug() << "Unexpected message from" << senderAddress << ":" << message;
                emit connectionError("Unexpected message from " + senderAddress);
            }
        }
    }

