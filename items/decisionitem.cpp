#include "decisionitem.h"

DecisionItem::DecisionItem() {
    QPolygonF pol;
    pol << QPointF(-100, 0) << QPointF(0, 60)

        << QPointF(100, 0) << QPointF(0,-60);//画出多边形
    setPolygon(pol);

    MagPoints.append(new MagPoint(-100, 0,3));//设置吸附点
    MagPoints.append(new MagPoint(0, 60,3));
    MagPoints.append(new MagPoint(100, 0,3));
    MagPoints.append(new MagPoint(0,-60,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}


