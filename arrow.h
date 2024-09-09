#ifndef ARROW_H
#define ARROW_H
#include <QGraphicsPathItem>
#include "QPainter"
#include "arrowpoint.h"
class MagPoint;

class Arrow : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 3 };
    int type() const{return Type;}
    Arrow(MagPoint* start,MagPoint* end,QList<ArrowPoint*>);
    ~Arrow();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    MagPoint* startp,*endp;
    int arrowSize = 10;
    QList<ArrowPoint*> pathp;
    QPolygonF arrowHead;
    QPainterPath shape() const override;
    QColor myColor = Qt::black;

};

#endif // ARROW_H
