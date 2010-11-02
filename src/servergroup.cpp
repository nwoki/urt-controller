#include "servergroup.h"

#include <KLocalizedString>
#include <QString>

ServerGroup::ServerGroup( const QString& name )
    : m_groupName( name )
{
    if( m_groupName.isEmpty() )
        m_groupName = i18n( "<Please set a label>" );
}

void ServerGroup::addServer( Server* server )
{
    m_servers.push_back( server );
}

void ServerGroup::addServer( const QString& name, const QString& address, const QString& rcon, int port )
{
    Server *auxServer = new Server( name, address, port, rcon );
    m_servers.push_back( auxServer );
}

QString ServerGroup::groupName() const
{
    return m_groupName;
}



