#ifndef OUTERCONNECTERITEM_H
#define OUTERCONNECTERITEM_H

#include "../custombaseitem.h"

class OuterConnecterItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 27 };
    int type() const override {return Type;}
    OuterConnecterItem();
};

#endif // OUTERCONNECTERITEM_H
