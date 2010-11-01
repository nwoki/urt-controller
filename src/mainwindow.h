#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

class KAboutData;
class KAction;
class KApplication;
class KMenuBar;
class KSystemTrayIcon;

class MainWindow : public KMainWindow
{
public:
    MainWindow( KApplication *app, QWidget *parent = 0 );

private:
    void setupMenu();           // setup mainwindow menu and dock
    KMenuBar *m_menuBar;

    KAction *m_quitAction       // quit program
    , *m_addServerAction        // add new server
    , *m_editServerAction       // edit server
    , *m_removeServerAction     // remove server
    , *m_refreshServerAction;   // refresh server list

    KApplication *m_app;        // pointer to application object

    KAboutData *m_about;        // program about data
    KSystemTrayIcon *m_trayIcon;// program tray icon
};


#endif