#include "velocityindicator.h"
#include <QHeaderView>

//#ifdef QT_DEBUG
//#include <QDebug>
//#endif

VelocityIndicator::VelocityIndicator(QWidget *parent)
    :QTableWidget(parent)
{
    setRowCount(1);
    setColumnCount(3);
    setHorizontalHeaderLabels(QStringList()<<"Output1"<<"Output2"<<"Output3");

    QTableWidgetItem* output1 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output2 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output3 = new QTableWidgetItem(tr("Unknown"));

    output1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    output2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    output3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    setItem(0,0,output1);
    setItem(0,1,output2);
    setItem(0,2,output3);

    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    verticalHeader()->setVisible(false);

    updateSize();
}

void VelocityIndicator::onVelocityChanged(qreal out1, qreal out2, qreal out3){
    item(0,0)->setText(QString::number(out1));
    item(0,1)->setText(QString::number(out2));
    item(0,2)->setText(QString::number(out3));

    updateSize();
}

void VelocityIndicator::clearAllText() {
    item(0,0)->setText("Unknown");
    item(0,1)->setText("Unknown");
    item(0,2)->setText("Unknown");

    updateSize();
}

//QSize VelocityIndicator::getRealSize(){
//    int width = verticalHeader()->width()+4;

//    for(int i=0;i<columnCount();++i){
//        width += columnWidth(i);
//    }

//    int height = horizontalHeader()->width()+4;

//    for(int j=0;j<rowCount();++j){
//        height += rowHeight(j);
//    }

//    return QSize(width,height);
//}

void VelocityIndicator::updateSize(){
    resizeColumnsToContents();
    resizeRowsToContents();
    setFixedSize(horizontalHeader()->length(),
                 verticalHeader()->length()+horizontalHeader()->height());
    update();
}
