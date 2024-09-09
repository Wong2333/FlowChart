#ifndef AUTOARROW_H
#define AUTOARROW_H

#include <QGraphicsPathItem>
#include "arrowpoint.h"
class MagPoint;
class AutoArrow : public QGraphicsPathItem
{
public:
    AutoArrow(MagPoint* start,MagPoint* end,QList<ArrowPoint*>);
    enum { Type = UserType + 5 };
    int type() const{return Type;}
    ~AutoArrow();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    MagPoint* startp,*endp;
    int arrowSize = 10;
    QList<ArrowPoint*> pathp;
    QPolygonF arrowHead;
    QPainterPath shape() const override;
    QColor myColor = Qt::black;
};

#endif // AUTOARROW_H
