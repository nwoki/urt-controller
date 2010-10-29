#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "mainwindow.h"

int main( int argc, char **argv ) {
    KAboutData aboutData(
        "urtcontroller",                        // The program name used internally.
        0,                                      // The message catalog name. If null, program name is used instead.
        ki18n( "urtcontroller" ),               // A displayable program name string.
        "1.0",                                  // The program version string.
        ki18n("Control multiple UrT servers"),  // Short description of what the app does.
        KAboutData::License_GPL_V3,             // The license this code is released under
        ki18n("(c) 2010"),                      // Copyright Statement
        ki18n(""),                              // Optional text shown in the About box.Can contain any information desired.
        "http://2s2h.com",                      // The program homepage string.
        "francesco.nwokeka@gmail.com");         // The bug report email address

    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;

    MainWindow *main = new MainWindow();
    main->show();

    return app.exec();
}