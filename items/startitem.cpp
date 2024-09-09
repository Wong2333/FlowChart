#include "startitem.h"
#include<QPainter>


StartItem::StartItem() : CustomBaseItem(){

    QPolygonF pol;
    QPainter painter;
    pol << QPointF(-50, -50) << QPointF(50, -50)
        << QPointF(100, 0) << QPointF(50, 50)
        << QPointF(-50, 50) << QPointF(-100,0) << QPointF(-50,-50);//画出多边形
    setPolygon(pol);

    MagPoints.append(new MagPoint(-50, -50,3));//设置吸附点
    MagPoints.append(new MagPoint(50, -50,3));
    MagPoints.append(new MagPoint(100, 0,3));
    MagPoints.append(new MagPoint(50, 50,3));
    MagPoints.append(new MagPoint(-50, 50,3));
    MagPoints.append(new MagPoint(-100,0,3));
    MagPoints.append(new MagPoint(0, 50,3));
    MagPoints.append(new MagPoint(0, -50,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }

}

