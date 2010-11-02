#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>

class QUdpSocket;
/*
 * Class that stores data about a server added by the user
 * to keep track of
 */

/// TODO server info struct

class Server : public QObject
{
    Q_OBJECT
public:
    Server( const QString &name, const QString &address, int port, const QString &rcon );

    QString name() const;                   // get server name
    QString address() const;                // get server address
    int port() const;                       // get server port
    QString rcon() const;                   // get server rcon

    void setName( QString name );           // set server name
    void setAddress( QString address );     // set server address
    void setPort( int port );               // set server port
    void setRcon( QString rcon );           // set server rcon password

private:
    QString m_name          // server name
    , m_address             // server address
    , m_rcon;               // server rcon password
    int m_port;             // server port
    QUdpSocket *m_socket;   // server socket
};

#endif


