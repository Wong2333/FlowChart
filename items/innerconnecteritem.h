#ifndef INNERCONNECTERITEM_H
#define INNERCONNECTERITEM_H

#include "../custombaseitem.h"

class InnerConnecterItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 26 };
    int type() const override {return Type;}
    InnerConnecterItem();
};

#endif // INNERCONNECTERITEM_H
