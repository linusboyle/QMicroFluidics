#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>

class EditorView:public QGraphicsView
{
public:
    EditorView(QWidget* parent = nullptr);
protected:
    void wheelEvent(QWheelEvent* event) override;
};

#endif // EDITORVIEW_H
