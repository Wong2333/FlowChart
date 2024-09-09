#ifndef STARTITEM_H
#define STARTITEM_H

#include "../custombaseitem.h"

class StartItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 23 };
    int type() const override {return Type;}
    StartItem();
};

#endif // STARTITEM_H
