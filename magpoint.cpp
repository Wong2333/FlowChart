#include "magpoint.h"


MagPoint::MagPoint(qreal x, qreal y, qreal r, QGraphicsItem *parent)
    : QGraphicsEllipseItem(-r, -r, r*2, r*2, parent)
{
    //setTransformOriginPoint(r,r);
    setPos(x,y);
    QBrush brush(Qt::gray);
    setBrush(brush);
}

void MagPoint::addArrow(Arrow* arrow){
    arrows.append(arrow);
}

void MagPoint::removeArrow(Arrow* arrow){
    arrows.removeAll(arrow);
}


void MagPoint::addArrow(AutoArrow* arrow){
    autoArrows.append(arrow);
}

void MagPoint::removeArrow(AutoArrow* arrow){
    autoArrows.removeAll(arrow);
}

void MagPoint::removeArrows(){

}

QPainterPath MagPoint::shape() const{
    QRectF extendedRect = QRectF(-20,-20,40,40);

    // 创建一个更大的椭圆路径
    QPainterPath path;
    path.addEllipse(extendedRect);
    return path;
}
