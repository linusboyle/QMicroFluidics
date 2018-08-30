#ifndef PIPESCENE_H
#define PIPESCENE_H

#include <QGraphicsScene>

class ConfigurationEntity;
class QMenu;
class EditorView;

#define PIPE_LENGTH qreal(80)
#define PIPE_WIDTH qreal(10)
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

private slots:
    void onPipeRequsetResetWidth(qreal id);

signals:
    void needCalc(const QVector<qreal>&);
    void contextDemandClear();
    void requestPopUpWarningBox();

private:
    ConfigurationEntity* entity;
    QMenu* contextmenu;
    QHash<int,QGraphicsItem*> items;
    EditorView* view;

    QVector<qreal> getStatusMatrix() const;
    void initContextMenu();
};

#endif // PIPESCENE_H
