#ifndef MAGPOINT_H
#define MAGPOINT_H
#include <QGraphicsEllipseItem>
#include "arrow.h"
#include "autoarrow.h"
class MagPoint : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 2 };
    int type() const{return Type;}
    MagPoint(qreal x, qreal y, qreal r, QGraphicsItem *parent = nullptr);

    QList<Arrow*> arrows;
    QList<AutoArrow*> autoArrows;
    void addArrow(Arrow*);
    void addArrow(AutoArrow*);
    void removeArrow(Arrow*);
    void removeArrow(AutoArrow*);
    void removeArrows();
    QPainterPath shape() const override;
};

#endif // MAGPOINT_H
