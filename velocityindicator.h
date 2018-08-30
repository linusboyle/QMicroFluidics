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
};

#endif // VELOCITYINDICATOR_H
