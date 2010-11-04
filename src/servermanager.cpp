/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * servermanager.cpp is part of Urtcontroller                                           *
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

#include "servergroup.h"
#include "servermanager.h"

#include <KConfig>
#include <KConfigGroup>
#include <KListWidget>
#include <KLocalizedString>
#include <KMessageBox>

#include <QDebug>
#include <QDockWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

ServerManager::ServerManager( QWidget *parent )
    : QWidget( parent )
    , m_serverGroupsList( 0 )
    , m_serversTable( 0 )
    , m_playersTable( 0 )
    , m_serverInfoTable( 0 )
    , m_listDock( 0 )
{
    setupGui();     // first create gui
    loadConfig();   // then add items and stuff from config
}

void ServerManager::addNewServer( const QString& group, const QString& serverAddress )
{
    ServerGroup *auxGroup = 0;

    for( int i = 0; i < m_serverGroups.count(); i++ ) {
        if( m_serverGroups.at( i )->groupName() == group )
            auxGroup = m_serverGroups.at( i );
    }

    if( !auxGroup ) {
        qWarning() << "ServerManager::addNewServer ERROR: can't find servergroup: " << group;
        KMessageBox::sorry( this, "Can't find selected server group" );
    }
    else
        auxGroup->addServer( serverAddress );
}

void ServerManager::addNewServerGroup( const QString& name )
{
    ServerGroup *auxServerGroup = new ServerGroup( name );
    m_serverGroups.push_back( auxServerGroup );
    refreshGroups();
    addServerGroupToConfig( name );
}

QString ServerManager::currentGroupName() const
{
    return groupsList()->currentItem()->text();
}

QDockWidget* ServerManager::dockWidget() const
{
    return m_listDock;
}

void ServerManager::refreshGUI()
{
    bool found = false;
    int i = 0;
    ServerGroup *auxServerGroup = 0;

    while( i < serverGroups() && !found ) {
        if( m_serverGroups.at( i )->groupName() == currentGroupName() ) {
            auxServerGroup = m_serverGroups.at( i );
            found = true;
        }
        i++;
    }

    refreshServersTable( auxServerGroup );
}

void ServerManager::addServerGroupToConfig( const QString& name )
{
    KConfig config;
    KConfigGroup serverGroups = config.group( "ServerGroups" );
    KConfigGroup newGroup = serverGroups.group( name );
    newGroup.writeEntry( "name", name );
    newGroup.writeEntry( "servers", name + "-servers" );
    config.sync();
}

void ServerManager::loadConfig()
{
    KConfig config;
    KConfigGroup groups = config.group( "ServerGroups" );
    QStringList groupNames = groups.groupList();

    for( int i = 0; i < groupNames.size(); i++ )
        addNewServerGroup( groupNames.at( i ) );
}

void ServerManager::refreshGroups()
{
    if( m_serverGroupsList->count() < m_serverGroups.count() ) {        // update list ADD
        for( int i = m_serverGroupsList->count(); i < m_serverGroups.count(); i++ )
            m_serverGroupsList->addItem( new QListWidgetItem( m_serverGroups.at( i )->groupName() ) );
    }
    else if( m_serverGroupsList->count() > m_serverGroups.count() ) {   // elimate from list REMOVE
        for( int i = 0; i < m_serverGroupsList->count(); i++ ) {
            QListWidgetItem *auxItem = m_serverGroupsList->item( i );
            ServerGroup *auxServerGroup;

            bool found = false;

            for( int j = 0; j < m_serverGroups.count() && !found; j++ ) {
                auxServerGroup = m_serverGroups.at( j );
                if( auxItem->text() == auxServerGroup->groupName() )
                    found = true;
            }
            if( !found ) {      // eliminate serverGroup
                m_serverGroupsList->removeItemWidget( m_serverGroupsList->item( i ) );
                delete auxItem; // do i need this?
            }
        }
    }

    if( m_serverGroups.empty() )    // notify mainwindow
        emit emptyServerList();
}

void ServerManager::refreshServersTable( ServerGroup* serverGroup )
{
    m_serversTable->clearContents();                        // fresh start
    m_serversTable->setRowCount( serverGroup->servers() );  // update rows

    for( int i = 0; i < serverGroup->servers(); i++ ) {
        Server *auxServer = serverGroup->server( i );

        // create item for table widget
        QTableWidgetItem *nameItem = new QTableWidgetItem( KIcon( "urtcontroller" ), auxServer->name() );
        nameItem->setTextAlignment( Qt::AlignLeft );
        QTableWidgetItem *addrItem = new QTableWidgetItem( auxServer->address() );
        addrItem->setTextAlignment( Qt::AlignLeft );
        QTableWidgetItem *pingItem = new QTableWidgetItem( "TODO" );   ///TODO ping value goes here!
        pingItem->setTextAlignment( Qt::AlignHCenter );
        QTableWidgetItem *playersItem = new QTableWidgetItem( KIcon( "im-user" ), auxServer->currentPlayers() + "/" + auxServer->maxPlayers() );
        playersItem->setTextAlignment( Qt::AlignHCenter );
        QTableWidgetItem *mapItem = new QTableWidgetItem( auxServer->map() );
        mapItem->setTextAlignment( Qt::AlignHCenter );
        QTableWidgetItem *gametypeItem = new QTableWidgetItem( auxServer->gametype() );
        gametypeItem->setTextAlignment( Qt::AlignHCenter );

        m_serversTable->setItem( i, 0, nameItem );
        m_serversTable->setItem( i, 1, addrItem );
        m_serversTable->setItem( i, 2, pingItem );
        m_serversTable->setItem( i, 3, playersItem );
        m_serversTable->setItem( i, 4, mapItem );
        m_serversTable->setItem( i, 5, gametypeItem );
    }
}

void ServerManager::removeServerGroup( const QString& name )
{
    ServerGroup *auxServerGroup;
    bool found = false;
    int i = 0;

    while( i < m_serverGroups.count() && !found ) {
        if( m_serverGroups.at( i )->groupName() == name ) {
            auxServerGroup = m_serverGroups.at( i );
            m_serverGroups.remove( i );
            delete auxServerGroup;
            found = true;
        }
        else
            i++;
    }
    refreshGroups();    // to update list
    removeServerGroupFromConfig( name );
}

QString ServerManager::serverGroupName( int index )
{
    if( index > m_serverGroups.count() )    // over the limit!
        return i18n( "<empty>" );
    else
        return m_serverGroups.at( index )->groupName();
}

int ServerManager::serverGroups() const
{
    return m_serverGroups.count();
}

KListWidget* ServerManager::groupsList() const
{
    return m_serverGroupsList;
}

void ServerManager::removeServerGroupFromConfig( const QString& name )
{
    KConfig config;
    KConfigGroup serverGroups = config.group( "ServerGroups" );
    KConfigGroup serverToDelete = serverGroups.group( name );
    KConfigGroup servers = config.group( "servers" );
    // get groupname related servers
    QString groupServersToDelete = serverToDelete.readEntry( "servers" );

    // delete servers related to group
    servers.deleteGroup( groupServersToDelete );
    // delete server group
    serverGroups.deleteGroup( name );
    config.sync();
}

void ServerManager::setupGui()
{
    /// TODO check that objects aren't already created and exit from this function if so

    QVBoxLayout *vertLay = new QVBoxLayout();           // holds servers table and small horrlay
    QHBoxLayout *horrLay = new QHBoxLayout();           // holds playersTable and serverInfoTable

    m_serverGroupsList = new KListWidget();

    m_listDock = new QDockWidget( i18n( "ServerGroups" ) );
    m_listDock->setFeatures( QDockWidget::NoDockWidgetFeatures );
    m_listDock->setWidget( m_serverGroupsList );

    m_serversTable = new QTableWidget( 0, 6 );
    m_serversTable->setHorizontalHeaderLabels( QStringList() << i18n( "Name" ) << i18n( "Address" ) << i18n( "Ping" ) << i18n( "#Players" ) << i18n( "Map" ) << i18n( "Gametype" ) );
    m_serversTable->setAlternatingRowColors( true );
    m_serversTable->setEditTriggers( QAbstractItemView::NoEditTriggers );
    m_serversTable->setShowGrid( false );
    m_serversTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    m_serversTable->setSelectionMode( QAbstractItemView::SingleSelection );
    m_serversTable->verticalHeader()->hide();
    m_serversTable->horizontalHeader()->setStretchLastSection( true );


    m_serverInfoTable = new QTableWidget( 0, 2 );
    m_serverInfoTable->setHorizontalHeaderLabels( QStringList() << i18n( "Setting" ) << i18n( "Value" ) );

    m_playersTable = new QTableWidget( 0, 4 );
    m_playersTable->setHorizontalHeaderLabels( QStringList() << i18n( "Name" ) << i18n( "Frags" ) << i18n( "Ping" ) << i18n( "Ip" ) );

    horrLay->addWidget( m_playersTable );
    horrLay->addWidget( m_serverInfoTable );

    vertLay->addWidget( m_serversTable );
    vertLay->addLayout( horrLay );

    setLayout( vertLay );
}

