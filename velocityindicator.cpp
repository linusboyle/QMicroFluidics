/**
 * velocityindicator.cpp
 * Copyright (c) 2018 Linus Boyle <linusboyle@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "velocityindicator.h"
#include <QHeaderView>

//#ifdef QT_DEBUG
//#include <QDebug>
//#endif

VelocityIndicator::VelocityIndicator(QWidget *parent)
    :QTableWidget(parent)
{
    setRowCount(1);
    setColumnCount(7);
    setHorizontalHeaderLabels(QStringList()<<tr("Output1")<<tr("Output2")<<tr("Output3")
                              <<tr("Input1")<<tr("Input2")<<tr("Pipe Length")<<tr("Initial Pipe Width"));

    QTableWidgetItem* output1 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output2 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* output3 = new QTableWidgetItem(tr("Unknown"));
    QTableWidgetItem* input1 = new QTableWidgetItem(tr("200"));
    QTableWidgetItem* input2 = new QTableWidgetItem(tr("200"));
    QTableWidgetItem* pipelength = new QTableWidgetItem(tr("1600"));
    QTableWidgetItem* pipewidth = new QTableWidgetItem(tr("200"));

    output1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    output2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    output3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    input1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    input2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    pipelength->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    pipewidth->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    setItem(0,0,output1);
    setItem(0,1,output2);
    setItem(0,2,output3);
    setItem(0,3,input1);
    setItem(0,4,input2);
    setItem(0,5,pipelength);
    setItem(0,6,pipewidth);

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
