#ifndef PROCESSITEM_H
#define PROCESSITEM_H

#include "../custombaseitem.h"

class ProcessItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 22 };
    int type() const override {return Type;}
    ProcessItem();
};

#endif // PROCESSITEM_H
