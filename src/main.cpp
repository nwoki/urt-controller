/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * main.cpp is part of Urtcontroller                                                    *
 *                                                                                      *
 * Urtcontroller is free software: you can redistribute it and/or modify it under the   *
 * terms of the GNU General Public License as published by the Free Software Foundation,*
 * either version 3 of the License, or (at your option) any later version.              *
 *                                                                                      *
 * Urtcontroller is distributed in the hope that it will be useful, but WITHOUT ANY     *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.            *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with this    *
 * program.  If not, see <http://www.gnu.org/licenses/>.                                *
 ****************************************************************************************/

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

    KApplication *app = new KApplication();

    MainWindow *main = new MainWindow( app );
    main->show();

    return app->exec();
}