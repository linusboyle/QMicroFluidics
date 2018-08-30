#include "pipescene.h"
#include "configurationentity.h"
#include "pipe.h"
#include "microfluidicsserver.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QInputDialog>
#include <QApplication>

#ifdef QT_DEBUG
#include <QDebug>
#endif

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
            Pipe* m_pipe = new Pipe(id,baseX+PIPE_WIDTH*i+PIPE_LENGTH*i,
                                    baseY+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,
                                    PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL);
            addItem(m_pipe);
            items.insert(id,m_pipe);
            id++;
            connect(m_pipe,&Pipe::requestWidthChange,this,&PipeScene::onPipeRequsetResetWidth);
        }
    }

    for(int j=0;j<size-1;++j) {//each row
        for(int i=0;i<size;++i) { //rows
            Pipe* m_pipe = new Pipe(id,baseX+PIPE_WIDTH*(j+1)+PIPE_LENGTH*j,
                                    baseY+PIPE_WIDTH*i+PIPE_LENGTH*i,
                                    PIPE_LENGTH,PIPE_WIDTH,Pipe::HORIZONTAL);
            addItem(m_pipe);
            items.insert(id,m_pipe);
            id++;
            connect(m_pipe,&Pipe::requestWidthChange,this,&PipeScene::onPipeRequsetResetWidth);
        }
    }

    int indexIN1 = entity->getInput1Pos();
    Pipe* input1_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexIN1+PIPE_LENGTH*indexIN1,baseY-PIPE_LENGTH,
                                 PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL,Pipe::PIPE_INPUT);
    addItem(input1_pipe);
    items.insert(id,input1_pipe);
    id++;

    int indexIN2 = entity->getInput2Pos();
    Pipe* input2_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexIN2+PIPE_LENGTH*indexIN2,baseY-PIPE_LENGTH,
                                 PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL,Pipe::PIPE_INPUT);
    addItem(input2_pipe);
    items.insert(id,input2_pipe);
    id++;

    int indexOUT1 = entity->getOutput1Pos();
    Pipe* output1_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT1+PIPE_LENGTH*indexOUT1,
                                  baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,
                                  PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL,Pipe::PIPE_OUTPUT);
    addItem(output1_pipe);
    items.insert(id,output1_pipe);
    id++;

    int indexOUT2 = entity->getOutput2Pos();
    Pipe* output2_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT2+PIPE_LENGTH*indexOUT2,
                                  baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,
                                  PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL,Pipe::PIPE_OUTPUT);
    addItem(output2_pipe);
    items.insert(id,output2_pipe);
    id++;

    int indexOUT3 = entity->getOutput3Pos();
    Pipe* output3_pipe = new Pipe(id,baseX+PIPE_WIDTH*indexOUT3+PIPE_LENGTH*indexOUT3,
                                  baseY+PIPE_LENGTH*(size-1)+PIPE_WIDTH*size,
                                  PIPE_WIDTH,PIPE_LENGTH,Pipe::VERTICAL,Pipe::PIPE_OUTPUT);
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

void PipeScene::onPipeRequsetResetWidth(qreal id)
{
    Pipe* sender = qgraphicsitem_cast<Pipe*>(items.value(id));
    QRectF boundingrect = sender->boundingRect();

    /*
     * get the new width with dialog
     */

    bool ok;
    double basevalue=0;

    if(sender->getOrientation() == Pipe::VERTICAL)
        basevalue = boundingrect.width()/PIPE_WIDTH * PIPE_REAL_WIDTH;
    else if(sender->getOrientation() == Pipe::HORIZONTAL)
        basevalue = boundingrect.height()/PIPE_WIDTH * PIPE_REAL_WIDTH;

    qreal newWidth = QInputDialog::getDouble(qApp->activeWindow(),
                                             QObject::tr("Change Width"),
                                             QObject::tr("Input New Width:"),
                                             basevalue,0,2147483647,1,
                                             &ok,Qt::Dialog|Qt::FramelessWindowHint);

    if(ok){
        //transform back to inner coordinate;
        newWidth = newWidth / PIPE_REAL_WIDTH * PIPE_WIDTH;

        if(sender->getOrientation() == Pipe::VERTICAL){
            qreal newleftx = boundingrect.x()-(newWidth-boundingrect.width())/2;
            qreal newrightx = boundingrect.x()+(newWidth+boundingrect.width())/2;
            int leftid = MicroFluidicsServer::instance()->queryNearItemsIndex(id,MicroFluidicsServer::LEFT);
            int rightid = MicroFluidicsServer::instance()->queryNearItemsIndex(id,MicroFluidicsServer::RIGHT);

            if(leftid>=0){
                qreal leftline = items.value(leftid)->boundingRect().right();
                if(newleftx-leftline < PIPE_WIDTH){
                    emit requestPopUpWarningBox();
                    return;
                }
            }

            if(rightid>=0){
                qreal rightline = items.value(rightid)->boundingRect().left();
                if(rightline-newrightx < PIPE_WIDTH){
                    emit requestPopUpWarningBox();
                    return;
                }
            }
        } else if (sender->getOrientation() == Pipe::HORIZONTAL){
            qreal newupy = boundingrect.y()-(newWidth-boundingrect.height())/2;
            qreal newdowny = boundingrect.y()+(newWidth+boundingrect.height())/2;
            int upid = MicroFluidicsServer::instance()->queryNearItemsIndex(id,MicroFluidicsServer::UP);
            int downid = MicroFluidicsServer::instance()->queryNearItemsIndex(id,MicroFluidicsServer::DOWN);

            if(upid>=0){
                qreal upline = items.value(upid)->boundingRect().bottom();
                if(newupy-upline < PIPE_WIDTH){
                    emit requestPopUpWarningBox();
                    return;
                }
            }

            if(downid>=0){
                qreal downline = items.value(downid)->boundingRect().top();
                if(downline-newdowny < PIPE_WIDTH){
                    emit requestPopUpWarningBox();
                    return;
                }
            }
        }
        //if reach here,it's legal
        sender->resetWidth(newWidth);
    }
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
    QAction* clearaction = contextmenu->addAction(QIcon::fromTheme("edit-clear-all"),tr("&Clear"));
    QAction* restoreaction = contextmenu->addAction(QIcon::fromTheme("view-restore"),tr("&Restore"));
    connect(clearaction,&QAction::triggered,this,&PipeScene::contextDemandClear);
    connect(restoreaction,&QAction::triggered,this,&PipeScene::restore);
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

void PipeScene::setView(EditorView *_view){
    view = _view;
}
