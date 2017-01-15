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

#include "asmedit.h"
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QTableView>
#include <QHeaderView>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QTextBlock>
#include <QFile>
#include <QFont>
#include <QFontMetrics>
#include <QBrush>
#include <QStringListModel>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QTextBlockFormat>
#include <QClipboard>
#include <QMenu>
#include <QPalette>

#include <QDebug>
#include <QtDebug>

AsmEdit::AsmEdit( QWidget* parent ) : QPlainTextEdit( parent ) {
    QFont font = QFontDatabase::systemFont( QFontDatabase::FixedFont );
    font.setPointSize( 12 );
    setFont( font );

//     qDebug() << fontMetrics().height() << fontMetrics().ascent() << fontMetrics().descent();

    int fh = fontMetrics().height();
    int ih = fh - 2;
    debug_image = QIcon( ":/resources/images/debug_point.svg" ).pixmap( ih, ih );
    break_image = QIcon( ":/resources/images/break_point.svg" ).pixmap( ih, ih );
    dbg_area_width = fh + 2;

//     curr_dbg_line = 10;
//     breakpoints.append( 1 );
//     breakpoints.append( 4 );
//     breakpoints.append( 7 );
//     breakpoints.append( 10 );

    can_breakpoints = true;
    show_line_numbers = true;
    side_area = new SideArea( this );

    setFrameShape( QFrame::NoFrame );
//     setWordWrapMode(QTextOption::NoWrap);
//     setWordWrapMode(QTextOption::WordWrap);
//     setWordWrapMode(QTextOption::WrapAnywhere);
    setWordWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );

    updateAdditionalAreaWidth( 0 );

//     qDebug() << contentOffset();
//     QColor textColor(230,230,230);
//
//     QPalette pal;
//     pal.setColor(QPalette::Text, textColor);
//     pal.setBrush(QPalette::HighlightedText, textColor);
//     pal.setBrush(QPalette::Highlight, QColor(85, 85, 85));
//     setPalette(pal);
//
//     clearColor.setRgb(45,45,45);
//
//     connect( this, SIGNAL( blockCountChanged( int ) ), this, SLOT( updateAdditionalAreaWidth( int ) ) );
//     connect( this, SIGNAL( updateRequest( QRect, int ) ), this, SLOT( onUpdateRequest( QRect, int ) ) );
    connect( this, &AsmEdit::blockCountChanged, this, &AsmEdit::updateAdditionalAreaWidth );
    connect( this, &AsmEdit::updateRequest, this, &AsmEdit::onUpdateRequest );
}

AsmEdit::~AsmEdit() {
    delete side_area;
}

void AsmEdit::contextMenuEvent( QContextMenuEvent* event ) {
    QPlainTextEdit::contextMenuEvent( event );
}

void AsmEdit::mousePressEvent( QMouseEvent* event ) {
    QPlainTextEdit::mousePressEvent( event );
//      checkCurrentObject();
//      highLightBraces();
}

void AsmEdit::focusInEvent( QFocusEvent* event ) {
//     if (c) {
//         c->setWidget(this);
//     }

    QPlainTextEdit::focusInEvent( event );
}

void AsmEdit::resizeEvent( QResizeEvent* event ) {
    QPlainTextEdit::resizeEvent( event );

    QRect cr = contentsRect();
    QRect vr = viewport()->rect();
    QRect visual = QStyle::visualRect( layoutDirection(), vr,
        QRect( cr.left(), cr.top(), sideAreaWidth(), vr.height() - vr.top() ) );

    if( visual != geometry() ) {
//         qDebug() << "[resizeEvent]" << cr << vr << visual;
        side_area->setGeometry( visual );
    }
}

void AsmEdit::keyPressEvent( QKeyEvent* event ) {
    QPlainTextEdit::keyPressEvent( event );
}

int AsmEdit::sideAreaWidth() {
    int space = dbg_area_width;

    if ( show_line_numbers ) {
        int digits = QString::number( blockCount() ).length();
        space = space + 5 + fontMetrics().width( QString( digits, '0' ) );
    }

    return space;
}

void AsmEdit::updateAdditionalAreaWidth( int ) {
    setViewportMargins( sideAreaWidth(), 0, 0, 0 );
}

void AsmEdit::onUpdateRequest( const QRect& rect, int dy ) {
//     qDebug() << "[onUpdateRequest]" << rect << dy << viewport()->rect() << side_area->geometry();
    if ( dy ) {
        side_area->scroll( 0, dy );
    }
    else {
        QRect arect( 0, rect.y(), side_area->width(), rect.height() );
//         qDebug() << "[onUpdateRequest]" << arect;
        side_area->update( arect );
    }

    if ( rect.contains( viewport()->rect() ) ) {
        updateAdditionalAreaWidth( 0 );
    }
}

void AsmEdit::sideAreaPaintEvent( QPaintEvent* event ) {
    QPainter painter( side_area );
    QRect er = event->rect();

//     painter.fillRect(er, clearColor); //background

    if ( show_line_numbers ) {
        painter.setPen( QColor( 160, 160, 160 ) ); //line
        painter.drawLine( dbg_area_width, er.top(), dbg_area_width, er.bottom() );
    }

    QTextCursor tc = textCursor();
    int fh = fontMetrics().height();
    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = ( int ) blockBoundingGeometry( block ).translated( contentOffset() ).top();
    int bottom = top + ( int ) blockBoundingRect( block ).height();

    while ( block.isValid() && top <= er.bottom() ) {
        if ( block.isVisible() && bottom >= er.top() ) {
            if ( show_line_numbers ) {
                if ( tc.blockNumber() == block_number ) {
                    painter.setPen( QColor( 90, 90, 90 ) ); //number current
                }
                else {
                    painter.setPen( QColor( 160, 160, 160 ) ); //number
                }

//                 painter.drawLine( 0, top, side_area->width(), top );
                QString number = QString::number( block_number + 1 );
                painter.drawText( 0, top, side_area->width() - 2, fh, Qt::AlignRight, number );
            }

            if ( breakpoints.contains( block_number + 1 ) && can_breakpoints ) {
                QRect rect( 2, top, break_image.width(), break_image.height() );
                painter.drawPixmap( rect, break_image );
            }

            if ( block_number + 1 == curr_dbg_line ) {
                QRect rect( 2, top, debug_image.width(), debug_image.height() );
                painter.drawPixmap( rect, debug_image );
            }
        }

        top = bottom;
        block = block.next();
        bottom = top + ( int ) blockBoundingRect( block ).height();
        block_number++;
    }
}

void AsmEdit::sideAreaMouseReleaseEvent( QMouseEvent* event ) {
    if ( can_breakpoints && event->x() < dbg_area_width ) {
        int line_number = 0;
        int ey = event->y();
        int range = ey / fontMetrics().height();
        line_number = range + verticalScrollBar()->value(); //+ invisible lines

//         qDebug() << ey << range << line_number << document()->lineCount();
        if ( line_number <= document()->lineCount() ) {
            line_number = document()->findBlockByLineNumber( line_number ).blockNumber() + 1;
//             qDebug() << line_number;

            //add or remove line number in list
            if ( breakpoints.contains( line_number ) ) {
                breakpoints.removeOne( line_number );
                emit breakpointsChanged( line_number, false );
            }
            else {
                breakpoints.append( line_number );
                emit breakpointsChanged( line_number, true );
            }

            emit updateRequest( side_area->rect(), 0 );
        }
    }
}
