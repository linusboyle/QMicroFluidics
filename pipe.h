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
