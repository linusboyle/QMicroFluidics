#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QFrame>

class QSlider;
class QToolButton;
class EditorView;
class VelocityIndicator;

class EditorWidget:public QFrame
{
    Q_OBJECT
public:
    EditorWidget(QWidget* parent = nullptr);

    EditorView* getView() const;
    VelocityIndicator* getIndicator() const;

signals:
    void requestDeletion();

protected:
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void zoomIn(int scale = 1);
    void zoomOut(int scale = 1);
    void resetView();
    void rotateLeft();
    void rotateRight();

private slots:
    void enableResetButton();
    void setUpMatrix();

private:
    EditorView* view;
    VelocityIndicator* indicator;

    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;
    QToolButton* rotateLeftButton;
    QToolButton* rotateRightButton;
    QToolButton* resetButton;
    QSlider* zoomSlider;
    QSlider* rotateSlider;

};

#endif // EDITORWIDGET_H
