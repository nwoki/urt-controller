#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>
#include "server.h"

class KAboutData;
class KAction;
class KApplication;
class KSystemTrayIcon;
class ServerManager;

/*
 * Mainwindow class that has menus and useful stuff
 */

class MainWindow : public KMainWindow
{
public:
    MainWindow( KApplication *app, QWidget *parent = 0 );

private:
    void setupMenu();               // setup mainwindow menu and dock

    KAction *m_quitAction           // quit program
    , *m_addServerAction            // add new server
    , *m_editServerAction           // edit server
    , *m_removeServerAction         // remove server
    , *m_refreshServerAction;       // refresh server list

    KApplication *m_app;            // pointer to application object

    KAboutData *m_about;            // program about data
    KSystemTrayIcon *m_trayIcon;    // program tray icon
    ServerManager *m_serverManager; // server manager class. Main class of the program
};


#endif