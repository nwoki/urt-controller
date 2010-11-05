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


// getinfo
// ÿÿÿÿinfoResponse
//\game\q3ut4\maxPing\250\pure\1\gametype\4\sv_maxclients\14\clients\3\mapname\ut4_turnpike\hostname\^22s2h ^7return ^1ITA #1\protocol\68
/// TODO server info struct

class Server : public QObject
{
    Q_OBJECT
public:
    Server( const QString &address );       // only need address of server. All other info is set upon connect or refresh

    QString address() const;                // get server address
    QString currentPlayers() const;         // get server current players in game
    QString gametype() const;               // get server gametype
    bool isVaid() const;                    // returns validity of server
    QString map() const;                    // get server map
    QString maxPlayers() const;             // get server maxplayers allowed
    QString name() const;                   // get server name
    int port() const;                       // get server port
    QString rcon() const;                   // get server rcon

    void refreshServerInfo();               // refresh server info to display to user
//     void setAddress( QString address );     // set server address
//     void setName( QString name );           // set server name
//     void setPort( int port );               // set server port
    void setRcon( QString rcon );           // set server rcon password

public slots:
    void handleSocketError( QAbstractSocket::SocketError error );
    void parseRecievedData();

private:
    QString addressLookup( const QString &address );    // looks up address and returns ip if given a dns
    void getInfo();                               // sends "getinfo" to server

    void parseGetInfoCommand( QByteArray msg );         // parses info from the "getinfo" command

    QString m_address       // server address
    , m_currPlayers         // current number of players on server
    , m_gametype            // server gametype
    , m_map                 // current map being played on server
    , m_maxPlayers          // max players allowed on server
    , m_name                // server name
    , m_rcon;               // server rcon password
    int m_port;             // server port
    QUdpSocket *m_socket;   // server socket

    bool m_getInfoFlag      // flag to determine which command i'm waiting for when parsing data in response
    , m_validity;            // flag to determine validity of server
};

#endif


