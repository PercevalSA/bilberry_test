#include <QCoreApplication>
#include <QCommandLineParser>

#include "server.h"

int main(int argc, char *argv[ ])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("gps-server");

    // get data file from command line
    QCommandLineParser parser;
    parser.setApplicationDescription("GPS Server");
    parser.addHelpOption();
    parser.addPositionalArgument("gps_data",
        QCoreApplication::translate("main",
            "File containing NMEA frames the server send"));

    parser.process(app);
    const QStringList args = parser.positionalArguments();
    if (args.count() != 1)
        parser.showHelp(-1);

    // passing data filename to application and start serving
    Server server(&(args.at(0)));

    return app.exec();
}
