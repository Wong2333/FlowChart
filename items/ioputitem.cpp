#include "ioputitem.h"

ioputItem::ioputItem() {
    QPolygonF pol;
    pol << QPointF(-50,-50 ) << QPointF(75, -50)

        << QPointF(50, 50) << QPointF(-75,50)<< QPointF(-50,-50);//画出多边形
    setPolygon(pol);

    MagPoints.append(new MagPoint(12.5, -50,3));//设置吸附点
    MagPoints.append(new MagPoint(62.5, 0,3));
    MagPoints.append(new MagPoint(-12.5, 50,3));
    MagPoints.append(new MagPoint(-62.5,0,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}
