#include "mainwindow.h"
#include "servermanager.h"

#include <KAboutData>
#include <KAction>
#include <KApplication>
#include <KDialog>
#include <KHelpMenu>
#include <KLineEdit>
#include <KListWidget>
#include <KLocale>
#include <KMenu>
#include <KMenuBar>
#include <KSystemTrayIcon>
#include <KToolBar>

#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow( KApplication *app, QWidget *parent )
    : KMainWindow( parent )
    , m_quitAction( 0 )
    , m_addServerAction( 0 )
    , m_editServerAction( 0 )
    , m_removeServerAction( 0 )
    , m_refreshServerAction( 0 )
    , m_addServerGroupAction( 0 )
    , m_removeServerGroupAction( 0 )
    , m_app( app )
    , m_about( 0 )
    , m_trayIcon( 0 )
    , m_serverManager( 0 )
    , m_addServerGroupDialog( 0 )
    , m_dialogServerGroupName( 0 )
{
    setWindowIcon( KIcon( "urtcontroller" ) );
    setMinimumSize( 600, 600 );
    setupMenu();

    m_trayIcon = new KSystemTrayIcon( KIcon( "urtcontroller" ), this );
    m_trayIcon->setVisible( true );             // Show immediatly, on by default

    // add serverlist dock widget
    m_serverManager = new ServerManager();
    addDockWidget( Qt::LeftDockWidgetArea, m_serverManager->dockWidget() );
    setCentralWidget( m_serverManager );

    // connect to activate toolbar
    connect( m_serverManager->groupsList(), SIGNAL( itemSelectionChanged() ), this, SLOT( activateToolbar() ) );

    // create dialogs
    createAddServerGroupDialog();
}

void MainWindow::activateToolbar()
{
    if( !m_addServerAction->isEnabled() )
        m_addServerAction->setEnabled( true );

    if( !m_removeServerAction->isEnabled() )
        m_removeServerAction->setEnabled( true );

    if( !m_refreshServerAction->isEnabled() )
        m_refreshServerAction->setEnabled( true );
}

void MainWindow::addServerGroupDialogOkClicked()
{
    // add group only if text is not empty
    if( !m_dialogServerGroupName->text().isEmpty() )
        addServerGroup( m_dialogServerGroupName->text() );
}

void MainWindow::showAddServerGroupDialog()
{
    if( !m_dialogServerGroupName->text().isEmpty() )
        m_dialogServerGroupName->clear();       // clear old text

    m_addServerGroupDialog->show();
}

void MainWindow::addServerGroup( const QString& name )
{
    m_serverManager->addNewServerGroup( name );
}

void MainWindow::createAddServerGroupDialog()
{
    m_addServerGroupDialog = new KDialog( this );
    m_dialogServerGroupName = new KLineEdit( this );

    QWidget *auxWidget = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();

    lay->addWidget( new QLabel( i18n( "Group name: " ) ) );
    lay->addWidget( m_dialogServerGroupName );
    auxWidget->setLayout( lay );

    m_addServerGroupDialog->setMainWidget( auxWidget );

    connect( m_addServerGroupDialog, SIGNAL( okClicked() ), this, SLOT( addServerGroupDialogOkClicked() ) );
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
    m_addServerGroupAction = new KAction( KIcon( "list-add" ), i18n( "AddServerGroup" ), this );
    m_removeServerGroupAction = new KAction( KIcon( "list-remove" ), i18n( "RemoveServerGroup" ), this );
    m_quitAction = new KAction( KIcon( "application-exit"), i18n( "&Quit" ), this );
    m_editServerAction = new KAction( KIcon( "network-server" ), i18n( "&EditServer" ), this );

    // toolbar actions ( all disabled until user clicks on a server group )
    m_addServerAction = new KAction( KIcon( "list-add" ), i18n( "&AddServer" ), this );
    m_addServerAction->setEnabled( false );
    m_removeServerAction = new KAction( KIcon( "list-remove" ), i18n( "&RemoveServer" ), this );
    m_removeServerAction->setEnabled( false );
    m_refreshServerAction = new KAction( KIcon( "view-refresh" ), i18n( "Re&freshServers" ), this );
    m_refreshServerAction->setEnabled( false );

    // connect actions
    connect( m_addServerGroupAction, SIGNAL( triggered() ), this, SLOT( showAddServerGroupDialog() ) );
    connect( m_quitAction, SIGNAL( triggered() ), m_app, SLOT( quit() ) );

    // file menu setup
    fileMenu->addAction( m_addServerGroupAction );
    fileMenu->addAction( m_removeServerGroupAction );
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
    menuBar->addMenu( helpMenu->menu() );

    setMenuBar( menuBar );
}

