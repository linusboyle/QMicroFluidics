#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;
class QMenu;

#define PIPE_LENGTH 80
#define PIPE_WIDTH 10

class PipeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PipeScene(QObject* parent = nullptr);
    ~PipeScene();

    void reset(ConfigurationEntity* _entity);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
    void deleteSelectionItems();
    void restore();

private slots:
    void onPipeRequsetResetWidth(qreal id,qreal newWidth);

signals:
    void needCalc(const QVector<qreal>&);
    void contextDemandClear();
    void requestPopUpWarningBox();

private:
    ConfigurationEntity* entity;
    QMenu* contextmenu;
    QHash<int,QGraphicsItem*> items;

    QVector<qreal> getStatusMatrix() const;
    void initContextMenu();
};

#endif // PIPESCENE_H
