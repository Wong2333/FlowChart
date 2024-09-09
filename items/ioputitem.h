#ifndef IOPUTITEM_H
#define IOPUTITEM_H

#include "../custombaseitem.h"

class ioputItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 31 };
    int type() const override {return Type;}
    ioputItem();
};

#endif // IOPUTITEM_H
