#include "pipe.h"
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

#ifdef QT_DEBUG
#include <QDebug>
#endif

Pipe::Pipe(int id, qreal x, qreal y, qreal width, qreal height, Orientation orientation, Types type, QGraphicsItem *parent)
    :QGraphicsItem(parent),m_id(id),baseX(x),baseY(y),m_width(width),m_height(height),m_orientation(orientation),m_type(type)
{
    if(m_type == PIPE_NORM){
        setFlags(ItemIsSelectable);
        setAcceptHoverEvents(true);
    }
    setZValue(0);
}

QRectF Pipe::boundingRect() const {
    //no pen width :)
    return QRectF(baseX,baseY,m_width,m_height);
}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    if(option->state & QStyle::State_MouseOver)
        setZValue(1);
    else
        setZValue(0);

    painter->setPen(Qt::NoPen);
    switch (m_type) {
        case PIPE_NORM:
            if(option->state & QStyle::State_MouseOver){
                painter->setBrush(Qt::lightGray);
            }
            else if(option->state & QStyle::State_Selected)
                painter->setBrush(Qt::black);
            else
                painter->setBrush(Qt::darkGray);
            painter->drawRect(QRectF(baseX,baseY,m_width,m_height));
            break;
        case PIPE_INPUT:
            painter->setBrush(Qt::darkBlue);
            painter->drawRect(QRectF(baseX,baseY,m_width,m_height));

            painter->setPen(Qt::white);
            painter->setBrush(Qt::NoBrush);
            painter->drawText(boundingRect(),Qt::AlignCenter,QString("I\n"
                                                                     "N"));
            break;
        case PIPE_OUTPUT:
            painter->setBrush(Qt::darkCyan);
            painter->drawRect(QRectF(baseX,baseY,m_width,m_height));

            painter->setPen(Qt::white);
            painter->setBrush(Qt::NoBrush);
            painter->drawText(boundingRect(),Qt::AlignCenter,QString("O\n"
                                                                     "U\n"
                                                                     "T"));
            break;
        default:
            Q_UNREACHABLE();
#ifdef QT_DEBUG
        qDebug()<<"enumeration in pipe failed!";
#endif
            break;
    }
}


QPainterPath Pipe::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void Pipe::resetWidth(qreal width) {
    Q_ASSERT(width>0);

    switch (m_orientation) {
        case HORIZONTAL:
            baseY -= (width-m_height)/2;
            m_height = width;
            prepareGeometryChange();
            update();
            break;
        case VERTICAL:
            baseX -= (width-m_width)/2;
            m_width = width;
            prepareGeometryChange();
            update();
            break;
        default:
            Q_UNREACHABLE();
            break;
    }
}

void Pipe::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() != Qt::LeftButton)
        QGraphicsItem::mouseDoubleClickEvent(event);
    else{
        bool ok;
        double basevalue=0;

        if(m_orientation == VERTICAL)
            basevalue = this->m_width;
        else if(m_orientation == HORIZONTAL)
            basevalue = this->m_height;

        qreal newWidth = QInputDialog::getDouble(event->widget(),
                                                 QObject::tr("Change Width"),
                                                 QObject::tr("Input New Width:"),
                                                 basevalue,0,2147483647,1,
                                                 &ok,Qt::Dialog|Qt::FramelessWindowHint);
        if(ok){
            emit requestWidthChange(m_id,newWidth);
        }
    }
}

int Pipe::type() const{
    return MyType;
}

Pipe::Types Pipe::getType() const {
    return m_type;
}

Pipe::Orientation Pipe::getOrientation() const {
    return m_orientation;
}
