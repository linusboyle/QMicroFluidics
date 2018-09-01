/**
 * microfluidicsserver.h
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
#ifndef MICROFLUIDICSSERVER_H
#define MICROFLUIDICSSERVER_H

#include <QVector>
#include <QObject>
class ConfigurationEntity;

class MicroFluidicsServer:public QObject
{
    Q_OBJECT

signals:
    void demandIndicatorVelocityChange(qreal,qreal,qreal);
    void demandColorChange(QVector<qreal>);
public:
    inline static MicroFluidicsServer* instance() {
        static MicroFluidicsServer* theinstance = new MicroFluidicsServer();

        return theinstance;
    }

    enum Direction {
        LEFT = 0,
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
    };

    int queryNearItemsIndex(int baseindex,Direction direction);
    void setConfiguration(ConfigurationEntity* entity);

public slots:
    void queryVelocity(const QVector<qreal>& design);

private:

    inline MicroFluidicsServer(){}
    inline ~MicroFluidicsServer(){}
    MicroFluidicsServer(const MicroFluidicsServer&) = delete;
    MicroFluidicsServer& operator= (const MicroFluidicsServer&) = delete;

    int size;
    int nodeNumber;
    int edgeNumber;

    int input1pos;
    int input2pos;
    int output1pos;
    int output2pos;
    int output3pos;

    std::array<int,2> inputindex;
    std::array<int,3> outputindex;

    int getOutputIndex(int);
};

#endif // MICROFLUIDICSSERVER_H
