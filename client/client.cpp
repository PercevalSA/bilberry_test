#include "client.h"

GPSClient::GPSClient(const QString logFileName, QObject *parent) : QObject(parent)
{
    qDebug() << "Initialize worker thread";

    loggerThread = new QThread();
    worker = new Logger(logFileName);
    worker->moveToThread(loggerThread);

    connect(this->loggerThread, &QThread::finished, this->worker, &QObject::deleteLater);
    connect(this, &GPSClient::logFrame, this->worker, &Logger::writeData);

    qRegisterMetaType<QList<QString>>("QList<QString>"); // to send QList into signal

    loggerThread->start();

    QHostAddress ipAddress = QHostAddress::LocalHost;
    qDebug().noquote() << "Trying to connect to " << ipAddress.toString() << ":" << SERVER_PORT;
    connectToServer(&ipAddress, SERVER_PORT);
}

GPSClient::~GPSClient()
{
    loggerThread->quit();
    loggerThread->wait();
    delete loggerThread;
}

void GPSClient::connectToServer(const QHostAddress *host, const quint16 port)
{
    const int Timeout = 5 * 1000;

    socket.connectToHost(*host, port);

    if (!socket.waitForConnected(Timeout)) {
        qDebug() << socket.errorString();
        return;
    }

    connect(&socket, SIGNAL(readyRead()), this, SLOT(readData()));

    qDebug() << "Connected to server";
    while (socket.state() == QAbstractSocket::ConnectedState)
    {
        socket.waitForDisconnected(-1);
    }
    qCritical() << "Server deconnexion. Restart the program to reconnect";
}

void GPSClient::readData()
{
    QByteArray data = socket.readAll();
    QString dataString(data);
    QList<QString> dataGPS = dataString.split(",");

    // extracts only data we want : [ timestamp, fixQuality, altitude, altitudeUnit ]
    const QList<QString> *gpsData = new QList<QString>(
    {
        dataGPS[1],  // timestamp
        dataGPS[6],  // fixQuality
        dataGPS[9],  // altitude
        dataGPS[10], // altitudeUnit
    });

    emit logFrame(*gpsData);
}
