/**
 * pipescene.h
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
#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;
class QMenu;
class EditorView;
class Pipe;

#define PIPE_REAL_WIDTH qreal(200)

class PipeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PipeScene(QObject* parent = nullptr);
    ~PipeScene();

    void reset(ConfigurationEntity* _entity);
    void setView(EditorView* _view);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
    void deleteSelectionItems();
    void restore();
    void changePipeColor(QVector<qreal> velocity);

private slots:
    void onPipeRequsetResetWidth(qreal id);

signals:
    void needCalc(const QVector<qreal>&);
    void contextDemandClear();
    void requestPopUpWarningBox();

private:
    ConfigurationEntity* entity;
    QMenu* contextmenu;
    QHash<int,Pipe*> items;
    EditorView* view;

    QVector<qreal> getStatusMatrix() const;
    void initContextMenu();
};

#endif // PIPESCENE_H
