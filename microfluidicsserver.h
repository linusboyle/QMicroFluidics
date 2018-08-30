#ifndef MICROFLUIDICSSERVER_H
#define MICROFLUIDICSSERVER_H

#include <QVector>
#include <QObject>
class ConfigurationEntity;

class MicroFluidicsServer:public QObject
{
    Q_OBJECT

signals:
    void velocityChanged(qreal,qreal,qreal);

public:
    inline static MicroFluidicsServer* instance() {
        static MicroFluidicsServer* theinstance = new MicroFluidicsServer();

        return theinstance;
    }

    void setConfiguration(ConfigurationEntity* entity);

public slots:
    void queryVelocity(const QVector<qreal>& design);

private:
//    typedef struct {
//        QVector<int> relatedEdges;
//    } Node;
//    typedef struct{
//        qreal velocity;
//        qreal length;
//        int sourceNodeIndex;
//        int destNodeIndex;
//    } Edge;
//    QVector<Node> m_nodes;
//    QVector<Edge> m_edges;

    inline MicroFluidicsServer(){
//        equaltion = nullptr;
    }
    inline ~MicroFluidicsServer(){}
    MicroFluidicsServer(const MicroFluidicsServer&) = delete;
    MicroFluidicsServer& operator= (const MicroFluidicsServer&) = delete;

    int size;
//    int nodeNumber;
//    int edgeNumber;

    int input1pos;
    int input2pos;
    int output1pos;
    int output2pos;
    int output3pos;

//    QVector<QVector<qreal>>* equation;

//    void initEquation();
//    void calcAnswer();

//    int getEdgeIndex(int nodeX, int nodeY, int direction);
//    bool checkeEdgeValid(int nodex,int nodey,int direction);

//    void findLine(int x,int y,int endEdge);
//    void recursionLine(int nodex,int nodey,int direction,QVector<qreal>& retval,int endEdge);
//    bool DFS(int nodex,int nodey,QVector<qreal>& retval,int endEdge);
//    void getVoltageDelta(int inputIndex);
};

#endif // MICROFLUIDICSSERVER_H
