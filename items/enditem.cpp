#include "enditem.h"

EndItem::EndItem() {
    QPainterPath path;
    QPolygonF pol;


    QRectF rect(-80, -40, 160, 80);    // 中心为(0, 0)，矩形宽155，高80
    path.addRoundedRect(rect, 40, 40);   // 圆角半径为40，形成椭圆形外观
    pol << path.toFillPolygon();

    setPolygon(pol);

    MagPoints.append(new MagPoint(0,-40 ,3));//设置吸附点
    MagPoints.append(new MagPoint(80,0,3));
    MagPoints.append(new MagPoint(0, 40,3));
    MagPoints.append(new MagPoint(-80,0,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}
