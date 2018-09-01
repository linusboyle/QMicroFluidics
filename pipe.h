/**
 * pipe.h
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
#ifndef PIPE_H
#define PIPE_H

#include <QGraphicsItem>

#define PIPE_LENGTH qreal(80)
#define PIPE_WIDTH qreal(10)

class Pipe :public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum Types {
        PIPE_NORM = 1,
        PIPE_INPUT = 2,
        PIPE_OUTPUT = 4,
    };

    enum Orientation {
        HORIZONTAL = 1,
        VERTICAL = 2,
    };

    enum { MyType = UserType+1};

    Pipe(int id,qreal x,qreal y,qreal width,qreal height,Orientation orientation,
             Types type = PIPE_NORM,QGraphicsItem* parent = nullptr);
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int type() const override;
    Types getType() const;
    Orientation getOrientation() const;
    QRectF realRect() const;

    void setDefaultColor(QColor color);

public slots:
    void resetWidth(qreal width);

signals:
    void requestWidthChange(qreal id);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_id;
    qreal baseX;
    qreal baseY;
    qreal m_width;
    qreal m_height;
    QColor m_defaultcolor;

    Orientation m_orientation;
    Types m_type;
};

#endif // PIPE_H
