#ifndef DECISIONITEM_H
#define DECISIONITEM_H

#include "../custombaseitem.h"

class DecisionItem : public CustomBaseItem
{
public:
    enum { Type = UserType + 21 };
    int type() const override {return Type;}
    DecisionItem();
};

#endif // DECISIONITEM_H
