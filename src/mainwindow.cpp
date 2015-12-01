/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
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
#include <QFileDialog>
#include <QMessageBox>
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

#include "about.h"
#include "settingswindow.h"
#include "project/projectwindow.h"
#include "project/project.h"
#include "editor/asmedit.h"
#include "editor/filecontroller.h"

#include "editor/syntax/highlighter.h"

// MainWindow& MainWindow::instance() {
//     static MainWindow m_instance;
//     return m_instance;
// }

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

//     connect(errorView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(goToError(QListWidgetItem*)));
    connect( QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::onClipboard_dataChanged );

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
        QMessageBox::question( this,
            qApp->applicationDisplayName(),
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
    FileController* fc = fileControllersList.at( tabSources->currentIndex() );

    try {
        fc->save();
    }
    catch ( QString e ) {
        QMessageBox::critical( this,
            qApp->applicationDisplayName(),
            tr( "Error write file %1:\n%2." ).arg( fc->absolutePath() ).arg( e )
        );

        return false;
    }

    pathLabel->setText( fc->absolutePath() );

    statusBar()->showMessage( tr( "File saved" ), 2000 );

    return true;
}

FileController* MainWindow::newFileController( QString absolute_path ) {
    FileController* fc = NULL;

    try {
        fc = new FileController( this, absolute_path );
        if ( !absolute_path.isEmpty() ) {
            fc->open();
        }
        fileControllersList.append( fc );
    }
    catch ( QString e ) {
        QMessageBox::warning( this,
            qApp->applicationDisplayName(),
            tr( "Error reading file %1:\n%2." ).arg( absolute_path ).arg( e )
        );

        if( fc ) delete fc;
        return NULL;
    }

    tabSources->addTab( fc->editor(), fc->title() );
    tabSources->setCurrentWidget( fc->editor() );

    connect( fc->editor()->document(), &QTextDocument::modificationChanged, this, &MainWindow::onTextDocument_modificationChanged );
    connect( fc->editor(), &QPlainTextEdit::copyAvailable, actionCut, &QAction::setEnabled );
    connect( fc->editor(), &QPlainTextEdit::copyAvailable, actionCopy, &QAction::setEnabled );

    onTextDocument_modificationChanged( false );
    fc->editor()->setFocus();

    return fc;
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
        for ( int i = 0; i < fileControllersList.size(); ++i ) {
            if ( fileControllersList.at( i )->absolutePath() == absolute_path ) {
                tabSources->setCurrentWidget( fileControllersList.at( i )->editor() );
                return;
            }
        }

        newFileController( absolute_path );

        statusBar()->showMessage( tr( "File loaded" ), 2000 );
    }
}

Project * MainWindow::newProject( QString absolute_path ) {
    Q_ASSERT( !absolute_path.isEmpty() );
    Project * pc = NULL;

    try {
        pc = new Project( this, absolute_path );
        pc->open();
        projectsList.append( pc );
    }
    catch ( QString e ) {
        QMessageBox::warning( this,
                              qApp->applicationDisplayName(),
                              tr( "Error reading project %1:\n%2." ).arg( absolute_path ).arg( e )
        );

        if ( pc ) delete pc;
        return NULL;
    }

    return pc;
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

    //check if project is opened
    foreach( Project * pc, projectsList ) {
        if ( pc->absolutePath() == path ) {
            statusBar()->showMessage( tr( "Project already loaded" ), 2000 );
            return;
        }
    }

    newProject( path );

    statusBar()->showMessage( tr( "Project loaded" ), 2000 );
}

void MainWindow::updateMenus() {
    bool at_least_one_opened = false;
    QString absolute_path = "";

    int tab_num = tabSources->currentIndex();

    if ( tab_num != -1 ) {
        FileController* fc = fileControllersList.at( tab_num );
        absolute_path = fc->absolutePath();
        at_least_one_opened = true;

        bool modified = fc->editor()->document()->isModified();
        actionSaveFile->setEnabled( modified );
        setWindowModified( modified );
        actionUndo->setEnabled( fc->editor()->document()->isUndoAvailable() );
        actionRedo->setEnabled( fc->editor()->document()->isRedoAvailable() );

        setWindowTitle( QString( "%1 - [ %2 [*]] - %3" ).arg( "project" ).arg( fc->title() ).arg( qApp->applicationDisplayName() ) );
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
    FileController* fc = fileControllersList.at( tabSources->currentIndex() );
    return fc->editor();
}

/*****************************************************************************************

 ******************************************************************************************/

void MainWindow::on_actionNewProject_triggered() {
    ProjectWindow* frm = new ProjectWindow( this, true );
    QString project_path = frm->exec_and_return_path();
    if ( !project_path.isEmpty() ) {
        newProject( project_path );
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
    newFileController();
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

    if ( fileControllersList.at( currentIndex )->absolutePath().isEmpty() ) {
        return on_actionSaveAs_triggered();
    }
    else {
        return saveFile();
    }
}

bool MainWindow::on_actionSaveAs_triggered() {
    FileController* fc = fileControllersList.at( tabSources->currentIndex() );
    QString absolute_path = fc->absolutePath();

    absolute_path =
        QFileDialog::getSaveFileName( this,
            tr( "Save as" ),
            absolute_path,
            tr( "All files (*);;NASM assembler files (*.asm *.nasm *.inc *.ninc)" )
        );

    if ( absolute_path.isEmpty() ) {
        return false;
    }

    fc->setAbsolutePath( absolute_path );
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

    FileController* fc = fileControllersList.at( index );

    if ( fc->editor()->document()->isModified() ) {
        if ( !maybeSave() ) {
            return false;
        }
    }

    fc->disconnect();

    if ( !fc->absolutePath().isEmpty() ) {
        if ( !closedFileNames.contains( fc->absolutePath() ) ) {
            //check size of closedFileNames before inserting new file name
            if ( closedFileNames.size() > MaxRecentFiles + 1 ) {
                closedFileNames.removeFirst();
            }

            closedFileNames.append( fc->absolutePath() );
        }

        updateRecentFileList();
    }

    tabSources->blockSignals( true );

    fileControllersList.removeAt( index );
    tabSources->removeTab( index );
    delete fc;

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

