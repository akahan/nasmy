#ifndef QFILEEDIT_H
#define QFILEEDIT_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QValidator>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QLineEdit>
#include <QAction>
#include <QStyle>

#include <QtDebug>

class QFileValidator : public QValidator {
    Q_OBJECT

    public:
        QFileValidator ( QObject* parent ) : QValidator( parent ) {
            qDebug() << "QFileValidator";
        }
        ~QFileValidator() {
            qDebug() << "~QFileValidator";
        }

        virtual State validate( QString& input, int& ) const Q_DECL_OVERRIDE {
            QFileInfo fi( input );
            qDebug() << "QFileValidator validate";

            if ( fi.isFile() && fi.exists() )
                return Acceptable;

            qDebug() << "QFileValidator Intermediate";

            return Intermediate;
        }
};

class QFolderValidator : public QValidator {
    Q_OBJECT

    public:
        QFolderValidator ( QObject* parent ) : QValidator( parent ) {
            qDebug() << "QFolderValidator";
        }
        ~QFolderValidator() {
            qDebug() << "~QFolderValidator";
        }

        virtual State validate( QString& input, int& ) const Q_DECL_OVERRIDE {
            QDir di( input );
            qDebug() << "QFolderValidator validate";

            if ( di.exists() )
                return Acceptable;

            qDebug() << "QFolderValidator Intermediate";

            return Intermediate;
        };
};

class QDESIGNER_WIDGET_EXPORT QFileEdit : public QLineEdit {
    Q_OBJECT

    public:
        enum Mode {
            OpenFileDialog,
            OpenFolderDialog
        };

        Q_ENUM( Mode )
        Q_PROPERTY( Mode mode READ mode WRITE setMode )
        Q_PROPERTY( QString filter READ filter WRITE setFilter )

        explicit QFileEdit( QWidget* parent = NULL, const Mode& mode = OpenFileDialog ) : QLineEdit( parent ) {
            setMode( mode );
            m_dialog_action = new QAction( QIcon( style()->standardPixmap( QStyle::SP_DialogOpenButton ) ), QString(), this );
            this->addAction( m_dialog_action, QLineEdit::LeadingPosition );
            connect( m_dialog_action, SIGNAL( triggered() ), this, SLOT( onDialogActionTriggered() ) );
        }

        inline const QString& filter() const { return m_filter; }
        void setFilter( const QString& value ) {
            if ( m_filter != value ) {
                m_filter = value;
            }
        }

        inline const Mode& mode() const { return m_mode; }
        void setMode( const Mode& value ) {
            if ( m_mode != value ) {
                m_mode = value;
                switch( m_mode ) {
                    case OpenFileDialog: {
                        (const_cast<QValidator *>(validator()))->deleteLater();
                        setValidator( new QFileValidator( this ) );
                        break;
                    }
                    case OpenFolderDialog: {
                        (const_cast<QValidator *>(validator()))->deleteLater();
                        setValidator( new QFolderValidator( this ) );
                        break;
                    }
                }
            }
        }

    protected slots:
        void onDialogActionTriggered() {
            if ( m_mode == OpenFileDialog ) {
                QFileInfo fi( text() );
                QString path = QFileDialog::getOpenFileName( this, tr( "Open File" ), fi.absoluteFilePath(), m_filter );
                if ( !path.isEmpty() )
                    setText( QDir::toNativeSeparators( path ) );
            }
            else if ( m_mode == OpenFolderDialog ) {
                QDir di( text() );
                QString path = QFileDialog::getExistingDirectory( this, tr( "Select Folder" ), di.absolutePath() );
                if ( !path.isEmpty() )
                    setText( QDir::toNativeSeparators( path ) );
            }
        }

    private:
        QAction * m_dialog_action;
        Mode m_mode;
        QString m_filter;
};

#endif // QFILEEDIT_H

