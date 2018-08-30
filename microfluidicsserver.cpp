#include "microfluidicsserver.h"
#include "configurationentity.h"
#include <tuple>

#ifdef QT_DEBUG
#include <QDebug>
#endif

std::tuple<double,double,double> caluconspeed(int num, const QVector<double>&length, int i1, int i2, int o1, int o2, int o3);

//static QVector<bool> indicator;

void MicroFluidicsServer::queryVelocity(const QVector<qreal> &design)
{
    Q_ASSERT(design.size() == edgeNumber);
    auto retval = caluconspeed(size,design,input1pos,input2pos,output1pos,output2pos,output3pos);

    emit velocityChanged(std::get<0>(retval),std::get<1>(retval),std::get<2>(retval));
}

int MicroFluidicsServer::queryNearItemsIndex(int baseindex, Direction direction) {
    Q_ASSERT(baseindex>=0);

    switch (direction) {
    case LEFT:
        //only for vertical items
        Q_ASSERT(baseindex<size*size-size);
        //the most left column
        if(baseindex<size-1)
            return -1;
        else
            return baseindex-size+1;
        break;
    case RIGHT:
        Q_ASSERT(baseindex<size*size-size);
        if(baseindex<(size-1)*(size-1))
            return baseindex+size-1;
        else
            return -1;
        break;
    case UP:
        Q_ASSERT(baseindex>=size*size-size);
        if((baseindex-size*size+size) % size ==0)
            return -1;
        else
            return baseindex-1;
        break;
    case DOWN:
        Q_ASSERT(baseindex>=size*size-size);
        if((baseindex-size*size+1) % size == 0)
            return -1;
        else
            return baseindex+1;
        break;
    default:
        Q_UNREACHABLE();
        break;
    }
}

void MicroFluidicsServer::setConfiguration(ConfigurationEntity *entity){

    size = entity->getSize();
    nodeNumber = size*size;
    edgeNumber = 2*size*size-2*size+5;
    input1pos = entity->getInput1Pos();
    input2pos = entity->getInput2Pos();
    output1pos = entity->getOutput1Pos();
    output2pos = entity->getOutput2Pos();
    output3pos = entity->getOutput3Pos();

//    m_nodes.clear();
//    m_edges.clear();
//    indicator.clear();
//    indicator.fill(false,edgeNumber);

//    m_nodes.reserve(nodeNumber);
//    m_edges.reserve(edgeNumber);

//    if(equation){
//        delete equation;
//        equation = new QVector<QVector<qreal>>();
//        //the number of equations should be definite here...
//    }
}

//int MicroFluidicsServer::getEdgeIndex(int nodeX, int nodeY, int direction){
//    int retval = edgeNumber;
//    int nodeIndex = nodeX*size+nodeY;

//    switch (direction) {
//    case 0:
//        if(nodeY == 0){
//            if(m_edges.at(edgeNumber-5).destNodeIndex == nodeIndex){
//                retval = edgeNumber-5;
//            } else if(m_edges.at(edgeNumber-4).destNodeIndex == nodeIndex){
//                retval= edgeNumber-4;
//            } else {
//                retval = edgeNumber;
//            }
//        } else {
//            retval = nodeX*(size-1)+nodeY-1;
//        }
//        break;
//    case 1:
//        if(nodeX == size-1){
//            retval = edgeNumber;
//        } else {
//            retval = size*size-size+nodeX*size+nodeY;
//        }
//        break;
//    case 2:
//        if(nodeY == size-1){
//            if(m_edges.at(edgeNumber-3).sourceNodeIndex == nodeIndex){
//                retval = edgeNumber-3;
//            } else if (m_edges.at(edgeNumber-2).sourceNodeIndex == nodeIndex){
//                retval = edgeNumber-2;
//            } else if (m_edges.at(edgeNumber-1).sourceNodeIndex == nodeIndex){
//                retval = edgeNumber-1;
//            } else {
//                retval = edgeNumber;
//            }
//        } else {
//            retval = nodeX*(size-1)+nodeY;
//        }
//        break;
//    case 3:
//        if(nodeX == 0){
//            retval = edgeNumber;
//        } else {
//            retval = size*size-size+size*(nodeX-1)+nodeY;
//        }
//        break;
//    default:
//        Q_UNREACHABLE();
//        break;
//    }

//    return retval;
//}

//bool MicroFluidicsServer::checkeEdgeValid(int nodex, int nodey, int direction){
//    int edgeIndex = getEdgeIndex(nodex,nodey,direction);

//    if (edgeIndex >= edgeNumber)
//        return false;

//    return m_edges.at(edgeIndex).length>0;
//}

//void MicroFluidicsServer::recursionLine(int nodex, int nodey, int direction, QVector<qreal> &retval, int endEdge){
//    int edgeIndex = getEdgeIndex(nodex,nodey,direction);
//    int nodeIndex = nodex*size+nodey;
//    if(edgeIndex > edgeNumber-6)
//        return;

//    if(m_edges.at(edgeIndex).sourceNodeIndex == nodeIndex){
//        retval.at(edgeIndex) = m_edges.at(edgeIndex).length;
//    } else {
//        retval.at(edgeIndex) = -m_edges.at(edgeIndex).length;
//    }

//    if(edgeIndex == endEdge){
//        equation->push_back(retval);
//        return;
//    }

//    switch (direction) {
//        case 0:
//            nodey--;
//            break;
//        case 1:
//            nodex++;
//            break;
//        case 2:
//            nodey++;
//            break;
//        case 3:
//            nodex--;
//            break;
//        default:
//            Q_UNREACHABLE();
//            break;
//    }

//    for(int i=0;i<4;++i){
//        int newDirection = direction+1-i;
//        newDirection = (newDirection+4)%4;

//        if(checkeEdgeValid(nodex,nodey,newDirection)){
//            recursionLine(nodex,nodey,newDirection,retval,endEdge);
//            break;
//        }
//    }
//}

//bool MicroFluidicsServer::DFS(int nodex, int nodey, QVector<qreal> &retval, int endEdge){
//    for(int i=0;i<4;i++){
//        int newx = nodex ,newy = nodey;
//        int edgeIndex = getEdgeIndex(nodex,nodey,i);
//        if(edgeIndex >= edgeNumber)
//            continue;
//        if(indicator.at(edgeIndex))
//            continue;

//        int nodeIndex = nodex*size+nodeY;
//        if(m_edges.at(edgeIndex) == nodeIndex){
//            retval.at(edgeIndex) = m_edges.at(edgeIndex).length;
//        } else {
//            retval.at(edgeIndex) = -m_edges.at(edgeIndex).length;
//        }

//        if(edgeIndex == endEdge){
//            return true;
//        }

//        if(edgeIndex>edgeNumber-6){
//            retval.at(edgeIndex) = 0;
//            continue;
//        }

//        switch (direction) {
//            case 0:
//                newy = nodey--;
//                break;
//            case 1:
//                newx = nodex++;
//                break;
//            case 2:
//                newy = nodey++;
//                break;
//            case 3:
//                newx = nodex--;
//                break;
//            default:
//                Q_UNREACHABLE();
//                break;
//        }
//        if(DFS(newx,newy,retval,endEdge)){
//            return true;
//        }

//        retval.at(edgeIndex) = 0;
//    }

//    return false;
//}

//void MicroFluidicsServer::findLine(int x, int y, int endEdge){
//    QVector<qreal> retval(edgeNumber+1,0);
//    recursionLine(x,y,1,retval,endEdge);
//}

//void MicroFluidicsServer::getVoltageDelta(int inputIndex){
//    QVector<qreal> tmp(edgeNumber+1,0);
//    indicator.fill(false,edgeNumber);
//    DFS(m_edges.at(inputIndex).destNodeIndex/size,0,tmp,edgeNumber-1);
//    QVector<qreal> tmp2(edgeNumber+1,0);
//    indicator.fill(false,edgeNumber);
//    DFS(m_edges.at(inputIndex).destNodeIndex/size,0,tmp2,edgeNumber-1);
//    QVector<qreal> tmp3(edgeNumber+1,0);
//    indicator.fill(false,edgeNumber);
//    DFS(m_edges.at(inputIndex).destNodeIndex/size,0,tmp3,edgeNumber-1);

//    QVector<qreal> retval(edgeNumber+1,0);
//    for(int i=0;i<edgeNumber+1;++i){
//        retval.at(i) = tmp.at(i)-tmp2.at(i);
//    }
//    equation->push_back(retval);

//    for(int i=0;i<edgeNumber+1;++i){
//        retval.at(i) = tmp3.at(i)-tmp2.at(i);
//    }
//    equation->push_back(retval);

//}

//void MicroFluidicsServer::initEquation(){
//    for(int i=0;i<edgeNumber;++i){
//        if(m_edges.at(i).length == 0){
//            QVector<qreal> tmp(edgeNumber+1,0);
//            tmp.at(i) = 1;
//            equation->push_back(tmp);
//        }
//    }
//    for (int i=0; i<nodeNumber-2; i++)
//    {
//        int number = 0;
//        QVector<qreal> tmp(edgeNumber+1,0);
//        for (int j=0; j<m_nodes.at(i).relatedEdges.size(); j++)
//            if (m_edges.at(m_nodes.at(i).relatedEdges.at(j)).length !=0)
//            {
//                number++;
//                if (m_edges.at(m_nodes.at(i).relatedEdges.at(j)).sourceNodeIndex == i)
//                    tmp.at(m_nodes.at(i).relatedEdges.at(j)) = 1;
//                else
//                    tmp.at(m_nodes.at(i).relatedEdges.at(j)) = -1;
//            }
//        tmp.at(edgeNumber) = 0;
//        if (number>0)
//            addrect(tmp);
//    }
//    for(int i=0;i<size-1;++i){
//        for(int j=0;j<n-1;++j){
//            int edge1 = i*(size-1)+j;
//            int edge2 = size*size-size+i*size+j;

//            if(m_edges.at(edge1).length != 0
//                    && m_edges.at(edge2).length !=0)
//                findLine(i,j,edge1);
//        }
//    }

//    getVoltageDelta(edgeNumber-4);

//    QVector<qreal> tmp(edgeNumber,0);
//    tmp.at(edgeNumber-5) = 1;
//    tmp.at(edgeNumber) = 200;
//    equation->push_back(tmp);

//    QVector<qreal> tmp2(edgeNumber,0);
//    tmp2.at(edgeNumber-4) = 1;
//    tmp2.at(edgeNumber) = 200;
//    equation->push_back(tmp2);
//}

//void MicroFluidicsServer::calcAnswer(){
//    int n = equation->size();

//    for(int i=0;i<n;++i){
//        for(int j=0;j<edgeNumber+1;++j){
//            if(qFuzzyIsNull(qAbs(equation->at(i).at(j)))){
//                equation->at(i).at(j)= 0;
//            }
//        }
//    }
//}
