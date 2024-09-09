#include <QPainterPath>
#include <QGraphicsScene>
#include "arrow.h"
#include "magpoint.h"

Arrow::Arrow(MagPoint* start,MagPoint* end,QList<ArrowPoint*> pathp) : QGraphicsPathItem()
{
    startp = start;
    endp = end;
    this->pathp = pathp;
    for(auto p : pathp)
    {
        p->setParentItem(this);
    }
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(-1000);
}

Arrow::~Arrow()
{
    for(auto p : pathp)
    {
        if(p)
        {
            if(scene())
                scene()->removeItem(p);
            delete p;
        }
        p = nullptr;
    }
    if(startp)
        startp->removeArrow(this);
    startp = nullptr;
    if(endp)
        endp->removeArrow(this);
    endp = nullptr;
    if(scene())
        scene()->removeItem(this);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = this->path();
    path.addPath(this->path());
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;

    path.moveTo(mapFromScene(startp->scenePos()));
    QPointF lastP = startp->scenePos();
    QLineF l;
    for(auto p : pathp)
    {
        path.lineTo(p->pos());
        lastP = p->scenePos();
    }
    l = QLineF(mapFromScene(lastP),mapFromScene(endp->scenePos()));
    path.lineTo(mapFromScene(endp->scenePos()));
    QPen pen;
    pen.setColor(myColor); // 设置颜色
    pen.setWidth(3);//设置宽度
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(path);
    setPath(path);
    double angle = std::atan2(l.dy(), -l.dx());// 计算线条与水平线之间的角度

    //下面开始绘制线条
    QPointF arrowP1 = l.p2() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                            cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = l.p2() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                            cos(angle + M_PI - M_PI / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << l.p2() << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHead);
}
