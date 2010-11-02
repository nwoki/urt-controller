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

    void addServer( Server *server );
    void addServer( const QString &name, const QString &address, const QString &rcon, int port );

private:
    QString m_groupName;
    QVector< Server* > m_servers;
};

#endif
