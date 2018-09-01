/**
 * velocityindicator.h
 * Copyright (c) 2018 Linus Boyle <linusboyle@gmail.com>
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
 */
#ifndef VELOCITYINDICATOR_H
#define VELOCITYINDICATOR_H

#include <QTableWidget>

class VelocityIndicator:public QTableWidget
{
    Q_OBJECT
public:
    VelocityIndicator(QWidget* parent = nullptr);
    void clearAllText();

public slots:
    void onVelocityChanged(qreal,qreal,qreal);

private:
    void updateSize();
};

#endif // VELOCITYINDICATOR_H
