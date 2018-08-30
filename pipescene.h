#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;
class QMenu;

class PipeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PipeScene(QObject* parent = nullptr);
    ~PipeScene();

    void restore();
    void reset(ConfigurationEntity* _entity);

    QVector<qreal> getStatusMatrix() const;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
    void deleteSelectionItems();

signals:
    void needCalc(const QVector<qreal>&);

private:
    ConfigurationEntity* entity;
    QMenu* contextmenu;
    QHash<int,QGraphicsItem*> items;

    void initContextMenu();
};

#endif // PIPESCENE_H
