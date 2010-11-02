#include "mainwindow.h"

#include <KAboutData>
#include <KAction>
#include <KApplication>
#include <KHelpMenu>
#include <KLocale>
#include <KMenu>
#include <KMenuBar>
#include <KSystemTrayIcon>
#include <KToolBar>


MainWindow::MainWindow( KApplication *app, QWidget *parent )
    : KMainWindow( parent )
    , m_quitAction( 0 )
    , m_addServerAction( 0 )
    , m_editServerAction( 0 )
    , m_removeServerAction( 0 )
    , m_refreshServerAction( 0 )
    , m_app( app )
    , m_about( 0 )
    , m_trayIcon( 0 )
{
    setWindowIcon( KIcon( "urtcontroller" ) );
    setFixedSize( 600, 400 );
    setupMenu();

    m_trayIcon = new KSystemTrayIcon( KIcon( "urtcontroller" ), this );
    m_trayIcon->setVisible( true );             // Show immediatly, on by default
}


void MainWindow::setupMenu()
{
    KMenuBar *menuBar = new KMenuBar( this );

    // program about data
    m_about = new KAboutData(
        "urtcontroller",                        // The program name used internally.
        0,                                      // The message catalog name. If null, program name is used instead.
        ki18n( "urtcontroller" ),               // A displayable program name string.
        "1.0",                                  // The program version string.
        ki18n( "Control multiple Urban Terror servers" ),
        KAboutData::License_GPL_V3,             // The license this code is released under
        ki18n("(c) 2010"),                      // Copyright Statement
        ki18n( "" ),                            // Optional text shown in the About box.Can contain any information desired.
        "http://2s2h.com",                      // The program homepage string.
        "francesco.nwokeka@gmail.com" );        // The bug report email address or website

    // author + people contributing to this project
    m_about->addAuthor( ki18n( "Francesco Nwokeka" ), ki18n( "Author" ), "francesco.nwokeka@gmail.com" );

    KMenu *fileMenu = new KMenu( i18n( "&File" ) );
    KMenu *editMenu = new KMenu( i18n( "&Settings" ) );
    KHelpMenu *helpMenu = new KHelpMenu( this, m_about );
    KToolBar *toolBar = new KToolBar( this );

    // menu actions
    m_quitAction = new KAction( KIcon( "application-exit"), i18n( "&Quit" ), this );
    m_editServerAction = new KAction( KIcon( "network-server" ), i18n( "&EditServer" ), this );

    // toolbar actions
    m_addServerAction = new KAction( KIcon( "list-add" ), i18n( "&AddServer" ), this );
    m_removeServerAction = new KAction( KIcon( "list-remove" ), i18n( "&RemoveServer" ), this );
    m_refreshServerAction = new KAction( KIcon( "view-refresh" ), i18n( "Re&freshServers" ), this );

    // connect actions
    connect( m_quitAction, SIGNAL( triggered() ), m_app, SLOT( quit() ) );

    // file menu setup
    fileMenu->addSeparator();
    fileMenu->addAction( m_quitAction );

    // edit menu setup
    editMenu->addAction( m_editServerAction );

    // toolbar actions
    toolBar->addAction( m_refreshServerAction );
    toolBar->addAction( m_addServerAction );
    toolBar->addAction( m_removeServerAction );

    // menu bar
    menuBar->addMenu( fileMenu );
    menuBar->addMenu( editMenu );
    menuBar->addMenu( helpMenu->menu());


    setMenuBar( menuBar );
}

