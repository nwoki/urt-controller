#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QWidget>

class KListWidget;
class QDockWidget;
class QString;
class QTableWidget;
class ServerGroup;

/*
 * Main widget. Keeps all together. Stores server objects and has the programs
 * layout. This class interacts with the user showing info stored in class objects
 */

class ServerManager : public QWidget
{
public:
    ServerManager( QWidget *parent = 0 );

    void addNewServerGroup();
    QDockWidget *dockWidget() const;

private:
    void setupGui();                            // setup gui layout

    KListWidget *m_serverGroupsList;            // list widget with user's server groups
    QTableWidget *m_serversTable                // table with servergroups servers
    , *m_playersTable                           // table showing info on players in a server
    , *m_serverInfoTable;                       // table with server info
    QDockWidget *m_listDock;                    // dock used to contain listwidget and set to mainwindow
    QVector< ServerGroup* > m_serverGroups;     // string -> groupName. vector -> group servers
};

#endif
