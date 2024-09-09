#ifndef CUSTOMBASEITEM_H
#define CUSTOMBASEITEM_H
#include <QGraphicsItemGroup>
#include "arrow.h"
#include "magpoint.h"
#include "textitem.h"
class CustomBaseItem : public QGraphicsPolygonItem
{
public:
    CustomBaseItem();
    ~CustomBaseItem();
    enum { Type = UserType + 20 };
    int type() const override {return Type;}
    QList<MagPoint*> MagPoints;//保存吸附点
    TextItem text = TextItem("请输入");//图元中间的文本框
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    void setScale(double x,double y) {now_scale_x = x;now_scale_y = y;}//设置缩放比例
    void doSize(double x = 0,double y = 0);//放大
    void doRotation(double r);//旋转
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void showMag();
    void hideMag();
    QColor myColor = Qt::white;

protected:
    bool inited = false;

private:
    double now_scale_x = 1,now_scale_y = 1;
    double scale_x = 0.1,scale_y = 0.1;//缩放比例
};

#endif // CUSTOMBASEITEM_H
