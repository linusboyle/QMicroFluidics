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

    Pipe(int id,int x,int y,int width,int height,Type type = PIPE_NORM,QGraphicsItem* parent = nullptr);
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int m_id;
    int baseX;
    int baseY;
    int m_width;
    int m_height;

    Type m_type;
};

#endif // PIPE_H
