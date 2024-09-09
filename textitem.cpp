#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include "textitem.h"
#include "itemscene.h"

TextItem::TextItem() :QGraphicsTextItem(){
    setDefaultTextColor(myColor);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPos(-boundingRect().width() / 2, -boundingRect().height() / 2);
    setTransformOriginPoint(boundingRect().width() / 2,boundingRect().height() / 2);
    connect(document(),&QTextDocument::contentsChanged,this,&TextItem::updatePosition);
    setZValue(0);
}

TextItem::TextItem(QString text) :QGraphicsTextItem(text){
    setDefaultTextColor(myColor);
    setFlag(QGraphicsItem::ItemIsMovable);
    setPlainText(text);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPos(-boundingRect().width() / 2, -boundingRect().height() / 2);
    setTransformOriginPoint(boundingRect().width() / 2,boundingRect().height() / 2);
    connect(document(),&QTextDocument::contentsChanged,this,&TextItem::updatePosition);
    setZValue(0);
}

QVariant TextItem::itemChange(GraphicsItemChange change,
                                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

void TextItem::focusOutEvent(QFocusEvent *event)  // 失去焦点
{
    if(isInItem)
    {
        QGraphicsTextItem::focusOutEvent(event);
        return;
    }
    setTextInteractionFlags(Qt::NoTextInteraction);
    QTextCursor cursor = textCursor();
    cursor.clearSelection();  // 把选中的字取消选中
    setTextCursor(cursor);

    if (toPlainText().isEmpty()) {
        QGraphicsScene* scenePtr = scene();
        if (scenePtr) {
            scenePtr->removeItem(this);
            emit aboutToBeDeleted();
            deleteLater();
        }
    }

    QGraphicsTextItem::focusOutEvent(event);
}

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 获取当前文本光标
        QTextCursor cursor = textCursor();
        cursor.setPosition(event->scenePos().x(), QTextCursor::KeepAnchor);
        setTextCursor(cursor);

        // 确保QGraphicsTextItem被选中
        setSelected(true);
    }
    QGraphicsTextItem::mousePressEvent(event);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void TextItem::updatePosition(){
    if(!isInItem) return;
    if(toPlainText().length() == 0){
        setPos(0 , -boundingRect().height() / 2);
    }
    else {
        setPos(-boundingRect().width() / 2 * now_scale_x, -boundingRect().height() / 2 * now_scale_y);
    }
}


void TextItem::doSize(double x,double y){

    QTransform transform;
    transform.scale(now_scale_x = (now_scale_x * x),
                    now_scale_y = (now_scale_y * y));
    // 将变换应用到QGraphicsItem上
    setTransform(transform);
    updatePosition();
}

void TextItem::doRotation(double r){//旋转
    setRotation(rotation() + r);
    updatePosition();
}

void TextItem::HighTextExtra(int l,int r)
{
    QTextCharFormat format;
    format.setBackground(Qt::red);
    QTextCursor cursor=textCursor();
    cursor.setPosition(l, QTextCursor::MoveAnchor);
    cursor.setPosition(r, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
}
void TextItem::HighText(int l,int r)
{
    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    QTextCursor cursor=textCursor();
    cursor.setPosition(l, QTextCursor::MoveAnchor);
    cursor.setPosition(r, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
}
void TextItem::LowText(int l,int r)
{
    QTextCharFormat format;
    format.setBackground(Qt::transparent);
    QTextCursor cursor=textCursor();
    cursor.setPosition(l, QTextCursor::MoveAnchor);
    cursor.setPosition(r, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
}
