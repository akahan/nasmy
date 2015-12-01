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

#ifndef COMPLETERPOPUPMODEL_H
#define COMPLETERPOPUPMODEL_H

#include <QStandardItemModel>

class CompleterPopupModel : public QStandardItemModel {
        Q_OBJECT

    public:
        CompleterPopupModel(QObject* parent = 0);
        CompleterPopupModel(int rows, int columns, QObject* parent = 0);

    signals:

    private:
        int n_rows;
        int n_columns;

    public slots:

    public:
        QVariant data(const QModelIndex& index, int role) const;
        virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
};

#endif // COMPLETERPOPUPMODEL_H
