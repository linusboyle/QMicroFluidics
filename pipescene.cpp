#include "pipescene.h"
#include "configurationentity.h"
#include "pipe.h"
#include "microfluidicsserver.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#ifdef QT_DEBUG
#include <QDebug>
#endif

#define PIPE_LENGTH 80
#define PIPE_WIDTH 10

PipeScene::PipeScene(QObject *parent):
    QGraphicsScene(parent),entity(nullptr)
{
    initContextMenu();
}

PipeScene::~PipeScene(){
    if(contextmenu){
        contextmenu->deleteLater();
    }
    if(entity)
        delete entity;
}

void PipeScene::reset(ConfigurationEntity *_entity){
    if (entity != _entity) {
        if (entity) {
            delete entity;
        }
        //deep copy
        entity = new ConfigurationEntity(*_entity);
    }

    this->items.clear();
    this->clear();
    int size = entity->getSize();

    int baseX=0;
    int baseY=0;

    int id = 0;
    //columns
    for(int i=0;i<size;++i) {
        for(int j=0;j<size-1;++j) {
            Pipe* m_pipe = new Pipe(id,baseX+PIPE_WIDTH*i+PIPE_LENGTH*i,baseY+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,PIPE_WIDTH,PIPE_LENGTH);
            addItem(m_pipe);
            items.insert(id,m_pipe);
            id++;
        }
    }

    for(int j=0;j<size-1;++j) {//each row
        for(int i=0;i<size;++i) { //rows
            Pipe* m_pipe = new Pipe(id,baseX+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,baseY+PIPE_WIDTH*i+PIPE_LENGTH*i,PIPE_LENGTH,PIPE_WIDTH);
            addItem(m_pipe);
            items.insert(id,m_pipe);
            id++;
        }
    }

    int indexIN1 = entity->getInput1Pos();
    Pipe* input1_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexIN1+PIPE_LENGTH*indexIN1,baseY-PIPE_LENGTH,PIPE_WIDTH,PIPE_LENGTH,Pipe::PIPE_INPUT);
    addItem(input1_pipe);
    items.insert(id,input1_pipe);
    id++;

    int indexIN2 = entity->getInput2Pos();
    Pipe* input2_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexIN2+PIPE_LENGTH*indexIN2,baseY-PIPE_LENGTH,PIPE_WIDTH,PIPE_LENGTH,Pipe::PIPE_INPUT);
    addItem(input2_pipe);
    items.insert(id,input2_pipe);
    id++;

    int indexOUT1 = entity->getOutput1Pos();
    Pipe* output1_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT1+PIPE_LENGTH*indexOUT1,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,Pipe::PIPE_OUTPUT);
    addItem(output1_pipe);
    items.insert(id,output1_pipe);
    id++;

    int indexOUT2 = entity->getOutput2Pos();
    Pipe* output2_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT2+PIPE_LENGTH*indexOUT2,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,Pipe::PIPE_OUTPUT);
    addItem(output2_pipe);
    items.insert(id,output2_pipe);
    id++;

    int indexOUT3 = entity->getOutput3Pos();
    Pipe* output3_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT3+PIPE_LENGTH*indexOUT3,baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,PIPE_WIDTH,PIPE_LENGTH,Pipe::PIPE_OUTPUT);
    addItem(output3_pipe);
    items.insert(id,output3_pipe);
    id++;

#ifdef QT_DEBUG
    qDebug()<<"total pipes:" <<id;
#endif

    Q_ASSERT(id == 2*size*size-2*size+5);
    Q_ASSERT(items.size() == 2*size*size-2*size+5);

    emit needCalc(QVector<qreal>(items.size(),PIPE_LENGTH));
}

void PipeScene::restore(){
    if(entity)
        this->reset(entity);
}

void PipeScene::deleteSelectionItems() {
    QList<QGraphicsItem*> selecteditems = selectedItems();

    foreach (QGraphicsItem* item, selecteditems) {
        item->setVisible(false);
    }

    if(selecteditems.size()>0)
        emit needCalc(getStatusMatrix());
}

void PipeScene::initContextMenu()
{
    contextmenu = new QMenu();
    QAction* deleteaction = contextmenu->addAction(QIcon::fromTheme("edit-delete"),tr("&Delete Selected"));
    connect(deleteaction,&QAction::triggered,this,&PipeScene::deleteSelectionItems);
}

QVector<qreal> PipeScene::getStatusMatrix() const {
    QVector<qreal> retval;

    for(int i=0;i<items.size();++i){
        retval.push_back(items.value(i)->isVisible() ? PIPE_LENGTH:0);
    }

    return retval;
}

void PipeScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(this->hasFocus()){
        contextmenu->exec(event->screenPos());
    }
}
