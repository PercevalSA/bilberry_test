#include "server.h"

#define SERVER_PORT 4242

Server::Server(const QString *dataFileName, QObject *parent) : QObject(parent)
{
    initServer();
    readDataFile(dataFileName);

    connect(gpsServer, &QTcpServer::newConnection, this, &Server::sendGPS);
}

Server::~Server()
{
    gpsServer->close();
    delete gpsServer;
}

void Server::initServer()
{
    QString error;
    gpsServer = new QTcpServer(this);
    QHostAddress ipAddress = QHostAddress::LocalHost;

    if (!gpsServer->listen(ipAddress, SERVER_PORT)) {
        error = "GPS Server : Unable to start the server: %1";
        qCritical() << error.arg(gpsServer->errorString());
        return;
    }

    error = "The server is running on %1:%2";
    qInfo().noquote() << error
        .arg(gpsServer->serverAddress().toString())
        .arg(gpsServer->serverPort());
}

void Server::sendGPS()
{
    qDebug() << "A client has connected";

    QTcpSocket *clientConnection = gpsServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    // send a gps frame every second
    QList<QString>::iterator frame;
    for (frame = gpsFrames.begin(); frame != gpsFrames.end(); ++frame) // iterate through file data
    {
        if(clientConnection->state() != QAbstractSocket::ConnectedState)
            break;

        clientConnection->write(frame->toUtf8());
        clientConnection->waitForBytesWritten();

        QThread::sleep(1);
    }

    qDebug() << "Client disconnected or end of GPS Frames";
    clientConnection->disconnectFromHost();
    delete clientConnection;
}

void Server::readDataFile(const QString *fileName)
{
    QFile file(*fileName);

    if(!file.exists())
    {
        qCritical() << "Specified file does not exist";
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open specified file: " << file.errorString();
        return;
    }
    QTextStream inputData(&file);

    // rework needed ?
    while (!inputData.atEnd())
    {
        QString line = inputData.readLine();
        gpsFrames.append(line);
    }
    file.close();
}
