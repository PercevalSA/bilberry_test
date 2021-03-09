#include "logger.h"

Logger::Logger(const QString logFileName, QObject *parent) : QObject(parent)
{
    fileName = logFileName;
}

void Logger::writeData(const QList<QString> data)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Cannot open specified file: " << file.error();
        return;
    }
    
    QTextStream stream(&file);
    
    for(auto my_iter = data.begin(); my_iter != data.end(); ++my_iter)
        stream << *my_iter << ",";

    // if Qt::endl is used instead (because endl is deprecated)
    // it does not compile on Debian Buster (Qt 5.11.3)
    stream << endl;
    file.close();
}
