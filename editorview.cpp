/**
 * editorview.cpp
 * Copyright (c) 2018 Linus Boyle <linusboyle@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

//void EditorView::wheelEvent(QWheelEvent *event) {
//    if (event->modifiers() & Qt::ControlModifier) {
//        if (event->delta() > 0) {
//            _parent->zoomIn(6);
//        } else {
//            _parent->zoomOut(6);
//        }
//    } else {
//        QGraphicsView::wheelEvent(event);
//    }
//}
