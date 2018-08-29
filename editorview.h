#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>

class EditorWidget;

class EditorView:public QGraphicsView
{
public:
    EditorView(EditorWidget* parent = nullptr);

    //disabled because of sigv fault
//protected:
//    void wheelEvent(QWheelEvent* event) override;

private:
    EditorWidget* _parent;
};

#endif // EDITORVIEW_H
