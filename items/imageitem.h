#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "../custombaseitem.h"

class ImageItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 30 };
    int type() const override {return Type;}
    ImageItem(QString file);
    QPixmap pixmap;
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override ;

};

#endif // IMAGEITEM_H
