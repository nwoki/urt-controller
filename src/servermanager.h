/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * servermanager.h is part of Urtcontroller                                             *
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

    void addNewServerGroup( const QString &name );
    QDockWidget *dockWidget() const;
    KListWidget *groupsList() const;

private:
    void refreshGroups();                       // refresh groups list
    void setupGui();                            // setup gui layout

    KListWidget *m_serverGroupsList;            // list widget with user's server groups
    QTableWidget *m_serversTable                // table with servergroups servers
    , *m_playersTable                           // table showing info on players in a server
    , *m_serverInfoTable;                       // table with server info
    QDockWidget *m_listDock;                    // dock used to contain listwidget and set to mainwindow
    QVector< ServerGroup* > m_serverGroups;     // vector with server groups
};

#endif
