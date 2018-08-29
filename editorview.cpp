#include "editorview.h"
#include "editorwidget.h"
#include <QWheelEvent>

#ifdef QT_DEBUG
#include <QDebug>
#endif

EditorView::EditorView(EditorWidget *parent)
    :QGraphicsView(parent)
{
    //some settings
    setDragMode(RubberBandDrag);
    setRenderHint(QPainter::Antialiasing,true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

}

void EditorView::wheelEvent(QWheelEvent *event) {
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
