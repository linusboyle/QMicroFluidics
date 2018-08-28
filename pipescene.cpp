#include "pipescene.h"
#include "configurationentity.h"

#define PIPE_LENGTH 50
#define PIPE_WIDTH 10

PipeScene::PipeScene(QObject *parent):
    QGraphicsScene(parent),entity(nullptr)
{

}

void PipeScene::reset(ConfigurationEntity *_entity){
    if (entity != _entity) {
        if (entity) {
            delete entity;
        }
        entity = new ConfigurationEntity(*_entity);
    }

    this->clear();
    int size = entity->getSize();

    int baseX=0;
    int baseY=0;
    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    //draw the complete pipes first
    for(int i=0;i<size;++i) { //rows
        for(int j=0;j<size-1;++j) {//each row
            //TOOD
            //replace using custom item
            addRect(baseX+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,baseY+PIPE_WIDTH*i+PIPE_LENGTH*i,PIPE_LENGTH,PIPE_WIDTH,pen,brush);
        }
    }

    //likewise for columns
    for(int i=0;i<size;++i) {
        for(int j=0;j<size-1;++j) {
            addRect(baseX+PIPE_WIDTH*i+PIPE_LENGTH*i,baseY+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,PIPE_WIDTH,PIPE_LENGTH,pen,brush);
        }
    }

    int indexIN1 = entity->getInput1Pos();
    addRect(baseX+PIPE_WIDTH*indexIN1+PIPE_LENGTH*indexIN1,baseY-PIPE_LENGTH,PIPE_WIDTH,PIPE_LENGTH,pen,brush);
    int indexIN2 = entity->getInput2Pos();
    addRect(baseX+PIPE_WIDTH*indexIN2+PIPE_LENGTH*indexIN2,baseY-PIPE_LENGTH,PIPE_WIDTH,PIPE_LENGTH,pen,brush);

    int indexOUT1 = entity->getOutput1Pos();
    addRect(baseX+PIPE_WIDTH*indexOUT1+PIPE_LENGTH*indexOUT1,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,pen,brush);
    int indexOUT2 = entity->getOutput2Pos();
    addRect(baseX+PIPE_WIDTH*indexOUT2+PIPE_LENGTH*indexOUT2,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,pen,brush);
    int indexOUT3 = entity->getOutput3Pos();
    addRect(baseX+PIPE_WIDTH*indexOUT3+PIPE_LENGTH*indexOUT3,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,pen,brush);
}

void PipeScene::restore(){
    this->reset(entity);
}
