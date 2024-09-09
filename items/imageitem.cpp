#include "imageitem.h"


ImageItem::ImageItem(QString file)
{
    QPolygonF pol;
    pol << QPointF(-200, -150) << QPointF(-200, 150)

        << QPointF(200, 150) << QPointF(200,-150);//画出多边形
    setPolygon(pol);
    text.hide();

    pixmap = QPixmap(file);
}

QRectF ImageItem::boundingRect() const{
    // 返回图片的边界矩形
    return QRectF(-200, -150, 400,300);
}



void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    // 在图形项上绘制图片
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());
}
