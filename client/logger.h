#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(const QString logFileName, QObject *parent = nullptr);

private:
    QString fileName;

public slots:
    void writeData(const QList<QString> data);
};

#endif
