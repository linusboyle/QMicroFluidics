#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;

class PipeScene : public QGraphicsScene
{
public:
    PipeScene(QObject* parent = nullptr);

    void restore();
    void reset(ConfigurationEntity* _entity);

public slots:
    void deleteSelectionItems();

private:
    ConfigurationEntity* entity;
    QHash<int,QGraphicsItem*> items;
};

#endif // PIPESCENE_H
