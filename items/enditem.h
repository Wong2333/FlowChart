#ifndef ENDITEM_H
#define ENDITEM_H

#include "../custombaseitem.h"

class EndItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 25 };
    int type() const override {return Type;}
    EndItem();
};

#endif // ENDITEM_H
