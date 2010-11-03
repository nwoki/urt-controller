/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * server.cpp is part of Urtcontroller                                                  *
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

#include "server.h"

#include <KLocale>
#include <KMessageBox>
#include "ksocketfactory.h"
#include <QDebug>
#include <QHostInfo>
#include <QString>
// prefix that goes in front of all messages to server
#define PREFIX "\xff\xff\xff\xff"


/*
 * "\xff\xff\xff\xffrcon <pass> serverinfo"
 * "\xff\xff\xff\xff\x02getinfo"
 */

Server::Server( const QString &address )
    : QObject( 0 )
    , m_name( QString() )
    , m_address( QString() )
    , m_rcon( QString() )
    , m_port( 27960 )
{
    if( !address.contains( "." ) )
        KMessageBox::error( 0, i18n( "Invalid address" ) );

    else if( address.contains( ":" ) ) {                        // split string to extract port
        QStringList list = address.split( ':' );

        if( list.size() != 2 )
            KMessageBox::error( 0, i18n( "Invalid address" ) );
        else {
            m_address = addressLookup( list.at( 0 ) );          // resolve address
            bool ok;
            m_port = list.at( 1 ).toInt( &ok, 10 );

            if( !ok ) {
                KMessageBox::error( 0, i18n( "Invalid port, using default: 27960" ) );
                m_port = 27960;
            }
        }
    }
    else
        m_address = addressLookup( address );

    if( !m_address.isEmpty() ) {                                // create socket only if address "seems" valid
        m_socket = new QUdpSocket( this );
        m_socket->connectToHost( m_address, m_port );

        if( !m_socket->isValid() )
            KMessageBox::error( 0, m_socket->errorString() );   // FAIL

        // socket signals setup
        connect( m_socket, SIGNAL( readyRead() ), this, SLOT( parseRecievedData() ) );
        connect( m_socket, SIGNAL( error( QAbstractSocket::SocketError ) ), this, SLOT( handleSocketError( QAbstractSocket::SocketError ) ) );
    }
}

QString Server::name() const
{
    return m_name;
}

QString Server::address() const
{
    return m_address;
}

int Server::port() const
{
    return m_port;
}

QString Server::rcon() const
{
    return m_rcon;
}

void Server::setName( QString name )
{
    m_name = name;
}

void Server::setAddress( QString address )
{
    m_address = address;
}

void Server::setPort( int port )
{
    m_port = port;
}

void Server::setRcon( QString rcon )
{
    m_rcon = rcon;
}

void Server::handleSocketError( QAbstractSocket::SocketError )
{
    // just show message box for the moment
    KMessageBox::information( 0, m_socket->errorString() );
}

void Server::parseRecievedData()
{
    while( m_socket->hasPendingDatagrams() ) {
        if( m_socket->pendingDatagramSize() == -1 )
            qDebug( "no data to read" );
        qDebug() << m_socket->readAll();
    }
}

QString Server::addressLookup( const QString& address )
{
    QHostInfo info = QHostInfo::fromName( address );

    if( !info.addresses().isEmpty() )
        return info.addresses().first().toString(); // there should be only one address
    else
        return QString();
}


