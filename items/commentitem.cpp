#include "commentitem.h"

CommentItem::CommentItem() {
    QPolygonF pol;
    QPainterPath path;
    path.moveTo(-200, 0);            // 起始点：左上角 (相对中心点)
    path.lineTo(-100, 0);
    path.lineTo(-100,-75);
    path.lineTo(100,-75);
    path.lineTo(100,75);
    path.lineTo(-100,75);
    path.lineTo(-100,0);
    path.lineTo(-200,0);
    pol << path.toFillPolygon();
    setPolygon(pol);


    // MagPoints.append(new MagPoint(0,-40 ,3));//设置吸附点
    // MagPoints.append(new MagPoint(80,0,3));
    // MagPoints.append(new MagPoint(0, 40,3));
    // MagPoints.append(new MagPoint(-80,0,3));
    // for(int i = 0;i<MagPoints.size();i++)
    // {
    //     MagPoints[i]->setParentItem(this);
    //     MagPoints[i]->hide();
    //     MagPoints[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
    // }
}


void CommentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath path;
    path.moveTo(-200, 0);            // 起始点：左上角 (相对中心点)
    path.lineTo(-100, 0);
    path.lineTo(-100,-75);
    path.lineTo(100,-75);
    path.lineTo(100,75);
    path.lineTo(-100,75);
    path.lineTo(-100,0);
    QPen pen;
    pen.setStyle(Qt::DashLine);  // 设置为虚线
    painter->setPen(pen);
    painter->setBrush(myColor);
    painter->drawPath(path);
}


