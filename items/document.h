#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../custombaseitem.h"

class Document : public CustomBaseItem
{
public:
    enum { Type = UserType + 24 };
    int type() const override {return Type;}
    Document();
};

#endif // DOCUMENT_H
