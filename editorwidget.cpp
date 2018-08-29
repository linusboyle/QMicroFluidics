#include "editorwidget.h"
#include "editorview.h"
#include <qmath.h>
#include <QSlider>
#include <QToolButton>
#include <QStyle>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollBar>
#include <QKeyEvent>

#ifdef QT_DEBUG
#include <QDebug>
#endif

EditorWidget::EditorWidget(QWidget *parent)
    :QFrame(parent)
{
    view = new EditorView(this);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconsize(size,size);

    zoomInButton = new QToolButton(this);
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(33);
    zoomInButton->setAutoRepeatDelay(0);
    zoomInButton->setIcon(QPixmap(":/icons/zoomin.png"));
    zoomInButton->setIconSize(iconsize);

    zoomOutButton = new QToolButton(this);
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(33);
    zoomOutButton->setAutoRepeatDelay(0);
    zoomOutButton->setIcon(QPixmap(":/icons/zoomout.png"));
    zoomOutButton->setIconSize(iconsize);

    zoomSlider = new QSlider(this);
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomInButton);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomOutButton);

    rotateLeftButton = new QToolButton(this);
    rotateLeftButton->setIcon(QPixmap(":/icons/rotateleft.png"));
    rotateLeftButton->setIconSize(iconsize);

    rotateRightButton = new QToolButton(this);
    rotateRightButton->setIcon(QPixmap(":/icons/rotateright.png"));
    rotateRightButton->setIconSize(iconsize);

    rotateSlider = new QSlider(this);
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);

    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftButton);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightButton);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(view, 0, 0);
    topLayout->addLayout(rotateSliderLayout, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 0, 1);
    topLayout->addWidget(resetButton, 1, 1);

    setLayout(topLayout);

    //button
    connect(rotateLeftButton, &QToolButton::clicked, this, &EditorWidget::rotateLeft);
    connect(rotateRightButton, &QToolButton::clicked, this, &EditorWidget::rotateRight);
    connect(zoomInButton,SIGNAL(clicked()),this,SLOT(zoomIn()));
    connect(zoomOutButton,SIGNAL(clicked()),this,SLOT(zoomOut()));
    connect(resetButton,&QToolButton::clicked,this,&EditorWidget::resetView);

    //sliders
    connect(zoomSlider,&QSlider::valueChanged,this,&EditorWidget::setUpMatrix);
    connect(rotateSlider,&QSlider::valueChanged,this,&EditorWidget::setUpMatrix);

    //scrollbars
    connect(view->horizontalScrollBar(),&QScrollBar::valueChanged,this,&EditorWidget::enableResetButton);
    connect(view->verticalScrollBar(),&QScrollBar::valueChanged,this,&EditorWidget::enableResetButton);

    setUpMatrix();
}

void EditorWidget::enableResetButton(){
    resetButton->setEnabled(true);
}

void EditorWidget::resetView() {
    zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setUpMatrix();
    view->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void EditorWidget::setUpMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateSlider->value());

    view->setMatrix(matrix);
    resetButton->setEnabled(true);
}

void EditorWidget::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void EditorWidget::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}

void EditorWidget::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void EditorWidget::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}

EditorView* EditorWidget::getView() const {
    return view;
}

void EditorWidget::keyPressEvent(QKeyEvent *event)
{
    //ctrl-- and ctrl-+
    if(event->modifiers() & Qt::ControlModifier) {
        switch (event->key()) {
        case Qt::Key_Minus:
            zoomOut(6);
            return;
        case Qt::Key_Equal:
            zoomIn(6);
            return;
        default:
            return;
        }
    }
}
