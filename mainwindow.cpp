#include "mainwindow.h"
#include "newdesigndialog.h"
#include "configurationentity.h"
#include "pipescene.h"
#include "editorwidget.h"
#include "editorview.h"
#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>

#ifdef QT_DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initMenu();

    scene = new PipeScene(this);
    dialog = new NewDesignDialog(this);
    editor = new EditorWidget(this);
    editor->getView()->setScene(scene);
    connect(editor,&EditorWidget::requestDeletion,scene,&PipeScene::deleteSelectionItems);

    setCentralWidget(editor);

    setMinimumSize(500,500);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initMenu(){

    //menus
    QMenu* filemenu = menuBar()->addMenu(tr("&File"));
    QMenu* editmenu = menuBar()->addMenu(tr("&Edit"));
    QMenu* canvasmenu = menuBar()->addMenu(tr("&Canvas"));
    QMenu* viewmenu = menuBar()->addMenu(tr("&View"));

    //actions
    QAction* quitaction = filemenu->addAction(tr("&Quit"));

    QAction* newaction = canvasmenu->addAction(tr("&New"));
    QAction* clearaction = canvasmenu->addAction(tr("&Clear"));
    QAction* restoreaction = canvasmenu->addAction(tr("&Restore"));

    QAction* zoominaction = viewmenu->addAction(tr("Zoom&In"));
    QAction* zoomoutaction = viewmenu->addAction(tr("Zoom&Out"));
    QAction* rotateleftaction = viewmenu->addAction(tr("Rotate&Left"));
    QAction* rotaterightaction = viewmenu->addAction(tr("Rotate&Right"));
    QAction* resetaction = viewmenu->addAction(tr("R&eset"));

    QAction* deleteaction = editmenu->addAction(tr("&Delete Selected"));

    connect(newaction,&QAction::triggered,this,&MainWindow::createNewDesign);
    connect(clearaction,&QAction::triggered,this,&MainWindow::clearScene);
    connect(restoreaction,&QAction::triggered,this,&MainWindow::restoreScene);
    connect(quitaction,&QAction::triggered,qApp,&QApplication::quit);

    connect(zoominaction,&QAction::triggered,[this](){
        this->editor->zoomIn();
    });
    connect(zoomoutaction,&QAction::triggered,[this](){
        this->editor->zoomOut();
    });
    connect(rotateleftaction,&QAction::triggered,[this](){
        this->editor->rotateLeft();
    });
    connect(rotaterightaction,&QAction::triggered,[this](){
        this->editor->rotateRight();
    });
    connect(resetaction,&QAction::triggered,[this](){
        this->editor->resetView();
    });
    connect(deleteaction,&QAction::triggered,[this](){
        this->scene->deleteSelectionItems();
    });

    //dont know why this leads to SIGV
    //connect(clearaction,&QAction::triggered,scene,&QGraphicsScene::clear);
}

void MainWindow::createNewDesign(){
    dialog->clearAll();
    if (dialog->exec() == QDialog::Accepted) {
        if (dialog->getEntity()->checkValidity()) {
            scene->reset(dialog->getEntity());
            editor->resetView();
        } else {
            QMessageBox::warning(this,tr("Your Configuration is Invalid!"),tr("NOTE:\n"
                                                                              "1.size should be between %1 and %2\n"
                                                                              "2.input and output pipe index must not be identical and "
                                                                              "must be between 0 and SIZE\n").arg(PIPE_SIZE_MIN).arg(PIPE_SIZE_MAX));
        }
    }
#ifdef QT_DEBUG
    else {
        qDebug()<<"rejected";
    }
#endif
}

void MainWindow::clearScene(){
    scene->clear();
}

void MainWindow::restoreScene()
{
    scene->restore();
}
