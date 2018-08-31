#include "microfluidicsserver.h"
#include "configurationentity.h"

QVector<qreal> caluconspeed(int num, const QVector<double>&length, int i1, int i2, int o1, int o2, int o3);

void MicroFluidicsServer::queryVelocity(const QVector<qreal> &design)
{
    Q_ASSERT(design.size() == edgeNumber);
    auto retval = caluconspeed(size,design,input1pos,input2pos,output1pos,output2pos,output3pos);

    emit demandIndicatorVelocityChange(retval.at(edgeNumber-3),retval.at(edgeNumber-2),retval.at(edgeNumber-1));
    emit demandColorChange(retval);
}

int MicroFluidicsServer::queryNearItemsIndex(int baseindex, Direction direction) {
    Q_ASSERT(baseindex>=0);

    switch (direction) {
        case LEFT:
            Q_ASSERT(baseindex<size*size-size || (baseindex > edgeNumber-6 && baseindex < edgeNumber));
            if(baseindex<size-1)
                return -1;
            else if(baseindex == edgeNumber-5){
                if(input1pos<input2pos)
                    return -1;
                else
                    return baseindex+1;
            }
            else if(baseindex == edgeNumber-4){
                if(input1pos<input2pos)
                    return baseindex-1;
                else
                    return -1;
            }
            else if(baseindex == edgeNumber-3){
                int index1 = getOutputIndex(output1pos);
                if( index1 == 0 )
                    return -1;
                else
                    return outputindex[index1-1];
            }
            else if(baseindex == edgeNumber-2){
                int index2 = getOutputIndex(output2pos);
                if( index2 == 0 )
                    return -1;
                else
                    return outputindex[index2-1];
            }
            else if(baseindex == edgeNumber-1){
                int index3 = getOutputIndex(output3pos);
                if( index3 == 0 )
                    return -1;
                else
                    return outputindex[index3-1];
            }
            else
                return baseindex-size+1;
            break;
        case RIGHT:
            Q_ASSERT(baseindex<size*size-size || (baseindex > edgeNumber-6 && baseindex < edgeNumber));
            if(baseindex<(size-1)*(size-1))
                return baseindex+size-1;
            else if(baseindex == edgeNumber-5){
                if(input1pos<input2pos)
                    return baseindex+1;
                else
                    return -1;
            }
            else if(baseindex == edgeNumber-4){
                if(input1pos<input2pos)
                    return -1;
                else
                    return baseindex-1;
            }
            else if(baseindex == edgeNumber-3){
                int index1 = getOutputIndex(output1pos);
                if( index1 == 3 )
                    return -1;
                else
                    return outputindex[index1+1];
            }
            else if(baseindex == edgeNumber-2){
                int index2 = getOutputIndex(output2pos);
                if( index2 == 3 )
                    return -1;
                else
                    return outputindex[index2+1];
            }
            else if(baseindex == edgeNumber-1){
                int index3 = getOutputIndex(output3pos);
                if( index3 == 3 )
                    return -1;
                else
                    return outputindex[index3+1];
            }
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

int MicroFluidicsServer::getOutputIndex(int pos){
    for (int i=0;i<3;++i){
        if(outputindex[i] == pos){
            return i;
        }
    }
    Q_UNREACHABLE();
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

    inputindex.at(0) = input1pos;
    inputindex.at(1) = input2pos;
    outputindex.at(0) = output1pos;
    outputindex.at(1) = output2pos;
    outputindex.at(2) = output3pos;

    std::sort(inputindex.begin(),inputindex.end());
    std::sort(outputindex.begin(),outputindex.end());
}
