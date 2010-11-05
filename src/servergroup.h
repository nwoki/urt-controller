/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * servergroup.h is part of Urtcontroller                                               *
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

#ifndef SERVERGROUP_H
#define SERVERGROUP_H

#include "server.h"
#include <QVector>

class QString;

/*
 * A logical class for grouping up servers
 */

class ServerGroup
{
public:
    ServerGroup( const QString &name );

    void addServer( const QString &serverAddress );     // adds a server to the group
    void deleteServer( const QString &address );        // deletes server from vector
    QString groupName() const;                          // returns group name
    Server* server( int index );                        // returns pointer to specified server at index
    int servers() const;                                // returns number of servers contain by servergroup

private:
    QString m_groupName;
    QVector< Server* > m_servers;
};

#endif
