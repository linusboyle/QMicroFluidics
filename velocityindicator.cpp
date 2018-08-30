#include "velocityindicator.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

VelocityIndicator::VelocityIndicator(QWidget *parent)
    :QTableWidget(parent)
{
    setRowCount(1);
    setColumnCount(3);
    setHorizontalHeaderLabels(QStringList()<<"Output1"<<"Output2"<<"Output3");

    QTableWidgetItem* output1 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output2 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output3 = new QTableWidgetItem(tr("Unknown"));

    setItem(0,0,output1);
    setItem(0,1,output2);
    setItem(0,2,output3);

    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

    setMaximumHeight(100);
}

void VelocityIndicator::onVelocityChanged(qreal out1, qreal out2, qreal out3){
    item(0,0)->setText(QString::number(out1));
    item(0,1)->setText(QString::number(out2));
    item(0,2)->setText(QString::number(out3));
}

void VelocityIndicator::clearAllText() {
    item(0,0)->setText("Unknown");
    item(0,1)->setText("Unknown");
    item(0,2)->setText("Unknown");
}
