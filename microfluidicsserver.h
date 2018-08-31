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
