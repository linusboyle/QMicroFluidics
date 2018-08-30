#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;

class PipeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PipeScene(QObject* parent = nullptr);

    void restore();
    void reset(ConfigurationEntity* _entity);

    QVector<qreal> getStatusMatrix() const;

public slots:
    void deleteSelectionItems();

signals:
    void needCalc(const QVector<qreal>&);

private:
    ConfigurationEntity* entity;
    QHash<int,QGraphicsItem*> items;
};

#endif // PIPESCENE_H
