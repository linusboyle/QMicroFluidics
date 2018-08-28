#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QFrame>

class QSlider;
class QToolButton;
class EditorView;

class EditorWidget:public QFrame
{
    Q_OBJECT
public:
    EditorWidget(QWidget* parent = nullptr);

    EditorView* getView() const;

public slots:
    void zoomIn(int scale = 1);
    void zoomOut(int scale = 1);
    void resetView();

private slots:
    void enableResetButton();
    void setUpMatrix();
    void rotateLeft();
    void rotateRight();

private:
    EditorView* view;
    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;
    QToolButton* rotateLeftButton;
    QToolButton* rotateRightButton;
    QToolButton* resetButton;
    QSlider* zoomSlider;
    QSlider* rotateSlider;
};

#endif // EDITORWIDGET_H
