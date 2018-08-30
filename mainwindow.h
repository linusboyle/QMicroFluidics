#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PipeScene;
class EditorWidget;
class NewDesignDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createNewDesign();

private:
    void initUI();
    void initGeometry();

    PipeScene* scene;
    EditorWidget* editor;
    NewDesignDialog* dialog;

private slots:
    void clearScene();
    void restoreScene();
    void showAboutMenu();
    void popupWarning();
};


#endif // MAINWINDOW_H
