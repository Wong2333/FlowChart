#ifndef PREDEFINEITEM_H
#define PREDEFINEITEM_H

#include "../custombaseitem.h"

class PredefineItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 29 };
    int type() const override {return Type;}
    PredefineItem();
};

#endif // PREDEFINEITEM_H
