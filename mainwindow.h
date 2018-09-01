/**
 * mainwindow.h
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
    void initTranslations();
    void initFont();

    PipeScene* scene;
    EditorWidget* editor;
    NewDesignDialog* dialog;

private slots:
    void clearScene();
    void restoreScene();
    void showAboutMenu();
    void popupWarning();
    void openSourceCodePage();
    void openPaper();
    void printDesign();
    void saveToImage();
};


#endif // MAINWINDOW_H
