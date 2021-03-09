#ifndef GPSSERVER_H
#define GPSSERVER_H

#include <QtNetwork>
#include <QFile>
#include <QList>
#include <QString>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(const QString *dataFileName, QObject *parent = nullptr);
    ~Server();

private slots:
    void sendGPS();

private:
    void initServer();
    void readDataFile(const QString *fileName);

    QTcpServer *gpsServer = nullptr;
    QList<QString> gpsFrames;

};

#endif
