/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * servergroup.cpp is part of Urtcontroller                                             *
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

#include <KLocalizedString>
#include <QString>

ServerGroup::ServerGroup( const QString& name )
    : m_groupName( name )
{
    // don't think i'll ever get an empty string here
    if( m_groupName.isEmpty() )
        m_groupName = i18n( "<Please set a label>" );
}

void ServerGroup::addServer(const QString& address )
{
    Server *auxServer = new Server( address );
    m_servers.push_back( auxServer );
}

void ServerGroup::deleteServer( const QString& address )
{
    qDebug( "sERVERgroup::deleteserver" );
    Server *auxServer = 0;
    bool found = false;

    for( int i = 0; i < m_servers.count() && !found; i++ ) {
        if( m_servers.at( i )->address() == address ) {
            qDebug( "FOUND" );
            auxServer = m_servers.at( i );
            m_servers.remove( i );
            found = true;
        }
    }

    delete auxServer;
}

QString ServerGroup::groupName() const
{
    return m_groupName;
}

Server* ServerGroup::server( int index )
{
    if( index > m_servers.count() )     // range check
        return new Server( QString() );
    else
        return m_servers.at( index );
}

int ServerGroup::servers() const
{
    return m_servers.count();
}





