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

#include <KListWidget>
#include <KLocalizedString>
#include <KMessageBox>
#include <QDebug>
#include <QDockWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

ServerManager::ServerManager( QWidget *parent )
    : QWidget( parent )
    , m_serverGroupsList( 0 )
    , m_serversTable( 0 )
    , m_playersTable( 0 )
    , m_serverInfoTable( 0 )
    , m_listDock( 0 )
{
    setupGui();
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
}

QString ServerManager::currentGroupName() const
{
    return groupsList()->currentItem()->text();
}

QDockWidget* ServerManager::dockWidget() const
{
    return m_listDock;
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

            int j = 0;
            bool found = false;

            while( j < m_serverGroups.count() && !found ) {
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
