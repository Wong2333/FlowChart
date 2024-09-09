#include <QBrush>
#include <QGraphicsEllipseItem>
#include "arrowpoint.h"

ArrowPoint::ArrowPoint(qreal x, qreal y, QGraphicsItem *parent)
    : QGraphicsEllipseItem(-2, -2, 4, 4, parent)
{
    setPos(x,y);
    QBrush brush(Qt::gray);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
}

ArrowPoint::ArrowPoint(QPointF point, QGraphicsItem *parent)
    : QGraphicsEllipseItem(-2, -2, 4, 4, parent)
{
    setPos(point.x(),point.y());
    QBrush brush(Qt::gray);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
}

QPainterPath ArrowPoint::shape() const {
    QRectF extendedRect = QRectF(-4,-4,8,8);

    // 创建一个更大的椭圆路径
    QPainterPath path;
    path.addEllipse(extendedRect);

    // 返回新的形状路径
    return path;
}
