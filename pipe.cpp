#include "pipe.h"
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>

Pipe::Pipe(int id, qreal x, qreal y, qreal width, qreal height, Orientation orientation, Types type, QGraphicsItem *parent)
    :QGraphicsItem(parent),m_id(id),baseX(x),baseY(y),m_width(width),m_height(height),m_orientation(orientation),m_type(type)
{
    m_defaultcolor = QColor(Qt::darkGray);
    if(m_type == PIPE_NORM){
        setFlags(ItemIsSelectable);
        setAcceptHoverEvents(true);
    }
    setZValue(0);
}

QRectF Pipe::boundingRect() const {
    QRectF actualRect;

    if(m_type != PIPE_NORM){
        actualRect.setRect(baseX,baseY,m_width,m_height);
    }
    else if(m_orientation == VERTICAL){
        actualRect.setRect(baseX,baseY-PIPE_WIDTH,m_width,m_height+PIPE_WIDTH*2);
    } else if(m_orientation == HORIZONTAL){
        actualRect.setRect(baseX-PIPE_WIDTH,baseY,m_width+PIPE_WIDTH*2,m_height);
    }

    return actualRect;
}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    if(option->state & QStyle::State_MouseOver)
        setZValue(1);
    else if(option->state & QStyle::State_Selected)
        setZValue(1);
    else
        setZValue(0);

    QRectF actualRect = boundingRect();

    painter->setPen(Qt::NoPen);
    switch (m_type) {
        case PIPE_NORM:
            if(option->state & QStyle::State_MouseOver){
                painter->setBrush(Qt::lightGray);
            }
            else if(option->state & QStyle::State_Selected)
                painter->setBrush(Qt::black);
            else
                painter->setBrush(m_defaultcolor);
            painter->drawRect(actualRect);
            break;
            //only normal pipe needs to draw more space
        case PIPE_INPUT:
            painter->setBrush(m_defaultcolor);
            painter->drawRect(actualRect);

            painter->setPen(Qt::white);
            painter->setBrush(Qt::NoBrush);
            painter->drawText(boundingRect(),Qt::AlignCenter,QString("I\n"
                                                                     "N"));
            break;
        case PIPE_OUTPUT:
            painter->setBrush(m_defaultcolor);
            painter->drawRect(actualRect);

            painter->setPen(Qt::white);
            painter->setBrush(Qt::NoBrush);
            painter->drawText(boundingRect(),Qt::AlignCenter,QString("O\n"
                                                                     "U\n"
                                                                     "T"));
            break;
        default:
            Q_UNREACHABLE();
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
    else
            emit requestWidthChange(m_id);
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

QRectF Pipe::realRect() const {
    //it's the same with i/o pipes
    return QRectF(baseX,baseY,m_width,m_height);
}

void Pipe::setDefaultColor(QColor color){
    m_defaultcolor = color;
    update();
}
