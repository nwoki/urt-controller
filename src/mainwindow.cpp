/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * mainwindow.cpp is part of Urtcontroller                                              *
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

#include "mainwindow.h"
#include "servermanager.h"

#include <KAboutData>
#include <KAction>
#include <KApplication>
#include <KComboBox>
#include <KDialog>
#include <KHelpMenu>
#include <KLineEdit>
#include <KListWidget>
#include <KLocale>
#include <KMenu>
#include <KMenuBar>
#include <KSystemTrayIcon>
#include <KToolBar>

#include <QDebug>
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
    , m_removeServerGroupDialog( 0 )
    , m_addServerDialog( 0 )
    , m_dialogServerGroupName( 0 )
    , m_dialogAddServerAddress( 0 )
    , m_removeServerGroupName( 0 )
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

    // connect to activate and deactivate toolbar
    connect( m_serverManager->groupsList(), SIGNAL( itemSelectionChanged() ), this, SLOT( activateToolbar() ) );
    connect ( m_serverManager, SIGNAL( emptyServerList() ), this, SLOT( deactivateToolbar() ) );

    // create dialogs
    createAddServerGroupDialog();
    createRemoveServerGroupDialog();
    createAddServerDialog();
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

void MainWindow::addServerDialogOkClicked()
{
    QString text = m_dialogAddServerAddress->text();
    if( !text.isEmpty() )
        m_serverManager->addNewServer( m_serverManager->currentGroupName(), text );
}

void MainWindow::addServerGroupDialogOkClicked()
{
    // add group only if text is not empty
    QString groupName = m_dialogServerGroupName->text();
    if( !groupName.isEmpty() )
        m_serverManager->addNewServerGroup( groupName );
}

void MainWindow::deactivateToolbar()
{
    if( m_addServerAction->isEnabled() )
        m_addServerAction->setEnabled( false );

    if( m_removeServerAction->isEnabled() )
        m_removeServerAction->setEnabled( false );

    if( m_refreshServerAction->isEnabled() )
        m_refreshServerAction->setEnabled( false );
}

void MainWindow::removeServerGroupDialogOkClicked()
{
    QString groupName = m_removeServerGroupName->currentText();
    if( !groupName.isEmpty() )
        m_serverManager->removeServerGroup( groupName );
}

void MainWindow::showAddServerDialog()
{
    if( !m_dialogAddServerAddress->text().isEmpty() )
        m_dialogAddServerAddress->clear();      // clear old text

    m_addServerDialog->show();
}

void MainWindow::showAddServerGroupDialog()
{
    if( !m_dialogServerGroupName->text().isEmpty() )
        m_dialogServerGroupName->clear();       // clear old text

    m_addServerGroupDialog->show();
}

void MainWindow::showRemoveServerGroupDialog()
{
    updateRemoveServerGroupName();
    m_removeServerGroupDialog->show();
}

void MainWindow::createAddServerDialog()
{
    m_addServerDialog = new KDialog( this );
    m_dialogAddServerAddress = new KLineEdit( this );

    QWidget *auxWidget = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();

    lay->addWidget( new QLabel( i18n( "Server Address: " ) ) );
    lay->addWidget( m_dialogAddServerAddress );
    auxWidget->setLayout( lay );

    m_addServerDialog->setMainWidget( auxWidget );

    connect( m_addServerDialog, SIGNAL( okClicked() ), this, SLOT( addServerDialogOkClicked() ) );
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

void MainWindow::createRemoveServerGroupDialog()
{
    m_removeServerGroupDialog = new KDialog( this );
    m_removeServerGroupName = new KComboBox( false, this ); // don't need the combobox to be editable

    // populate combobox
    for( int i = 0; i < m_serverManager->serverGroups(); i++ )
        m_removeServerGroupName->insertItem( i, KIcon( "network-server" ), m_serverManager->serverGroupName( i ) );

    QWidget *auxWidget = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();

    lay->addWidget( new QLabel( i18n( "Delete group: " ) ) );
    lay->addWidget( m_removeServerGroupName );
    auxWidget->setLayout( lay );

    m_removeServerGroupDialog->setMainWidget( auxWidget );

    connect( m_removeServerGroupDialog, SIGNAL( okClicked() ), this, SLOT( removeServerGroupDialogOkClicked() ) );
}

void MainWindow::setupMenu()
{
    KMenuBar *menuBar = new KMenuBar( this );

    // program about data
    m_about = new KAboutData(
        "urtcontroller",                        // The program name used internally.
        0,                                      // The message catalog name. If null, program name is used instead.
        ki18n( "urtcontroller" ),               // A displayable program name string.
        "1.0beta",                              // The program version string.
        ki18n( "Control and administrate multiple Urban Terror servers" ),
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
    connect( m_removeServerGroupAction, SIGNAL( triggered() ), this, SLOT( showRemoveServerGroupDialog() ) );
    connect( m_quitAction, SIGNAL( triggered() ), m_app, SLOT( quit() ) );

    // toolbar
    connect( m_addServerAction, SIGNAL( triggered() ), this, SLOT( showAddServerDialog() ) );

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

void MainWindow::updateRemoveServerGroupName()
{
    if( m_removeServerGroupName->count() != 0 )
        m_removeServerGroupName->clear();

    // populate
    for( int i = 0; i < m_serverManager->serverGroups(); i++ )
        m_removeServerGroupName->insertItem( i, KIcon( "network-server" ), m_serverManager->serverGroupName( i ) );
}


