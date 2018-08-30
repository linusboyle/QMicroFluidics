#ifndef PIPE_H
#define PIPE_H

#include <QGraphicsItem>

class Pipe :public QGraphicsItem
{
public:
    enum Type {
        PIPE_NORM = 1,
        PIPE_INPUT = 2,
        PIPE_OUTPUT = 4,
    };

    enum Orientation {
        HORIZONTAL = 1,
        VERTICAL = 2,
    };

    Pipe(int id,qreal x,qreal y,qreal width,qreal height,Orientation orientation
            ,Type type = PIPE_NORM,QGraphicsItem* parent = nullptr);
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void resetWidth(qreal width);

private:
    int m_id;
    qreal baseX;
    qreal baseY;
    qreal m_width;
    qreal m_height;

    Orientation m_orientation;
    Type m_type;
};

#endif // PIPE_H
