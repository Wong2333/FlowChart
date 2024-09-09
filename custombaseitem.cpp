#include <QGraphicsItem>
#include <QGraphicsScene>
#include "custombaseitem.h"

CustomBaseItem::CustomBaseItem() : QGraphicsPolygonItem() {
    text.setParentItem(this);
    text.isInItem = true;
    text.setFlag(QGraphicsItem::ItemIsMovable,false);
    text.setTextInteractionFlags(Qt::TextEditorInteraction);
    setTransformOriginPoint(0,0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setZValue(0);
}

CustomBaseItem::~CustomBaseItem() {
    for(auto p : MagPoints)
    {
        QList<Arrow*> arrows = p->arrows;
        for(auto arr : arrows)
        {
            delete arr;
        }
        if(scene())
            scene()->removeItem(p);
        delete p;
    }
}


void CustomBaseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(myColor);
    painter->drawPolygon(polygon());
}

void CustomBaseItem::showMag(){//显示吸附点，并且变得可选择，一般会在插入箭头时调用该函数
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->show();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
}
void CustomBaseItem::hideMag(){//隐藏吸附点
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}

QPainterPath CustomBaseItem::shape() const
{
    QPainterPath path = QGraphicsPolygonItem::shape();
    path.addPolygon(polygon());
    return path;
}

QVariant CustomBaseItem::itemChange(GraphicsItemChange change, const QVariant &value){

    if(change == QGraphicsItem::ItemPositionHasChanged)
    {
        for(auto p : MagPoints)
        {
            for(auto arr : p->arrows)
            {        
                arr->update();
            }
        }
    }
    else if(change == QGraphicsItem::ItemPositionChange)
    {
        //物体位置准备发生变化
    }
    return value;
}

void CustomBaseItem::doRotation(double r){//旋转
    setRotation(rotation() + r);
}

void CustomBaseItem::doSize(double x,double y){
    if(x<0 ||y<0) return;
    QTransform transform;
    transform.scale(now_scale_x = (now_scale_x * x),
                    now_scale_y = (now_scale_y * y));
    // 将变换应用到QGraphicsItem上
    setTransform(transform);
    text.doSize(1/x,1/y);
}
