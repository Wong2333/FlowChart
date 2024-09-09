#ifndef TEXTITEM_H
#define TEXTITEM_H
#include <QGraphicsTextItem>
#include <QFont>

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 4 };
    int type() const{return Type;}
    TextItem();
    TextItem(QString text);
    bool isInItem = false;
    void updatePosition();
    QColor myColor = Qt::black;
    QFont defaultFont = QFont("Microsoft YaHei UI", 9);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void doSize(double x,double y);
    void doRotation(double r);
    void HighTextExtra(int l,int r);
    void HighText(int l,int r);
    void LowText(int l,int r);

signals:
    void aboutToBeDeleted();
    void lostFocus(TextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    double now_scale_x = 1,now_scale_y = 1;
};

#endif // TEXTITEM_H
