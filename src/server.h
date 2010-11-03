/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * server.h is part of Urtcontroller                                                    *
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

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>
#include <QUdpSocket>

/*
 * Class that stores data about a server added by the user
 * to keep track of
 */

/// TODO server info struct

class Server : public QObject
{
    Q_OBJECT
public:
    Server( const QString &address );       // only need address of server. All other info is set upon connect or refresh

    QString address() const;                // get server address
    QString name() const;                   // get server name
    int port() const;                       // get server port
    QString rcon() const;                   // get server rcon

    void setAddress( QString address );     // set server address
    void setName( QString name );           // set server name
    void setPort( int port );               // set server port
    void setRcon( QString rcon );           // set server rcon password

public slots:
    void handleSocketError( QAbstractSocket::SocketError error );
    void parseRecievedData();

private:
    QString addressLookup( const QString &address );    // looks up address and returns ip if given a dns

    QString m_address       // server address
    , m_currPlayers         // current number of players on server
    , m_map                 // current map being played on server
    , m_maxPlayers          // max players allowed on server
    , m_name                // server name
    , m_rcon;               // server rcon password
    int m_port;             // server port
    QUdpSocket *m_socket;   // server socket
};

#endif


