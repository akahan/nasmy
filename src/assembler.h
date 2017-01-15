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

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "QObject"

class Assembler : public QObject
{
    Q_OBJECT

    public:
        explicit Assembler( const QString& arch );
        virtual ~Assembler();

        virtual void fillHighligherRules(
            QVector<Assembler::HighlightingRule> &highlightingRules,
            QList<QTextCharFormat *> &formats,
            bool &multiLineComments,
            QRegExp &commentStartExpression,
            QRegExp &commentEndExpression
        ) = 0;

        virtual QString getAssemblerOptions() = 0; //should return default assembler options
        virtual QString getLinkerOptions() = 0; //should return default linker options

    private:
        QString m_architecure;
};

#endif // ASSEMBLER_H
