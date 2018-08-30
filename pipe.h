#ifndef PIPE_H
#define PIPE_H

#include <QGraphicsItem>

class Pipe :public QObject,public QGraphicsItem
{
    Q_OBJECT
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
public slots:
    void resetWidth(qreal width);

signals:
    void requestWidthChange(qreal id,qreal newWidth);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_id;
    qreal baseX;
    qreal baseY;
    qreal m_width;
    qreal m_height;

    Orientation m_orientation;
    Types m_type;
};

#endif // PIPE_H
