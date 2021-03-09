#ifndef GPSCLIENT_H
#define GPSCLIENT_H

#include <QtNetwork>
#include <QThread>
#include <QDebug>

#include "logger.h"

#define SERVER_PORT 4242

class GPSClient : public QObject
{
    Q_OBJECT

public:
    GPSClient(const QString logFileName, QObject *parent = nullptr);
    ~GPSClient();

private slots:
    void readData();

signals:
    void logFrame(QList<QString> data);

private:
    void connectToServer(const QHostAddress *host, const quint16 port);

    QThread *loggerThread;
    Logger *worker;

    QTcpSocket socket;
};

#endif
