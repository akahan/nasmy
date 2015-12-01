/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  Roman Yusufkhanov r.yusufkhanov@gmail.com
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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class Highlighter: public QSyntaxHighlighter {
        Q_OBJECT

    public:
        Highlighter(QTextDocument* parent = 0);

    private:
        struct HighlightingRule {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> rules;


    protected:
        void highlightBlock(const QString& text);
};

#endif // HIGHLIGHTER_H
