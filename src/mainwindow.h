/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  Roman Yusufkhanov <r.yusufkhanov@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "ui_mainwindow.h"

class File;
class Project;
class AsmEdit;
class Highlighter;
// class QListWidgetItem;

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

    public:
        explicit MainWindow( QWidget* parent = 0 );
        virtual ~MainWindow();

        AsmEdit* currentEditor();
        QSettings settings;

    protected:

        void closeEvent( QCloseEvent* );
        void resizeEvent( QResizeEvent* );

    private:
        void setupGlobals();

        void readSettings();
        void saveSettings();
        void setupActions();
        void updateMenus();
        void updateRecentFileList();
        void updateRecentProjectList();

        bool saveFileByIndex( const int index = -1 );
        bool maybeSave();
        bool saveFileAs();
        bool closeAllFiles();

        void openFile( const QString& abs_path = "" );
        void openProject( const QString& abs_path = "" );
        bool closeTabByIndex( const int index );

//         void goToError(QListWidgetItem*);
        void formatFile();

        //         SearchPanel* searchPanel;
        //         int previousIndex;

        enum { MaxRecentFiles = 10 };
        QAction* recentFileSeparator;
        QAction* recentProjectSeparator;
        QAction* recentFileActions[MaxRecentFiles];
        QAction* recentProjectActions[MaxRecentFiles];
        QStringList closedFileNames;
        QStringList closedProjectNames;

private slots:
        void on_actionNewProject_triggered();
        void on_actionOpenProject_triggered();
        void on_actionClearRecentProjects_triggered();
        void on_actionBuildProject_triggered();
        void on_actionCompileFile_triggered();
        void on_actionCloseProject_triggered();

        void on_actionRun_triggered();
        void on_actionDebug_triggered();
        void on_actionStop_triggered();
        void on_actionStepInto_triggered();
        void on_actionStepOver_triggered();
        void on_actionStepOut_triggered();
        void on_actionRunToCursor_triggered();
        void on_actionAddBreakpoint_triggered();

        void on_actionNewFile_triggered();
        void on_actionOpenFile_triggered();
        void on_actionClearRecentFiles_triggered();
        bool on_actionSaveFile_triggered();
        bool on_actionSaveAs_triggered();
        void on_actionSaveAll_triggered();
        void on_actionClose_triggered();
        void on_actionCloseAll_triggered();
        void on_actionExit_triggered();

        void on_actionUndo_triggered();
        void on_actionRedo_triggered();
        void on_actionCut_triggered();
        void on_actionCopy_triggered();
        void on_actionPaste_triggered();
        void on_actionSelectAll_triggered();
        void on_actionFind_triggered();
        void on_actionReplace_triggered();
        void on_actionFindInFiles_triggered();
        void on_actionFormatFile_triggered();

        void on_actionSettings_triggered();
        void on_actionShowMenuBar_toggled(bool);
        void on_actionShowStatusBar_toggled(bool);

        void on_actionAbout_triggered();
        void on_actionAboutQt_triggered();

        void on_tabSources_currentChanged( int );
        void on_tabSources_tabCloseRequested( int index );

        void onActionRecentProjectOpen_triggered();
        void onActionRecentFileOpen_triggered();
        void onClipboard_dataChanged();
        void onTextDocument_modificationChanged( bool );

        void onFilesController_fileLoaded(File*);

        void onProjectsController_projectLoaded(Project*);
        void onProjectsController_projectActivated(Project*);
        void on_projectsTree_itemSelectionChanged();
        void on_projectsTree_itemDoubleClicked( QTreeWidgetItem*, int );
        void on_projectSettings_clicked(bool);
        void on_addTarget_clicked(bool);
};

#endif // MAINWINDOW_H
