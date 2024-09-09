#ifndef ARROWPOINT_H
#define ARROWPOINT_H

#include <QGraphicsEllipseItem>
#include <QPointF>
class Arrow;
class ArrowPoint : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 1 };
    int type() const{return Type;}
    ArrowPoint(qreal x, qreal y, QGraphicsItem *parent = nullptr);
    ArrowPoint(QPointF point, QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;

};

#endif // ARROWPOINT_H
