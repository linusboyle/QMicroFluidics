/**
 * editorwidget.h
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
