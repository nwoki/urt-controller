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

void ServerManager::addNewServerGroup( const QString& name )
{
    ServerGroup *auxServerGroup = new ServerGroup( name );
    m_serverGroups.push_back( auxServerGroup );
    refreshGroups();
}

QDockWidget* ServerManager::dockWidget() const
{
    return m_listDock;
}

void ServerManager::refreshGroups()
{
    if( m_serverGroupsList->count() < m_serverGroups.count() ) {  // need to update list ADD
        for( int i = m_serverGroupsList->count(); i < m_serverGroups.count(); i++ )
            m_serverGroupsList->addItem( new QListWidgetItem( m_serverGroups.at( i )->groupName() ) );
    }
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

