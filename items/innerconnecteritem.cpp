#include "innerconnecteritem.h"

InnerConnecterItem::InnerConnecterItem() {
    QPainterPath path;
    QPolygonF pol;


    int radius = 60;  // 圆的半径
    path.addEllipse(QPointF(0, 0), radius, radius);  // 以(0, 0)为中心绘制圆形
    pol << path.toFillPolygon();

    setPolygon(pol);

    MagPoints.append(new MagPoint(0,-60 ,3));//设置吸附点
    MagPoints.append(new MagPoint(60,0,3));
    MagPoints.append(new MagPoint(0, 60,3));
    MagPoints.append(new MagPoint(-60,0,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}
