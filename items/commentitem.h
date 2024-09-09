#ifndef COMMENTITEM_H
#define COMMENTITEM_H

#include "../custombaseitem.h"

class CommentItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 28 };
    int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    CommentItem();
};

#endif // COMMENTITEM_H
