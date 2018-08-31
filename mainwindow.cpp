#include "mainwindow.h"
#include "newdesigndialog.h"
#include "configurationentity.h"
#include "pipescene.h"
#include "editorwidget.h"
#include "editorview.h"
#include "microfluidicsserver.h"
#include "velocityindicator.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QScreen>
#include <QDesktopServices>
#include <QUrl>
#include <QTemporaryFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QTranslator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initTranslations();

    initUI();

    scene = new PipeScene(this);
    dialog = new NewDesignDialog(this);
    editor = new EditorWidget(this);

    editor->getView()->setScene(scene);
    scene->setView(editor->getView());

    connect(editor,&EditorWidget::requestDeletion,scene,&PipeScene::deleteSelectionItems);
    connect(scene,&PipeScene::contextDemandClear,this,&MainWindow::clearScene);
    connect(scene,&PipeScene::requestPopUpWarningBox,this,&MainWindow::popupWarning);
    connect(MicroFluidicsServer::instance(),&MicroFluidicsServer::demandIndicatorVelocityChange,editor->getIndicator(),&VelocityIndicator::onVelocityChanged);

    setCentralWidget(editor);

    setMinimumSize(600,600);
    setWindowTitle(tr("QMicroFluidics"));

    initGeometry();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI(){

    //menus
    QMenu* filemenu = menuBar()->addMenu(tr("&File"));
    QMenu* editmenu = menuBar()->addMenu(tr("&Edit"));
    QMenu* canvasmenu = menuBar()->addMenu(tr("&Canvas"));
    QMenu* viewmenu = menuBar()->addMenu(tr("&View"));
    QMenu* aboutmenu = menuBar()->addMenu(tr("&About"));

    //actions
    QAction* quitaction = filemenu->addAction(QIcon::fromTheme("application-exit",QIcon(":/icons/exit.svg")),tr("&Quit"));
    QAction* printaction = filemenu->addAction(QIcon::fromTheme("fileprint"),tr("&Print"));
    QAction* saveaction = filemenu->addAction(QIcon::fromTheme("filesave"),tr("&Save To Image"));

    QAction* newaction = canvasmenu->addAction(QIcon::fromTheme("filenew"),tr("&New"));
    QAction* clearaction = canvasmenu->addAction(QIcon::fromTheme("edit-clear-all"),tr("&Clear"));
    QAction* restoreaction = canvasmenu->addAction(QIcon::fromTheme("view-restore"),tr("&Restore"));

    //these five have already been on the central widget and need no icon
    QAction* zoominaction = viewmenu->addAction(tr("Zoom&In"));
    QAction* zoomoutaction = viewmenu->addAction(tr("Zoom&Out"));
    QAction* rotateleftaction = viewmenu->addAction(tr("Rotate&Left"));
    QAction* rotaterightaction = viewmenu->addAction(tr("Rotate&Right"));
    QAction* resetaction = viewmenu->addAction(tr("R&eset"));

    QAction* deleteaction = editmenu->addAction(QIcon::fromTheme("edit-delete"),tr("&Delete Selected"));
    QAction* aboutaction = aboutmenu->addAction(QIcon::fromTheme("help-about"),tr("&About"));
    QAction* gitaction = aboutmenu->addAction(QIcon::fromTheme("text-x-c++src"),tr("&Find Source Code"));
    QAction* helpaction = aboutmenu->addAction(QIcon::fromTheme("help"),tr("Help"));

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

    connect(aboutaction,&QAction::triggered,this,&MainWindow::showAboutMenu);
    connect(gitaction,&QAction::triggered,this,&MainWindow::openSourceCodePage);
    connect(helpaction,&QAction::triggered,this,&MainWindow::openPaper);
    connect(printaction,&QAction::triggered,this,&MainWindow::printDesign);
    connect(saveaction,&QAction::triggered,this,&MainWindow::saveToImage);

    //toolbar
    QToolBar* filetoolbar = new QToolBar(tr("File"));
    filetoolbar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea,filetoolbar);
    filetoolbar->addAction(quitaction);
    filetoolbar->addAction(printaction);
    filetoolbar->addAction(saveaction);

    QToolBar* canvastoolbar = new QToolBar(tr("Canvas"));
    canvastoolbar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea,canvastoolbar);
    canvastoolbar->addAction(newaction);
    canvastoolbar->addAction(clearaction);
    canvastoolbar->addAction(restoreaction);

    QToolBar* edittoolbar = new QToolBar(tr("Edit"));
    edittoolbar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea,edittoolbar);
    edittoolbar->addAction(deleteaction);

    QToolBar* abouttoolbar = new QToolBar(tr("About"));
    abouttoolbar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea,abouttoolbar);
    abouttoolbar->addAction(aboutaction);
    abouttoolbar->addAction(gitaction);
    abouttoolbar->addAction(helpaction);
}

void MainWindow::createNewDesign(){
    dialog->clearAll();
    if (dialog->exec() == QDialog::Accepted) {
        if (dialog->getEntity()->checkValidity()) {
            scene->reset(dialog->getEntity());
            editor->resetView();
            MicroFluidicsServer::instance()->setConfiguration(dialog->getEntity());
        } else {
            this->popupWarning();
        }
    }
}

void MainWindow::clearScene(){
    scene->clear();
    editor->getIndicator()->clearAllText();
}

void MainWindow::restoreScene()
{
    scene->restore();
}

void MainWindow::showAboutMenu()
{
    QMessageBox aboutbox(QMessageBox::Information,tr("QMicroFluidics Designer"),tr("<b>Author:Linus Boyle</b><br>"
                                                                                   "Algorithm based on <font color=red>Hailong Yao and Weiqing Ji</font>'s work<br>"
                                                                                   "Under GNU General Public License version 3<br>"
                                                                                   "You can find the source code on github<br>"));
    aboutbox.exec();
}

void MainWindow::popupWarning(){
    QMessageBox::warning(this,tr("Your Configuration is Invalid!"),
                         tr("NOTE:\n"
                            "1.size should be between %1 and %2\n"
                            "2.input and output pipe index must not be identical and "
                            "must be between 0 and size-1\n"
                            "3.the distance between two adjacent pipes must be greater "
                            "than %3").arg(PIPE_SIZE_MIN).arg(PIPE_SIZE_MAX).arg(PIPE_REAL_WIDTH));
}

void MainWindow::initGeometry(){
    QScreen* primaryscreen = QGuiApplication::primaryScreen();
    QRect rect = primaryscreen->geometry();
    setGeometry(QRect((rect.width()-this->width())/2,(rect.height()-this->height())/2,this->width(),this->height()));
}

void MainWindow::openSourceCodePage(){
    QDesktopServices::openUrl(QUrl("https://github.com/linusboyle/QMicroFluidics"));
}

void MainWindow::openPaper(){
    QFile paper(":/paper/paper.pdf");

    QTemporaryFile* tempfile = QTemporaryFile::createNativeFile(paper);

    QDesktopServices::openUrl(QUrl::fromLocalFile(tempfile->fileName()));
}

void MainWindow::printDesign(){
    QPrinter printer(QPrinter::HighResolution);

    if(QPrintDialog(&printer).exec() == QDialog::Accepted){
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);

        this->scene->render(&painter);
    }
}

void MainWindow::saveToImage(){
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isNull())
    {
        scene->clearSelection();
        QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        QPainter painter(&image);

        scene->render(&painter);

        image.save(fileName);
    }
}

void MainWindow::initTranslations(){
    QTranslator* translator = new QTranslator();

    if(translator->load(QString(":/translations/tr_")+QLocale::system().name()))
        qApp->installTranslator(translator);
    else {
        qDebug()<<"install translation failed!";
        translator->deleteLater();
    }
}
