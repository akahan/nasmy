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

#ifndef ASMEDIT_H
#define ASMEDIT_H

#include <QPlainTextEdit>

class QCompleter;
class AdditionalArea;

class AsmEdit : public QPlainTextEdit {
    Q_OBJECT

    friend class AdditionalArea;

    public:
        AsmEdit( QWidget* parent = 0 );
        ~AsmEdit();

        int curr_dbg_line;

        int additionalAreaWidth();

    signals:
//         void endOfCheckingCursorPositions();
        void breakpointsChanged( quint64 line_number, bool is_added );

    public slots:

    private slots:
        void updateAdditionalAreaWidth( int newBlockCount );
        void onUpdateRequest( const QRect&, int );

    protected:
        void keyPressEvent( QKeyEvent * );
        void focusInEvent( QFocusEvent* );
        void mousePressEvent( QMouseEvent* );
        void resizeEvent( QResizeEvent* );
        void contextMenuEvent( QContextMenuEvent* );

        void additionalAreaPaintEvent( QPaintEvent* );
        void additionalAreaMouseReleaseEvent( QMouseEvent* );

    private:

        AdditionalArea* additional_area;
        QPixmap debug_image;
        QPixmap break_image;

        int dbg_area_width;
        bool can_breakpoints;
        bool show_line_numbers;
        QList<int> breakpoints;
};

class AdditionalArea : public QWidget {
    public:
        AdditionalArea( AsmEdit* editor ) : QWidget( editor ) {
//             setGeometry(0,0,0,0);
            asm_edit = editor;
        }

        QSize sizeHint() const Q_DECL_OVERRIDE {
            return QSize( asm_edit->additionalAreaWidth(), 0 );
        }

    protected:
        void paintEvent( QPaintEvent* event ) Q_DECL_OVERRIDE {
            asm_edit->additionalAreaPaintEvent( event );
        }

        void mouseReleaseEvent( QMouseEvent *event ) Q_DECL_OVERRIDE {
            asm_edit->additionalAreaMouseReleaseEvent( event );
        }

        void mousePressEvent( QMouseEvent * ) Q_DECL_OVERRIDE {
//             asm_edit->additionalAreaMousePressEvent( event );
        }

        void wheelEvent( QWheelEvent *event ) Q_DECL_OVERRIDE {
            asm_edit->wheelEvent( event );
        }

    private:
        AsmEdit* asm_edit;
};

#endif // ASMEDIT_H
