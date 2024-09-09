#ifndef ITEMSCENE_H
#define ITEMSCENE_H
#include <QGraphicsScene>
#include <QRubberBand>
#include "custombaseitem.h"
#include "textitem.h"
#include<QXmlStreamAttributes>
#include<QStack>


class ItemScene : public QGraphicsScene
{
public:
    ItemScene();
    ItemScene(qreal width,qreal height);
    void setSize(qreal,qreal);
    enum Mode { InsertItem, InsertArrow, InsertText, MoveItem, InsertAutoArrow};
    void setMode(Mode mode){myMode = mode;}
    void insertItem(CustomBaseItem* item);
    void setMoveItem();
    void insertArr();
    void insertText(TextItem*);
    void insertAutoArrow();
    void deleteSelectItem();
    void writeTo(QIODevice&,QList<QGraphicsItem*>);
    QList<QGraphicsItem*> readFrom(QIODevice&);
    void saveTo();
    void save();
    void openFile();
    Mode getMode(){return myMode;}
    QList<QColor> mySceneColors = {Qt::white,Qt::black,Qt::black};
    QColor currentColor = Qt::black;
    QFont defaultFont = QFont("Microsoft YaHei UI", 9);
    QPair<QString, QColor> pair = QPair<QString, QColor>("图形颜色", Qt::black);
    QAction *copyAction;
    QAction *pasteAction;
    QAction *cutAction;
    QAction*undoAction;
    QAction*redoAction;
    QAction* imageAction;
    void paste();
    void copy();
    void cut();
    void saveSceneState();
    void redo();
    void undo();
    void inputImage();

    void Check(QPointF s,QPointF t,QPainterPath& pa);
    bool check(int a,int b,QPointF c,QPointF d);
    bool check2(int a,int b,QPointF c,QPointF d);
    bool onedge(int x,int y,CustomBaseItem* id);
    void dfs(QPointF u,QPointF s,QPointF t);
    void bfs(QPointF s,QPointF t,QPainterPath& pa);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent) override;
    QGraphicsItem* loadItem(QXmlStreamAttributes att,
                            std::map<unsigned long long,CustomBaseItem*>& itemMap);
    QGraphicsItem* loadText(QXmlStreamAttributes att);
    QGraphicsItem* loadArrow(QXmlStreamAttributes att,QList<ArrowPoint*>pathp,
                             std::map<unsigned long long,CustomBaseItem*> itemMap);
    QGraphicsItem* loadAutoArrow(QXmlStreamAttributes att,QList<ArrowPoint*>pathp,
                                 std::map<unsigned long long,CustomBaseItem*> itemMap);
    void showMag();
    void hideMag();
    Mode myMode;
    qreal width = 1500,height = 1200;
    CustomBaseItem* insert_item = nullptr;
    TextItem* insert_text = nullptr;
    MagPoint* startp = nullptr;
    MagPoint* endp = nullptr;
    QList<ArrowPoint*>pathp;
    QList<QGraphicsLineItem*>pathl;
    QByteArray copyBytes;
    QString lastSaveFileName;
    QStack<QByteArray> undoStack;
    QStack<QByteArray> redoStack;


};

#endif // ITEMSCENE_H
