#include "pipe.h"
#include <QPainter>
#include <QStyleOption>

#ifdef QT_DEBUG
#include <QDebug>
#endif

Pipe::Pipe(int id, int x, int y, int width, int height, Type type, QGraphicsItem *parent)
    :QGraphicsItem(parent),m_id(id),baseX(x),baseY(y),m_width(width),m_height(height),m_type(type)
{
//#ifdef QT_DEBUG
//    qDebug()<< "id:"<<m_id<<" initialized";
//#endif

    if(m_type == PIPE_NORM)
        setFlags(ItemIsSelectable);
}

QRectF Pipe::boundingRect() const {
    //no pen width :)
    return QRectF(baseX,baseY,m_width,m_height);
}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    switch (m_type) {
        case PIPE_NORM:
            if(option->state & QStyle::State_Selected)
                painter->setBrush(Qt::black);
            else
                painter->setBrush(Qt::darkGray);
            break;
        case PIPE_INPUT:
            painter->setBrush(Qt::blue);
            break;
        case PIPE_OUTPUT:
            painter->setBrush(Qt::red);
            break;
        default:
            Q_UNREACHABLE();
#ifdef QT_DEBUG
        qDebug()<<"enumeration in pipe failed!";
#endif
            break;
    }

    painter->drawRect(baseX,baseY,m_width,m_height);

//for debug
//    painter->setPen(Qt::green);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawText(boundingRect(),Qt::AlignCenter,QString::number(m_id));
}


QPainterPath Pipe::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}
