/*
 * <one line to give the library's name and an idea of what it does.>
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

#include "nasmy.h"
#include "mainwindow.h"
#include "about.h"
#include "settingswindow.h"
#include "project/projectwindow.h"
#include "project/project.h"
#include "project/projectstreeitem.h"
#include "editor/asmedit.h"

// #include "editor/syntax/highlighter.h"

#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QTabBar>
#include <QTextCursor>
#include <QMimeData>

// #include <QQuickWidget>
// #include <QtQml/QQmlEngine>

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ) {
    setupGlobals();
    setupUi( this );

//     menubar->setAttribute( Qt::WA_DeleteOnClose, false );
    tabSources->removeTab( 0 );
    projectsTree->clear();
    watchesTree->clear();

//     setAttribute(Qt::WA_DeleteOnClose, false);
//     setAttribute(Qt::WA_QuitOnClose, false);

//     searchPanel = new SearchPanel(this);
//     searchPanel->hide();
//     searchPanel->move(0, splitter->sizes().at(0));

//     QFile styleFile(":/style.qss");
//     styleFile.open(QFile::ReadOnly);
//     QString style(styleFile.readAll());
//     setStyleSheet(style);
//     QPalette pal;
//     pal.setBrush(QPalette::HighlightedText, QColor(Qt::black));
//     pal.setBrush(QPalette::Highlight, QColor(Qt::lightGray));
//     errorView->setPalette(pal);

    setupActions();

    readSettings();

    updateRecentFileList();
    updateRecentProjectList();

//     QQuickWidget *view = new QQuickWidget(this);
//     view->setSource(QUrl("qrc:/dashboard.qml"));
//     tabFiles->setVisible(false);
//     setCentralWidget(view);

//     newFileController( "/home/jonny/projects/nasmy/test/testnum" );
//     newFileController();

    openProject( "/home/jonny/projects/testpto/testpto.nasmy" );

    statusBar()->showMessage( tr( "Ready" ) );
}

MainWindow::~MainWindow() {
    qDebug() << "~MainWindow";
}

void MainWindow::setupGlobals() {
    Nasmy::nasmy_ui = this;

    connect( Nasmy::fc(), &FilesController::fileLoaded, this, &MainWindow::onFilesController_fileLoaded );
    connect( Nasmy::pc(), &ProjectsController::projectLoaded, this, &MainWindow::onProjectsController_projectLoaded );
}

void MainWindow::readSettings() {
    closedFileNames = settings.value( "recentFileList" ).toStringList();
    closedProjectNames = settings.value( "recentProjectList" ).toStringList();

    settings.beginGroup( "MainWindow" );
    restoreGeometry( settings.value( "geometry", QByteArray() ).toByteArray() );
    restoreState( settings.value( "state", QByteArray() ).toByteArray() );
    settings.endGroup();
}

void MainWindow::saveSettings() {
    settings.setValue( "recentFileList", closedFileNames );
    settings.setValue( "recentProjectList", closedProjectNames );

    settings.beginGroup( "MainWindow" );
    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "state", saveState() );
    settings.endGroup();
}

void MainWindow::setupActions() {
    addAction(actionNewFile);
    addAction(actionOpenFile);
    addAction(actionSaveFile);
    addAction(actionSaveAs);
    addAction(actionClose);
    addAction(actionCloseAll);
    addAction(actionSaveAll);
    addAction(actionClearRecentFiles);
    addAction(actionSettings);
    addAction(actionAboutQt);
    addAction(actionAbout);
    addAction(actionExit);
    addAction(actionCopy);
    addAction(actionCut);
    addAction(actionPaste);
    addAction(actionUndo);
    addAction(actionRedo);
    addAction(actionSelectAll);
    addAction(actionRun);
    addAction(actionDebug);
    addAction(actionNewProject);
    addAction(actionBuildProject);
    addAction(actionCloseProject);
    addAction(actionCompileFile);
    addAction(actionOpenProject);
    addAction(actionStepInto);
    addAction(actionStepOver);
    addAction(actionStepOut);
    addAction(actionStop);
    addAction(actionRunToCursor);
    addAction(actionAddBreakpoint);
    addAction(actionClearRecentProjects);
    addAction(actionFind);
    addAction(actionReplace);
    addAction(actionFindInFiles);
    addAction(actionFormatFile);
    addAction(actionShowMenuBar);
    addAction(actionShowStatusBar);
    addAction(actionBuildAll);
    addAction(actionCleanProject);

    recentFileSeparator = menuRecentFiles->insertSeparator( actionClearRecentFiles );
    recentFileSeparator->setVisible( false );

    for ( int i = 0; i < MaxRecentFiles; ++i ) {
        recentFileActions[i] = new QAction( this );
        recentFileActions[i]->setVisible( false );
        connect( recentFileActions[i], &QAction::triggered, this, &MainWindow::onActionRecentFileOpen_triggered );
        menuRecentFiles->insertAction( !i ? recentFileSeparator : recentFileActions[0], recentFileActions[i] );
    }

    recentProjectSeparator = menuRecentProjects->insertSeparator( actionClearRecentProjects );
    recentProjectSeparator->setVisible( false );

    for ( int i = 0; i < MaxRecentFiles; ++i ) {
        recentProjectActions[i] = new QAction( this );
        recentProjectActions[i]->setVisible( false );
        connect( recentProjectActions[i], &QAction::triggered, this, &MainWindow::onActionRecentProjectOpen_triggered );
        menuRecentProjects->insertAction( !i ? recentProjectSeparator : recentProjectActions[0], recentProjectActions[i] );
    }

    //     connect(errorView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(goToError(QListWidgetItem*)));
    connect( QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::onClipboard_dataChanged );
}

void MainWindow::closeEvent( QCloseEvent* event ) {
//     QMainWindow::closeEvent( event );
    if ( on_actionCloseAll_triggered() ) {
        saveSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::resizeEvent( QResizeEvent* event ) {
    QMainWindow::resizeEvent( event );
}

bool MainWindow::maybeSave() {
    QMessageBox::StandardButton ret =
        Nasmy::question(
            tr( "The document was changed. Do you want to save changes?" ),
            QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Save,
            QMessageBox::Save
        );

    if ( ret == QMessageBox::Save ) {
        return on_actionSaveFile_triggered();
    }
    else if ( ret == QMessageBox::Cancel ) {
        return false;
    }

    return true;
}

bool MainWindow::saveFile() {
    File* file = Nasmy::fc()->getFile( tabSources->currentIndex() );

    try {
        file->save();
    }
    catch ( QString e ) {
        Nasmy::critical( tr( "Error write file %1:\n%2." ).arg( file->absolutePath() ).arg( e ) );
        return false;
    }

    pathLabel->setText( file->absolutePath() );

    statusBar()->showMessage( tr( "File saved" ), 2000 );

    return true;
}

void MainWindow::openFile( const QString& absolute_path ) {
    if ( absolute_path.isEmpty() ) {
        QStringList files =
            QFileDialog::getOpenFileNames( this,
                tr( "Open files" ),
                "/home/jonny/projects/nasmy/test/",
                tr( "NASM assembler files (*.asm *.nasm *.inc *.ninc);;All files (*)" )
            );

        if ( files.isEmpty() ) {
            return;
        }

        foreach( const QString &file, files ) {
            openFile( file );
        }

        statusBar()->showMessage( tr( "All files loaded" ), 2000 );
    }
    else {
        //check if file is opened
        if ( File* f = Nasmy::fc()->getFile( absolute_path ) ) {
            tabSources->setCurrentWidget( f->editor() );
            return;
        }

        Nasmy::fc()->loadFile( absolute_path );

        statusBar()->showMessage( tr( "File loaded" ), 2000 );
    }
}

void MainWindow::openProject( const QString& absolute_path ) {
    QString path;

    if ( absolute_path.isEmpty() ) {
        path =
            QFileDialog::getOpenFileName( this,
                tr( "Open project" ),
                "/home/jonny/projects/",
                tr( "Nasmy projects (*.nasmy)" )
            );

        if ( path.isEmpty() ) {
            return;
        }
    }
    else {
        path = absolute_path;
    }

    if (Nasmy::pc()->getProject( path )) {
        statusBar()->showMessage( tr( "Project already loaded" ), 2000 );
    }

    Nasmy::pc()->loadProject( path );

    //check if project is opened
    statusBar()->showMessage( tr( "Project loaded" ), 2000 );
}

void MainWindow::updateMenus() {
    bool at_least_one_opened = false;
    QString absolute_path = "";

    int tab_num = tabSources->currentIndex();

    if ( tab_num != -1 ) {
        at_least_one_opened = true;

        File* file = Nasmy::fc()->getFile(tab_num);
        absolute_path = file->absolutePath();

        bool modified = file->editor()->document()->isModified();
        actionSaveFile->setEnabled( modified );
        setWindowModified( modified );
        actionUndo->setEnabled( file->editor()->document()->isUndoAvailable() );
        actionRedo->setEnabled( file->editor()->document()->isRedoAvailable() );

        setWindowTitle( QString( "[ %1:%2 [*]] - %3" ).arg( "project" ).arg( file->title() ).arg( AppName ) );
    }

    actionSaveAs->setEnabled( at_least_one_opened );
    actionSaveAll->setEnabled( at_least_one_opened );
    actionClose->setEnabled( at_least_one_opened );
    actionCloseAll->setEnabled( at_least_one_opened );

    actionSelectAll->setEnabled( at_least_one_opened );

    actionFind->setEnabled( at_least_one_opened );
    actionReplace->setEnabled( at_least_one_opened );

    pathLabel->setText( absolute_path );
}

void MainWindow::onTextDocument_modificationChanged( bool modified ) {
    if ( modified ) {
        tabSources->setTabIcon( tabSources->currentIndex(), QIcon::fromTheme( "document-save" ) );
    }
    else {
        tabSources->setTabIcon( tabSources->currentIndex(), QIcon() );
    }

    setWindowModified( modified );
    updateMenus();
}

void MainWindow::updateRecentProjectList() {
    int numRecentFiles = qMin( ( int ) MaxRecentFiles, closedProjectNames.size() );

    for ( int i = 0; i < numRecentFiles; ++i ) {
        QString text = closedProjectNames.at( i );
        recentProjectActions[i]->setText( text );
        recentProjectActions[i]->setData( text );
        recentProjectActions[i]->setVisible( true );
    }

    for ( int j = numRecentFiles; j < MaxRecentFiles; ++j ) {
        recentProjectActions[j]->setVisible( false );
    }

    bool enable_clearing = numRecentFiles > 0;
    recentProjectSeparator->setVisible( enable_clearing );
    actionClearRecentProjects->setEnabled( enable_clearing );
}

void MainWindow::updateRecentFileList() {
    int numRecentFiles = qMin( ( int ) MaxRecentFiles, closedFileNames.size() );

    for ( int i = 0; i < numRecentFiles; ++i ) {
        QString text = closedFileNames.at( i );
        recentFileActions[i]->setText( text );
        recentFileActions[i]->setData( text );
        recentFileActions[i]->setVisible( true );
    }

    for ( int j = numRecentFiles; j < MaxRecentFiles; ++j ) {
        recentFileActions[j]->setVisible( false );
    }

    bool enable_clearing = numRecentFiles > 0;
    recentFileSeparator->setVisible( enable_clearing );
    actionClearRecentFiles->setEnabled( enable_clearing );
}

AsmEdit* MainWindow::currentEditor() {
    File* f = Nasmy::fc()->getFile( tabSources->currentIndex() );
    return f->editor();
}

/*****************************************************************************************

 ******************************************************************************************/

void MainWindow::on_actionNewProject_triggered() {
    ProjectWindow* frm = new ProjectWindow( this );
    QString project_path = frm->exec_and_return_path();
    if ( !project_path.isEmpty() ) {
        Nasmy::pc()->loadProject( project_path );
    }
}

void MainWindow::on_actionOpenProject_triggered() {
    openProject();
}

void MainWindow::on_actionClearRecentProjects_triggered() {
    closedProjectNames.clear();
    updateRecentProjectList();
}

void MainWindow::onActionRecentProjectOpen_triggered() {
    QAction* action = qobject_cast<QAction*> ( sender() );

    if ( action ) {
        QString absolute_path = action->data().toString();
        openProject( absolute_path );
        closedProjectNames.removeAll( absolute_path );
        updateRecentProjectList();
    }
}

void MainWindow::on_actionBuildProject_triggered() {
}

void MainWindow::on_actionCompileFile_triggered() {
}

void MainWindow::on_actionCloseProject_triggered() {
}

void MainWindow::on_actionRun_triggered() {
}

void MainWindow::on_actionDebug_triggered() {
}

void MainWindow::on_actionStop_triggered() {
}

void MainWindow::on_actionStepInto_triggered() {
}

void MainWindow::on_actionStepOver_triggered() {
}

void MainWindow::on_actionStepOut_triggered() {
}

void MainWindow::on_actionRunToCursor_triggered() {
}

void MainWindow::on_actionAddBreakpoint_triggered() {
}

void MainWindow::on_actionUndo_triggered() {
    currentEditor()->undo();
}

void MainWindow::on_actionRedo_triggered() {
    currentEditor()->redo();
}

void MainWindow::on_actionCut_triggered() {
    currentEditor()->cut();
}

void MainWindow::on_actionCopy_triggered() {
    currentEditor()->copy();
}

void MainWindow::on_actionPaste_triggered() {
    currentEditor()->paste();
}

void MainWindow::on_actionSelectAll_triggered() {
    currentEditor()->selectAll();
}

void MainWindow::on_actionFind_triggered() {
}

void MainWindow::on_actionReplace_triggered() {
}

void MainWindow::on_actionFindInFiles_triggered() {
}

void MainWindow::on_actionFormatFile_triggered() {
}

void MainWindow::on_actionNewFile_triggered() {
    Nasmy::fc()->loadFile();
}

void MainWindow::on_actionOpenFile_triggered() {
    openFile();
}

void MainWindow::on_actionClearRecentFiles_triggered() {
    closedFileNames.clear();
    updateRecentFileList();
}

void MainWindow::onActionRecentFileOpen_triggered() {
    QAction* action = qobject_cast<QAction*> ( sender() );

    if ( action ) {
        QString absolute_path = action->data().toString();
        openFile( absolute_path );
        closedFileNames.removeAll( absolute_path );
        updateRecentFileList();
    }
}

bool MainWindow::on_actionSaveFile_triggered() {
    int currentIndex = tabSources->currentIndex();

    if ( Nasmy::fc()->getFile( currentIndex )->absolutePath().isEmpty() ) {
        return on_actionSaveAs_triggered();
    }
    else {
        return saveFile();
    }
}

bool MainWindow::on_actionSaveAs_triggered() {
    File* file = Nasmy::fc()->getFile( tabSources->currentIndex() );
    QString absolute_path = file->absolutePath();

    absolute_path =
        QFileDialog::getSaveFileName( this,
            tr( "Save as" ),
            absolute_path,
            tr( "All files (*);;NASM assembler files (*.asm *.nasm *.inc *.ninc)" )
        );

    if ( absolute_path.isEmpty() ) {
        return false;
    }

    file->setAbsolutePath( absolute_path );
    tabSources->setTabText( tabSources->currentIndex(), QFileInfo( absolute_path ).fileName() );

    return saveFile();
}

void MainWindow::on_actionSaveAll_triggered() {
//     for ( int i = 0; i < tabSources->count(); ++i ) {
//         closeTabByIndex( i );
//     }
}

bool MainWindow::closeTabByIndex( const int index ) {
    //check tabs count
    if ( tabSources->count() == 0 ) {
        return true;
    }

    File* file = Nasmy::fc()->getFile( index );

    if ( file->editor()->document()->isModified() ) {
        if ( !maybeSave() ) {
            return false;
        }
    }

    if ( !file->absolutePath().isEmpty() ) {
        if ( !closedFileNames.contains( file->absolutePath() ) ) {
            //check size of closedFileNames before inserting new file name
            if ( closedFileNames.size() > MaxRecentFiles + 1 ) {
                closedFileNames.removeFirst();
            }

            closedFileNames.append( file->absolutePath() );
        }

        updateRecentFileList();
    }

    tabSources->blockSignals( true );

    Nasmy::fc()->unloadFile( index );

    tabSources->removeTab( index );

    //set current previous tab
    if ( index > 0 ) {
        tabSources->setCurrentIndex( index - 1 );
    }

    updateMenus();
    tabSources->blockSignals( false );

    return true;
}

void MainWindow::on_actionClose_triggered() {
    int index = tabSources->currentIndex();
    if ( index != -1 ) {
        closeTabByIndex( index );
    }
}

bool MainWindow::on_actionCloseAll_triggered() {
    bool can_continue = true;

    while ( tabSources->count() && can_continue ) {
        can_continue = closeTabByIndex( 0 );
    }

    return can_continue;
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::on_actionSettings_triggered() {
    SettingsWindow* frm = new SettingsWindow( this );
    frm->exec();
}

void MainWindow::on_actionShowMenuBar_toggled( bool show ) {
    show ? menuBar()->show() : menuBar()->hide();
}

void MainWindow::on_actionShowStatusBar_toggled( bool show ) {
    show ? statusBar()->show() : statusBar()->hide();
}

void MainWindow::on_actionAbout_triggered() {
    AboutWindow* frm = new AboutWindow( this );
    frm->exec();
}

void MainWindow::on_actionAboutQt_triggered() {
    QApplication::aboutQt();
}

void MainWindow::on_tabSources_tabCloseRequested( int index ) {
    closeTabByIndex( index );
}

void MainWindow::on_tabSources_currentChanged( int ) {
    updateMenus();
}

void MainWindow::onClipboard_dataChanged() {
    if ( const QMimeData * md = QApplication::clipboard()->mimeData() ) {
        actionPaste->setEnabled( md->hasText() );
    }
}

void MainWindow::onFilesController_fileLoaded( File* file ) {
    tabSources->addTab( file->editor(), file->title() );
    tabSources->setCurrentWidget( file->editor() );

    connect( file->editor()->document(), &QTextDocument::modificationChanged, this, &MainWindow::onTextDocument_modificationChanged );
    connect( file->editor(), &QPlainTextEdit::copyAvailable, actionCut, &QAction::setEnabled );
    connect( file->editor(), &QPlainTextEdit::copyAvailable, actionCopy, &QAction::setEnabled );

    onTextDocument_modificationChanged( false );
    file->editor()->setFocus();

}

void MainWindow::onProjectsController_projectLoaded(Project* p) {
    setWindowTitle( QString( "%1 - %2" ).arg( p->name() ).arg( AppName ) );
}

void MainWindow::on_projectsTree_itemSelectionChanged() {
//     projectsTree->selectedItems()
    projectSettings->setEnabled(true);
    addTarget->setEnabled(true);
}

void MainWindow::on_projectSettings_clicked(bool) {
    if ( Project* p = dynamic_cast<ProjectItem*>(projectsTree->selectedItems().at(0))->project() ) {
        ProjectWindow* frm = new ProjectWindow( this, p );
        QString project_path = frm->exec_and_return_path();
    }

//     if ( !project_path.isEmpty() ) {
//         Nasmy::pc()->loadProject( project_path );
//     }
}

void MainWindow::on_addTarget_clicked(bool) {
    Nasmy::information(QString("on_addTarget_clicked"));
}

void MainWindow::formatFile() {
//     FileController* fc = fileControllersList.at(tabFiles->currentIndex());
//
//     QString t = fc->editor()->toPlainText();
//     QJsonDocument dataDocument =  QJsonDocument::fromJson(t.toUtf8());
//     if (dataDocument.isEmpty()) {
//         qDebug() << "Invalid JSON, can't format";
//         return;
//     }
//     t = dataDocument.toJson(QJsonDocument::Indented);
//     fc->editor()->setPlainText(t);
//
//     statusBar()->showMessage("File formatted", 2000);
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on;

