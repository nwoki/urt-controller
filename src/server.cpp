#include "server.h"

#include <QUdpSocket>

Server::Server( const QString &name, const QString &address, int port, const QString &rcon )
    : QObject( 0 )
    , m_name( name )
    , m_address( address )
    , m_rcon( rcon )
    , m_port( port )
{
    m_socket = new QUdpSocket( this );
    m_socket->bind( QHostAddress( address ), qint16( port ) );
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
