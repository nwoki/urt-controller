/****************************************************************************************
 * Urtcontroller - A graphical application to administrate an Urban Terror server       *
 * remotley                                                                             *
 *                                                                                      *
 * Copyright (C) 2010, Francesco Nwokeka                                                *
 *                                                                                      *
 * mainwindow.h is part of Urtcontroller                                                *
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

#include "server.h"

class KAboutData;
class KAction;
class KApplication;
class KComboBox;
class KDialog;
class KLineEdit;
class KSystemTrayIcon;
class ServerManager;

/*
 * Mainwindow class that has menus and useful stuff
 */

class MainWindow : public KMainWindow
{
    Q_OBJECT
public:
    MainWindow( KApplication *app, QWidget *parent = 0 );

public slots:
    void activateToolbar();                         // activate toolbar when user selects a server group from the list
    void addServerGroupDialogOkClicked();           // activated on ok when adding server group
    void deactivateToolbar();                       // deactivate toolbar when grouplist is empty
    void removeServerGroupDialogOkClicked();        // activated on ok when deleting a server group
    void showAddServerGroupDialog();
    void showRemoveServerGroupDialog();

private:
    void addServerGroup( const QString &name );     // adds server group to m_serverManager
    void createAddServerGroupDialog();              // creates the add server group dialog
    void createRemoveServerGroupDialog();           // creats the delete server group dialog
    void removeServerGroup( const QString &name );  // removes servergroup from m_serverManager
    void setupMenu();                               // setup mainwindow menu and dock
    void updateRemoveServerGroupName();             // updates the combobox with the names of the current servergroups available

    KAction *m_quitAction               // quit program
    , *m_addServerAction                // add new server
    , *m_editServerAction               // edit server
    , *m_removeServerAction             // remove server
    , *m_refreshServerAction            // refresh server list
    , *m_addServerGroupAction           // add a new server group
    , *m_removeServerGroupAction;       // remove a server group

    KApplication *m_app;                // pointer to application object

    KAboutData *m_about;                // program about data
    KSystemTrayIcon *m_trayIcon;        // program tray icon
    ServerManager *m_serverManager;     // server manager class. Main class of the program
    KDialog *m_addServerGroupDialog     // dialog presented when user wats to ad a server group
    , *m_removeServerGroupDialog;       // dialog presented when user wants to delete a server group
    //add server
    //remove server

    KLineEdit *m_dialogServerGroupName; // string that saves the name when adding new server group
    KComboBox *m_removeServerGroupName; // combo box with names of servergroups to remove
//     , m_dialogServerAddress;
};


#endif