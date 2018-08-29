#include "editorview.h"
#include "editorwidget.h"
#include <QWheelEvent>

#ifdef QT_DEBUG
#include <QDebug>
#endif

EditorView::EditorView(QWidget *parent)
    :QGraphicsView(parent)
{
    //some settings
    setDragMode(RubberBandDrag);
    setRenderHint(QPainter::Antialiasing,true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void EditorView::wheelEvent(QWheelEvent *event) {
    EditorWidget* _parent = qobject_cast<EditorWidget*>(parent());

#ifdef QT_DEBUG
    if(!_parent){
        Q_UNREACHABLE();

        qDebug()<<"the parent is not an EditorWidget,it's strange!";
        return;
    }
#endif

    if (event->modifiers() & Qt::ControlModifier) {
        if (event->delta() > 0) {
            _parent->zoomIn(6);
        } else {
            _parent->zoomOut(6);
        }
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
