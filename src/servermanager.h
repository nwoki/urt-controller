#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QWidget>

class KListWidget;
class QDockWidget;
class QTableWidget;

/*
 * Main widget. Keeps all together. Stores server objects and has the programs
 * layout. This class interacts with the user showing info stored in class objects
 */

class ServerManager : public QWidget
{
public:
    ServerManager( QWidget *parent = 0 );

    QDockWidget *dockWidget() const;

private:
    void setupGui();                    // setup gui layout

    KListWidget *m_serverGroupsList;
    QTableWidget *m_serversTable
    , *m_playersTable
    , *m_serverInfoTable;
    QDockWidget *m_listDock;            // dock used to contain listwidget and set to mainwindow
};

#endif
