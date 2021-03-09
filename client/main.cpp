#include <QCoreApplication>
#include <QCommandLineParser>

#include "client.h"

int main(int argc, char *argv[ ])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("gps-client");

    // get filename from command line
    QCommandLineParser parser;
    parser.setApplicationDescription("GPS Client");
    parser.addHelpOption();
    parser.addPositionalArgument("log_file",
        QCoreApplication::translate("main",
            "File to write NMEA frames recieved from the server"));

    parser.process(app);

    const QStringList args = parser.positionalArguments();
    if (args.count() != 1)
        parser.showHelp(-1);

    // passing filename to application and connect to server
    GPSClient client(args.at(0));

    return app.exec();
}
