#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

class KAboutData;
class KAction;
class KApplication;
class KMenuBar;

class MainWindow : public KMainWindow
{
public:
    MainWindow( KApplication *app, QWidget *parent = 0 );

private:
    void setupMenu();
    KMenuBar *m_menuBar;

    KAction *m_quitAction       // quit program
    , *m_addServerAction;       // add new server
    KApplication *m_app;        // pointer to application object

    KAboutData *m_about;        // program about data
};


#endif