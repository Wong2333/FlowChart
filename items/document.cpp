#include "document.h"

Document::Document() {
    QPainterPath path;
    QPolygonF pol;


    path.moveTo(-80, -40);            // 起始点：左上角 (相对中心点)
    path.lineTo(80, -40);             // 顶部边线（直线）
    path.lineTo(80,50);               // 右侧边线（直线）

    // 波浪底边（使用三次贝塞尔曲线）
    path.cubicTo(60, 80, -60, 20, -80, 50); // 控制点和终点定义波浪曲线
    path.lineTo(-80, -40);           // 闭合路径（左侧直线）
    pol << path.toFillPolygon();

    setPolygon(pol);

    MagPoints.append(new MagPoint(-80,0 ,3));//设置吸附点
    MagPoints.append(new MagPoint(0,-40,3));
    MagPoints.append(new MagPoint(80, 0,3));
    MagPoints.append(new MagPoint(0,49,3));
    for(int i = 0;i<MagPoints.size();i++)
    {
        MagPoints[i]->setParentItem(this);
        MagPoints[i]->hide();
        MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}
