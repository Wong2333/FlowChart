#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QGraphicsView>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QBuffer>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "itemscene.h"
#include "arrow.h"
#include "./items/startitem.h"
#include "./items/decisionitem.h"
#include "./items/processitem.h"
#include "./items/document.h"
#include "./items/enditem.h"
#include "./items/innerconnecteritem.h"
#include "./items/outerconnecteritem.h"
#include "./items/predefineitem.h"
#include "./items/commentitem.h"
#include "./items/imageitem.h"
#include "./items/ioputitem.h"

ItemScene::ItemScene() {
    myMode = Mode::MoveItem;
    setSceneRect(QRectF(-width/2, -height/2, width, height));
}
ItemScene::ItemScene(qreal width,qreal height) {
    myMode = Mode::MoveItem;
    this->width = width;
    this->height = height;
    setSceneRect(QRectF(-width/2, -height/2, width, height));
}

void ItemScene::setSize(qreal width,qreal height){
    this->width = width;
    this->height;
    setSceneRect((QRectF(-width/2, -height/2, width, height)));
}

void ItemScene::showMag()
{
    QList<QGraphicsItem*> list = items();
    for(auto i : list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->showMag();
        }

    }
}

void ItemScene::hideMag()
{
    QList<QGraphicsItem*> list = items();
    for(auto i : list)
    {
        if(i->type()>QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->hideMag();
        }
    }
}

void ItemScene::setMoveItem(){
    if(myMode == InsertItem)
    {
        if(insert_item != nullptr)
            delete insert_item;
        insert_item = nullptr;
        myMode = MoveItem;
    }
    else if(myMode == InsertArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l:pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        hideMag();
        views().first()->setMouseTracking(false);
        myMode = MoveItem;
    }
    else if(myMode == InsertText)
    {
        if(insert_text!=nullptr)
            delete insert_text;
        insert_text = nullptr;
        myMode = MoveItem;
    }
    else if(myMode == InsertAutoArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l:pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        hideMag();
        views().first()->setMouseTracking(false);
        myMode = MoveItem;
    }
}

void ItemScene::insertArr()
{
    if(myMode == InsertItem)
    {
        if(insert_item!=nullptr)
            delete insert_item;
        insert_item = nullptr;
        myMode = InsertArrow;
    }
    else if(myMode == MoveItem)
    {
        myMode = InsertArrow;
    }
    else if(myMode == InsertText)
    {
        if(insert_text!=nullptr)
            delete insert_text;
        insert_text = nullptr;
        myMode = InsertArrow;
    }else if (myMode == InsertArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l: pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();

        myMode = InsertArrow;
    }else if (myMode == InsertAutoArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l: pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();

        myMode = InsertArrow;
    }
    showMag();
    views().first()->setMouseTracking(true);
}

void ItemScene::insertItem(CustomBaseItem* item){
    if(myMode == MoveItem)
    {
        setMode(ItemScene::InsertItem);
        insert_item = item;
    }
    else if(myMode == InsertItem)
    {
        if(insert_item!=nullptr)
            delete insert_item;
        insert_item = item;
    }
    else if(myMode == InsertArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();
        for(auto l : pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        views().first()->setMouseTracking(false);
        insert_item = item;
    }
    else if(myMode == InsertText)
    {
        if(insert_text!=nullptr)
            delete insert_text;
        insert_text = nullptr;
        insert_item = item;
    }
    else if(myMode == InsertAutoArrow){
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();
        for(auto l : pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        views().first()->setMouseTracking(false);
        insert_item = item;
    }
    myMode = InsertItem;

}

void ItemScene::insertText(TextItem* text){
    if(myMode == MoveItem)
    {
        setMode(ItemScene::InsertText);
        insert_text = text;
    }
    else if(myMode == InsertItem)
    {
        if(insert_item)
            delete insert_item;
        insert_item = nullptr;
        insert_text = text;
    }
    else if(myMode == InsertArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l : pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        views().first()->setMouseTracking(false);
        insert_text = text;
    }
    else if(myMode == InsertText)
    {
        if(insert_text)
            delete insert_text;
        insert_text = text;
    }
    else if(myMode == InsertAutoArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l : pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();
        views().first()->setMouseTracking(false);
        insert_text = text;
    }
    myMode = InsertText;
}


void ItemScene::insertAutoArrow(){
    if(myMode == InsertItem)
    {
        if(insert_item!=nullptr)
            delete insert_item;
        insert_item = nullptr;
        myMode = InsertAutoArrow;
    }
    else if(myMode == MoveItem)
    {
        myMode = InsertAutoArrow;
    }
    else if(myMode == InsertText)
    {
        if(insert_text!=nullptr)
            delete insert_text;
        insert_text = nullptr;
        myMode = InsertAutoArrow;
    }else if (myMode == InsertArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l: pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();

        myMode = InsertAutoArrow;
    }else if (myMode == InsertAutoArrow)
    {
        startp = nullptr;
        endp = nullptr;

        for(auto p : pathp)
        {
            removeItem(p);
            delete p;
        }
        pathp.clear();

        for(auto l: pathl)
        {
            removeItem(l);
            delete l;
        }
        pathl.clear();

        myMode = InsertAutoArrow;
    }
    showMag();
    views().first()->setMouseTracking(true);
}

void ItemScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (myMode) {
    case InsertItem:
        saveSceneState();
        addItem(insert_item);
        // 插入时设置图形颜色
        insert_item->myColor = this->mySceneColors[0];
        insert_item->update();
        // 插入时设置图形中文本颜色和字体格式
        insert_item->text.myColor = this->mySceneColors[1];
        insert_item->text.setDefaultTextColor(insert_item->text.myColor);
        insert_item->text.defaultFont = this->defaultFont;
        insert_item->text.setFont(insert_item->text.defaultFont);
        // 插入时更新文本框的位置，保证居中
        insert_item->text.updatePosition();
        insert_item->setPos(mouseEvent->scenePos());
        insert_item = nullptr;
        myMode = MoveItem;
        break;
    case InsertArrow:
        if(!startp)//寻找起始点
        {
            QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            for(auto i:list)
            {
                MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
                if(item)
                {
                    startp = item;  // 找到startp
                    pathl.append(new QGraphicsLineItem(QLineF(startp->scenePos(),startp->scenePos())));
                    addItem(pathl.last());
                    break;
                }
            }
        }
        else if(!endp)//寻找终点
        {
            // QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            // for(auto i:list)
            // {
            //     MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
            //     if(item)
            //     {
            //         endp = item;
            //         break;
            //     }
            // }
            int Min=1000000000,xxx,yyy;
            MagPoint* ed;
            QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            xxx=mouseEvent->scenePos().x(),yyy=mouseEvent->scenePos().y();
            for(auto i:list)
            {
                if(i->type() > QGraphicsItem::UserType + 20)
                {
                    CustomBaseItem* t = (CustomBaseItem*)i;
                    for(auto p : t->MagPoints){
                        int dis=sqrt(abs(xxx-p->scenePos().x())*abs(xxx-p->scenePos().x()+abs(yyy-p->scenePos().y())*abs(yyy-p->scenePos().y())));
                        if(dis<Min)
                        {
                            Min=dis;
                            ed=p;
                        }
                    }
                    endp=ed;
                    break;
                }
                MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
                if(item)
                {
                    endp = item;
                    break;
                }
            }
            if(endp)//找到终点，生成箭头
            {
                saveSceneState();
                Arrow* arr = new Arrow(startp,endp,pathp);
                addItem(arr);
                // 插入时设置线条颜色
                arr->myColor = this->mySceneColors[2];
                arr->update();
                startp->addArrow(arr);
                endp->addArrow(arr);
                startp = nullptr;
                endp = nullptr;
                for(auto l:pathl)
                {
                    removeItem(l);
                    delete l;
                }
                pathl.clear();
                pathp.clear();
                myMode = MoveItem;
                hideMag();
                views().first()->setMouseTracking(false);
            }
            else
            {
                pathp.append(new ArrowPoint(mouseEvent->scenePos()));
                pathl.append(new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos())));
                addItem(pathl.last());
            }

        }

        break;
    case InsertText:
        saveSceneState();
        addItem(insert_text);
        // 插入时设置文本颜色和字体格式
        insert_text->myColor = this->mySceneColors[1];
        insert_text->setDefaultTextColor(insert_text->myColor);
        insert_text->defaultFont = this->defaultFont;
        insert_text->setFont(insert_text->defaultFont);
        insert_text->setPos(mouseEvent->scenePos());
        insert_text = nullptr;
        myMode = MoveItem;
        hideMag();
        break;
    case MoveItem:
        saveSceneState();
        break;
    case InsertAutoArrow: //TODO
        if(!startp)
        {
            QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            for(auto i:list)
            {
                MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
                if(item)
                {
                    startp = item;  // 找到startp
                    pathl.append(new QGraphicsLineItem(QLineF(startp->scenePos(),startp->scenePos())));
                    addItem(pathl.last());
                    pathl.append(new QGraphicsLineItem(QLineF(startp->scenePos(),startp->scenePos())));
                    addItem(pathl.last());
                    break;
                }
            }
        }
        else if(!endp)//寻找终点
        {
            int Min=1000000000,xxx,yyy;
            MagPoint* ed;
            QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            xxx=mouseEvent->scenePos().x(),yyy=mouseEvent->scenePos().y();
            for(auto i:list)
            {
                if(i->type() > QGraphicsItem::UserType + 20)
                {
                    CustomBaseItem* t = (CustomBaseItem*)i;
                    for(auto p : t->MagPoints){
                        int dis=sqrt(abs(xxx-p->scenePos().x())*abs(xxx-p->scenePos().x()+abs(yyy-p->scenePos().y())*abs(yyy-p->scenePos().y())));
                        if(dis<Min)
                        {
                            Min=dis;
                            ed=p;
                        }
                    }
                    endp=ed;
                    break;
                }
                MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
                if(item)
                {
                    endp = item;
                    break;
                }
            }
            // QList<QGraphicsItem*>list = items(mouseEvent->scenePos());
            // for(auto i:list)
            // {
            //     MagPoint*item = qgraphicsitem_cast<MagPoint*>(i);
            //     if(item)
            //     {
            //         endp = item;
            //         break;
            //     }
            // }
            if(endp)//找到终点，生成箭头
            {
                saveSceneState();
                AutoArrow* arr = new AutoArrow(startp,endp,pathp);
                addItem(arr);
                // 插入时设置线条颜色
                arr->myColor = this->mySceneColors[2];
                arr->update();
                startp->addArrow(arr);
                endp->addArrow(arr);
                startp = nullptr;
                endp = nullptr;
                for(auto l:pathl)
                {
                    removeItem(l);
                    delete l;
                }
                pathl.clear();
                pathp.clear();
                myMode = MoveItem;
                hideMag();
                views().first()->setMouseTracking(false);
            }
            else
            {
                // int xx,yy;
                QPointF now=mouseEvent->scenePos();
                // yy=now.y();
                // int len=pathp.length();
                // if(!len) xx=startp->scenePos().x();
                // else xx=pathp.last()->scenePos().x();
                // pathp.append(new ArrowPoint(QPointF(xx,yy)));
                pathp.append(new ArrowPoint(now));
                pathl.append(new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos())));
                addItem(pathl.last());
                pathl.append(new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos())));
                addItem(pathl.last());
            }
            // else
            // {
            //     pathp.append(new ArrowPoint(mouseEvent->scenePos()));
            //     pathl.append(new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos())));
            //     addItem(pathl.last());
            // }

        }

        break;

    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void ItemScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (myMode) {
    case InsertArrow:
        if(!endp && startp)
        {
            QLineF newLine(pathl.last()->line().p1(),mouseEvent->scenePos());
            pathl.last()->setLine(newLine);
        }
        break;

    case InsertAutoArrow://TODO
        if(!endp && startp)
        {
            QPointF las=pathl.last()->line().p1();
            int xx=las.x(),yy=mouseEvent->scenePos().y();
            QLineF newLine1(las,QPointF(xx,yy));
            int len=pathl.length();
            pathl[len-1]->setLine(newLine1);
            QLineF newLine2(QPointF(xx,yy),mouseEvent->scenePos());
            pathl[len-2]->setLine(newLine2);
        }
        break;
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void ItemScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void ItemScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent){
    QMenu menu;

    menu.addAction(copyAction);
    menu.addAction(pasteAction);
    menu.addAction(cutAction);
    menu.addAction(undoAction);
    menu.addAction(redoAction);

    menu.exec(contextMenuEvent->screenPos());
}

void ItemScene::deleteSelectItem(){

    auto sele_item = selectedItems();
    for(auto item : sele_item)
    {
        if(!qgraphicsitem_cast<Arrow*>(item) &&
            !(item->type()>QGraphicsItem::UserType + 20) &&
            !qgraphicsitem_cast<TextItem*>(item) && !qgraphicsitem_cast<AutoArrow*>(item))
        {
            item->setSelected(false);
        }
        if(qgraphicsitem_cast<TextItem*>(item))
        {
            if(qgraphicsitem_cast<TextItem*>(item)->isInItem)
                item->setSelected(false);
        }
    }
    sele_item = selectedItems();
    for(auto item :sele_item)
    {
        if(qgraphicsitem_cast<Arrow*>(item))
        {
            Arrow* arr = qgraphicsitem_cast<Arrow*>(item);
            delete arr;//delete 会自动把arr移除scene
        }
        else if(qgraphicsitem_cast<AutoArrow*>(item))
        {
            AutoArrow* arr = qgraphicsitem_cast<AutoArrow*>(item);
            delete arr;//delete 会自动把arr移除scene
        }
    }
    sele_item = selectedItems();
    for(auto item:sele_item)
    {
        if(item->type() > QGraphicsItem::UserType + 20)
        {
            CustomBaseItem* del_item = (CustomBaseItem*)item;
            delete del_item;//delete 会自动把item移除
        }
        else if(qgraphicsitem_cast<TextItem*>(item))
        {
            TextItem* del_text = qgraphicsitem_cast<TextItem*>(item);
            if(del_text->isInItem)
                continue;
            removeItem(del_text);
            delete del_text;
        }
    }
}

void ItemScene::paste(){
    saveSceneState();
    QBuffer buffer(&copyBytes);
    QList<QGraphicsItem*> list = readFrom(buffer);
    if(list.size() == 0) return;
    QPoint globalMousePos = QCursor::pos(); // 获取全局鼠标位置
    QPoint viewMousePos = views().first()->mapFromGlobal(globalMousePos); // 将全局位置转换为视图坐标
    QPointF sceneMousePos = views().first()->mapToScene(viewMousePos); // 将视图坐标转换为场景坐标


    for(auto l : list)
    {
        QPointF pp = QPointF(l->scenePos() + QPointF(50,50));
        l->setPos(pp);
        addItem(l);
        l->setSelected(true);
        for(auto c : l->childItems()) c->setSelected(true);
    }
}

void ItemScene::copy(){
    QList<QGraphicsItem*> list = selectedItems();
    QBuffer buffer(&copyBytes);
    writeTo(buffer,list);
    for(auto l : list) l->setSelected(false);
}

void ItemScene::cut(){
    saveSceneState();
    QList<QGraphicsItem*> list = selectedItems();
    QBuffer buffer(&copyBytes);
    writeTo(buffer,list);

    deleteSelectItem();
}


void ItemScene::saveTo(){
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        tr("Save fct File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("FCT Files (*.fct)")); // 过滤器
    auto list = items();
    lastSaveFileName = fileName;
    QFile file(fileName);
    writeTo(file,list);
}
void ItemScene::save(){
    if(!lastSaveFileName.isEmpty())
    {
        QFile file(lastSaveFileName);
        auto list = items();
        writeTo(file,list);
    }
    else saveTo();
}
void ItemScene::openFile(){

    QString fileName = QFileDialog::getOpenFileName(
        nullptr, // 父窗口
        tr("Save fct File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("FCT Files (*.fct)")); // 过滤器
    QFile file(fileName);
    lastSaveFileName = fileName;
    for(auto i : items())
        i->setSelected(true);
    deleteSelectItem();
    auto list = readFrom(file);
    for(auto l : list)
        addItem(l);

}


void ItemScene::writeTo(QIODevice& file,QList<QGraphicsItem*> list){
    QDomDocument doc;

    // 创建 XML 声明
    QDomProcessingInstruction xmlDeclaration = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(xmlDeclaration);

    // 创建根元素
    QDomElement bound = doc.createElement("bound");
    doc.appendChild(bound);
    bound.setAttribute("height",height);
    bound.setAttribute("width",width);
    bound.setAttribute("path",lastSaveFileName);

    std::map<QGraphicsItem*,unsigned long long> itemMap;
    unsigned long long idx = 0;
    for(auto l : list)
    {
        if(l->type( )> QGraphicsItem::UserType + 20)//保存item
        {
            CustomBaseItem* cusItem = (CustomBaseItem*)l;
            QDomElement item = doc.createElement("item");
            itemMap[l] = idx;
            item.setAttribute("id",idx++);
            item.setAttribute("type",cusItem->type());
            item.setAttribute("text",cusItem->text.toPlainText());
            item.setAttribute("x",cusItem->scenePos().x());
            item.setAttribute("y",cusItem->scenePos().y());
            item.setAttribute("color",cusItem->myColor.rgba());
            item.setAttribute("textColor",cusItem->text.myColor.rgba());
            item.setAttribute("textSize",cusItem->text.defaultFont.pointSize());
            item.setAttribute("textFamily",cusItem->text.defaultFont.family());
            item.setAttribute("textBold",cusItem->text.defaultFont.bold());
            item.setAttribute("textItalic",cusItem->text.defaultFont.italic());
            item.setAttribute("textUnderline",cusItem->text.defaultFont.underline());
            bound.appendChild(item);
        }
        else if(qgraphicsitem_cast<TextItem*>(l))//保存text
        {
            TextItem* textitem = qgraphicsitem_cast<TextItem*>(l);
            if(textitem->isInItem)
                continue;
            QDomElement text = doc.createElement("text");
            text.setAttribute("text",textitem->toPlainText());
            text.setAttribute("x",textitem->scenePos().x());
            text.setAttribute("y",textitem->scenePos().y());
            text.setAttribute("textColor",textitem->myColor.rgba());
            text.setAttribute("textSize",textitem->defaultFont.pointSize());
            text.setAttribute("textFamily",textitem->defaultFont.family());
            text.setAttribute("textBold",textitem->defaultFont.bold());
            text.setAttribute("textItalic",textitem->defaultFont.italic());
            text.setAttribute("textUnderline",textitem->defaultFont.underline());
            bound.appendChild(text);
        }

    }
    for(auto l:list)
    {
        if(qgraphicsitem_cast<Arrow*>(l))
        {
            Arrow* arr = qgraphicsitem_cast<Arrow*>(l);
            QDomElement arrow = doc.createElement("arrow");

            if(itemMap.find(arr->startp->parentItem())!= itemMap.end())
            {
                unsigned long long id = itemMap[arr->startp->parentItem()];
                CustomBaseItem* parent = (CustomBaseItem*)(arr->startp->parentItem());
                int ndID = 0;
                for(auto p : parent->MagPoints)
                {
                    if(p == arr->startp)
                    {
                        break;
                    }
                    else ndID++;
                }
                arrow.setAttribute("startp",ndID);
                arrow.setAttribute("startItem",id);
            }else continue;
            if(itemMap.find(arr->endp->parentItem())!= itemMap.end())
            {
                unsigned long long id = itemMap[arr->endp->parentItem()];
                CustomBaseItem* parent = (CustomBaseItem*)(arr->endp->parentItem());
                int ndID = 0;
                for(auto p : parent->MagPoints)
                {
                    if(p == arr->endp)
                    {
                        break;
                    }
                    else ndID++;
                }
                arrow.setAttribute("endp",ndID);
                arrow.setAttribute("endItem",id);

            }else continue;

            for(auto p : arr->pathp)
            {
                QDomElement pathp = doc.createElement("pathp");
                pathp.setAttribute("y",p->scenePos().y());
                pathp.setAttribute("x",p->scenePos().x());
                arrow.appendChild(pathp);
            }
            arrow.setAttribute("color",arr->myColor.rgba());
            bound.appendChild(arrow);
        }
        else if(qgraphicsitem_cast<AutoArrow*>(l))
        {
            AutoArrow* arr = qgraphicsitem_cast<AutoArrow*>(l);
            QDomElement arrow = doc.createElement("autoArrow");

            if(itemMap.find(arr->startp->parentItem())!= itemMap.end())
            {
                unsigned long long id = itemMap[arr->startp->parentItem()];
                CustomBaseItem* parent = (CustomBaseItem*)(arr->startp->parentItem());
                int ndID = 0;
                for(auto p : parent->MagPoints)
                {
                    if(p == arr->startp)
                    {
                        break;
                    }
                    else ndID++;
                }
                arrow.setAttribute("startp",ndID);
                arrow.setAttribute("startItem",id);
            }else continue;
            if(itemMap.find(arr->endp->parentItem())!= itemMap.end())
            {
                unsigned long long id = itemMap[arr->endp->parentItem()];
                CustomBaseItem* parent = (CustomBaseItem*)(arr->endp->parentItem());
                int ndID = 0;
                for(auto p : parent->MagPoints)
                {
                    if(p == arr->endp)
                    {
                        break;
                    }
                    else ndID++;
                }
                arrow.setAttribute("endp",ndID);
                arrow.setAttribute("endItem",id);

            }else continue;

            for(auto p : arr->pathp)
            {
                QDomElement pathp = doc.createElement("pathp");
                pathp.setAttribute("y",p->scenePos().y());
                pathp.setAttribute("x",p->scenePos().x());
                arrow.appendChild(pathp);
            }
            arrow.setAttribute("color",arr->myColor.rgba());
            bound.appendChild(arrow);
        }
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
    } else {
        qWarning("Cannot open file for writing.");
    }
}

QList<QGraphicsItem*> ItemScene::readFrom(QIODevice& file)
{
    QDomDocument doc;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return QList<QGraphicsItem*>();
    }
    std::map<unsigned long long,CustomBaseItem*> itemMap;
    QXmlStreamReader xml(&file);
    QXmlStreamReader::TokenType token = xml.readNext();
    QXmlStreamAttributes atts;
    QList<ArrowPoint*> pathp;
    QList<QGraphicsItem*> new_items;
    if (token == QXmlStreamReader::StartDocument) {
        // 文档开始，通常不需要处理
    }
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if (xml.name().toString() == "bound") {
                // setSize(xml.attributes().value("width").toInt(),
                //         xml.attributes().value("height").toInt());
            } else if (xml.name().toString() == "item") {
                new_items.append(loadItem(xml.attributes(),itemMap));
            } else if (xml.name().toString() == "text") {
                new_items.append(loadText(xml.attributes()));
            }else if(xml.name().toString() == "arrow")
                atts = xml.attributes();          
            else if(xml.name().toString() == "autoArrow")
                atts = xml.attributes();
            else if(xml.name().toString() == "pathp"){
                pathp.append(new ArrowPoint(xml.attributes().value("x").toDouble(),
                                            xml.attributes().value("y").toDouble()));
            }
        }

        else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "arrow")
        {
            auto t_item = qgraphicsitem_cast<Arrow*>(loadArrow(atts,pathp,itemMap));
            if(t_item)//如果返回null，则不插入，并且释放内存
            {
                t_item->startp->addArrow(t_item);
                t_item->endp->addArrow(t_item);
                new_items.append(t_item);
                pathp.clear();
            }
            else {
                for(auto p : pathp)
                    delete p;
                pathp.clear();
            }
        }
        else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "autoArrow")
        {
            auto t_item = qgraphicsitem_cast<AutoArrow*>(loadArrow(atts,pathp,itemMap));
            if(t_item)//如果返回null，则不插入，并且释放内存
            {
                t_item->startp->addArrow(t_item);
                t_item->endp->addArrow(t_item);
                new_items.append(t_item);
                pathp.clear();
            }
            else {
                for(auto p : pathp)
                    delete p;
                pathp.clear();
            }
        }
    }
    // 检查是否有错误发生
    if (xml.hasError()) {
        qDebug() << "XML错误:" << xml.errorString();
    }
    file.close();
    return new_items;
}

QGraphicsItem* ItemScene::loadItem(QXmlStreamAttributes att,
                                   std::map<unsigned long long,CustomBaseItem*>& itemMap)
{

    CustomBaseItem* item = nullptr;
    int type  = att.value("type").toInt();
    switch (type) {
    case StartItem::Type:
        item = new StartItem();
        break;
    case DecisionItem::Type:
        item = new DecisionItem();
        break;
    case  ProcessItem::Type:
        item = new ProcessItem();
        break;
    case  Document::Type:
        item = new Document();
        break;
    case  EndItem::Type:
        item = new EndItem();
        break;
    case InnerConnecterItem::Type:
        item = new InnerConnecterItem();
        break;
    case OuterConnecterItem::Type:
        item = new OuterConnecterItem();
        break;
    case PredefineItem::Type:
        item = new PredefineItem();
        break;
    case CommentItem::Type:
        item = new CommentItem();
        break;
    case ioputItem::Type:
        item = new ioputItem();
        break;
    }
    if(!item)
        return nullptr;
    item->setPos(att.value("x").toDouble(),att.value("y").toDouble());
    item->myColor = QColor(att.value("color").toUInt());
    item->text.setPlainText(att.value("text").toString());
    item->text.myColor = QColor(att.value("textColor").toUInt());
    item->text.setDefaultTextColor(item->text.myColor);
    QFont font = QFont(att.value("textFamily").toString(),
                       att.value("textSize").toInt());
    if(att.value("textBold").toInt())
        font.setWeight(QFont::Bold);
    font.setItalic(att.value("textItalic").toInt());
    font.setUnderline(att.value("textUnderline").toInt());
    item->text.setFont(font);
    itemMap[att.value("id").toInt()] = item;
    item->text.updatePosition();
    return item;
}

QGraphicsItem* ItemScene::loadText(QXmlStreamAttributes att){
    TextItem* text = new TextItem();
    QFont font = QFont(att.value("textFamily").toString(),
                       att.value("textSize").toInt());
    if(att.value("textBold").toInt())
        font.setWeight(QFont::Bold);
    font.setItalic(att.value("textItalic").toInt());
    font.setUnderline(att.value("textUnderline").toInt());
    text->setFont(font);
    text->setPos(att.value("x").toDouble(),att.value("y").toDouble());
    text->setPlainText(att.value("text").toString());
    text->myColor = QColor(att.value("textColor").toUInt());
    text->setDefaultTextColor(text->myColor);
    return text;
}

QGraphicsItem* ItemScene::loadArrow(QXmlStreamAttributes att,QList<ArrowPoint*>pathp,
                                    std::map<unsigned long long,CustomBaseItem*> itemMap){
    int startpID = att.value("startp").toInt();
    int startItemID = att.value("startItem").toInt();
    int endpID = att.value("endp").toInt();
    int endItemID = att.value("endItem").toInt();
    MagPoint* startp = nullptr,*endp = nullptr;
    if(itemMap.find(startItemID)==itemMap.end() || itemMap.find(endItemID)==itemMap.end())
    {
        return nullptr;
    }
    int cnt = 0;
    for(auto p : itemMap[startItemID]->MagPoints)
    {
        if(cnt == startpID)
        {
            startp = p;
            break;
        }
        cnt++;
    }
    cnt = 0;
    for(auto p : itemMap[endItemID]->MagPoints)
    {
        if(cnt == endpID)
        {
            endp = p;
            break;
        }
        cnt++;
    }

    Arrow* arrow = new Arrow(startp,endp,pathp);
    arrow->myColor = att.value("color").toUInt();
    return arrow;
}

QGraphicsItem* ItemScene::loadAutoArrow(QXmlStreamAttributes att,QList<ArrowPoint*>pathp,
                                    std::map<unsigned long long,CustomBaseItem*> itemMap){
    int startpID = att.value("startp").toInt();
    int startItemID = att.value("startItem").toInt();
    int endpID = att.value("endp").toInt();
    int endItemID = att.value("endItem").toInt();
    MagPoint* startp = nullptr,*endp = nullptr;
    if(itemMap.find(startItemID)==itemMap.end() || itemMap.find(endItemID)==itemMap.end())
    {
        return nullptr;
    }
    int cnt = 0;
    for(auto p : itemMap[startItemID]->MagPoints)
    {
        if(cnt == startpID)
        {
            startp = p;
            break;
        }
        cnt++;
    }
    cnt = 0;
    for(auto p : itemMap[endItemID]->MagPoints)
    {
        if(cnt == endpID)
        {
            endp = p;
            break;
        }
        cnt++;
    }

    AutoArrow* arrow = new AutoArrow(startp,endp,pathp);
    arrow->myColor = att.value("color").toUInt();
    return arrow;
}

void ItemScene::saveSceneState(){
    auto list = items();
    QByteArray arr = QByteArray();
    QBuffer buffer(&arr);
    writeTo(buffer,list);
    while(!redoStack.isEmpty())
    {
        redoStack.pop();
    }
    undoStack.push(arr);
    if(undoStack.size()>20)
        undoStack.remove(0);
}
void ItemScene::redo(){

    if(redoStack.isEmpty()) return;
    qDebug()<<"redo";
    auto undo_list = items();
    QByteArray undo_arr = QByteArray();
    QBuffer undo_buffer(&undo_arr);
    writeTo(undo_buffer,undo_list);
    undoStack.push(undo_arr);

    QByteArray redo_arr = redoStack.pop();
    for(auto i : items())
    {
        i->setSelected(true);
    }
    deleteSelectItem();
    QBuffer redo_buffer(&redo_arr);
    auto redo_list = readFrom(redo_buffer);
    for(auto l : redo_list)
        addItem(l);
}
void ItemScene::undo(){
    if(undoStack.isEmpty())return;
    qDebug()<<"undo";
    auto redo_list = items();
    QByteArray redo_arr = QByteArray();
    QBuffer redo_buffer(&redo_arr);
    writeTo(redo_buffer,redo_list);
    redoStack.push(redo_arr);

    QByteArray undo_arr = undoStack.pop();
    for(auto i : items())
    {
        i->setSelected(true);
    }
    deleteSelectItem();
    QBuffer undo_buffer(&undo_arr);
    auto undo_list = readFrom(undo_buffer);
    for(auto l : undo_list)
        addItem(l);
}



void ItemScene::inputImage(){
    QString fileName = QFileDialog::getOpenFileName(
        nullptr, // 父窗口
        tr("Open image"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("")); // 过滤器
    addItem(new ImageItem(fileName));
}



bool ItemScene::onedge(int x,int y,CustomBaseItem* item)
{
    for(int i=1;i<item->polygon().size();i++)
    {
        QPointF las=item->polygon()[i-1];
        QPointF now=item->polygon()[i];
        int dx1=x-las.x(),dy1=y-las.y();
        int dx2=now.x()-las.x(),dy2=now.y()-las.y();
        if(dx1==0&&dx2==0) return true;
        if(dy1==0&&dy2==0) return true;
        if(dx1*dy2==dx2*dy1)
        {
            if(dx1*dy2!=0)
                return true;
        }
    }
    return false;
}
bool ItemScene::check2(int x,int y,QPointF u,QPointF v)
{
    QPointF now=QPointF(x,y);
    //if(x==u.x()||y==u.y()||x==v.x()||y==v.y()) return false;
    CustomBaseItem* t1,*t2;
    QList<QGraphicsItem*>list = items(u);
    // for(auto i:list)
    // {
    //     if(i->type() > QGraphicsItem::UserType + 20)
    //     {
    //         t1=(CustomBaseItem*)i;
    //         break;
    //     }
    // }
    // list = items(v);
    // for(auto i:list)
    // {
    //     if(i->type() > QGraphicsItem::UserType + 20)
    //     {
    //         t2=(CustomBaseItem*)i;
    //         break;
    //     }
    // }
    list = items(now);
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            //if(i==t1&&onedge(x,y,t1)) continue;
            //if(i==t2&&onedge(x,y,t2)) continue;
            // if(i==t1&&x==u.x()||y==u.y()) continue;
            // if(i==t2&&x==v.x()||y==v.y()) continue;
            return true;
            break;
        }
    }
    return false;
}
bool ItemScene::check(int x,int y,QPointF u,QPointF v)
{
    QPointF now=QPointF(x,y);
    //if(now==u||now==v) return false;
    if(x-10<=u.x()&&x+10>=u.x()&&y-10<=u.y()&&y+10>=u.y()) return false;
    if(x-10<=v.x()&&x+10>=v.x()&&y-10<=v.y()&&y+10>=v.y()) return false;
    // int xx=x,yy=y;
    // for(int ii=-0;ii<=0;ii++)
    // {
    //     for(int j=-0;j<=0;j++)
    //     {

    //         x=xx+ii;
    //         y=yy+j;
    QList<QGraphicsItem*>list = items(QPointF(x,y));
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            return true;
        }
    }
    x+=10;
    list = items(QPointF(x,y));
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            return true;
        }
    }
    y+=10;
    list = items(QPointF(x,y));
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            return true;
        }
    }
    x-=20;
    list = items(QPointF(x,y));
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            return true;
        }
    }
    y-=20;
    list = items(QPointF(x,y));
    for(auto i:list)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            return true;
        }
    }
    // }
    // }
    return false;
}
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
int whe[1300][1100];
QPointF q[2112341];
QPointF pre[1300][1100];
int tim=0,flag=0;
void ItemScene::dfs(QPointF u,QPointF s,QPointF t)
{
    if(u==t)
    {
        flag=1;
        return;
    }
    int id[4]={0,1,2,3};
    if(flag) return;
    if(t.x()<=u.x()&&t.y()>=u.y())
    {
        for(int i=0;i<=3;i++) id[i]=id[i];
    }
    if(t.y()>=u.y()&&t.x()>u.x())
    {
        // id={1,2,3,0};
        for(int i=0;i<=3;i++) id[i]=(id[i]+1)%4;
    }
    if(t.y()<u.y()&&t.x()>=u.x())
    {
        //id={2,3,0,1};
        for(int i=0;i<=3;i++) id[i]=(id[i]+2)%4;
    }
    if(t.y()<u.y()&&t.x()<u.x())
    {
        //id={3,0,1,2};
        for(int i=0;i<=3;i++) id[i]=(id[i]+3)%4;
    }
    for(int i=0;i<=3;i++)
    {
        int fx=u.x()+dx[id[i]];
        int fy=u.y()+dy[id[i]];
        if(fx<-600||fx>600||fy<-500||fy>500||check(fx,fy,s,t)||whe[fx+600][fy+500]==tim) continue;
        //if(tim==2)
        //qDebug()<<fx<<"   now "<<fy<<"   ";
        whe[fx+600][fy+500]=tim;
        pre[fx+600][fy+500]=u;
        dfs(QPointF(fx,fy),s,t)                               ;
    }
}
void  ItemScene::bfs(QPointF s,QPointF t,QPainterPath& pa)
{
    int l=1,r=0;
    flag=0;
    tim++;
    whe[int(s.x())+600][int(s.y())+500]=tim;
    dfs(s,s,t);
    qDebug()<<flag<<"hahaha";
    QPointF now=pre[int(t.x())+600][int(t.y())+500];
    std::vector<QPointF> ans;
    ans.clear();
    while(now!=s)
    {
        //pa.lineTo(now);
        ans.push_back(now);
        now=pre[int(now.x())+600][int(now.y())+500];
    }
    reverse(ans.begin(),ans.end());
    //qDebug()<<s.x()<<" qwe  "<<s.y()<<"  asd "<<t.x()<<"   zxc "<<t.y();
    for(int i=0;i<ans.size();)
    {
        //qDebug()<<p.x()<<"haha "<<p.y();
        l=i+1,r=ans.size()-1;
        while(l<r)
        {
            int mid=(l+r)/2;
            if((abs(ans[mid].x()-ans[i].x())==mid-i&&ans[mid].y()==ans[i].y())||(abs(ans[mid].y()-ans[i].y())==mid-i&&ans[mid].x()==ans[i].x())) l=mid+1;
            else r=mid;
        }
        pa.lineTo(ans[i]);
        pa.lineTo(ans[l-1]);
        i=l;
    }
}
void ItemScene::Check(QPointF s,QPointF t,QPainterPath& pa)
{
    for(int fy=std::min(s.y(),t.y());fy<=std::max(s.y(),t.y());fy++) if(!check2(s.x(),fy,s,t)){pa.lineTo(QPointF(s.x(),fy));}
    for(int fx=std::min(s.x(),t.x());fx<=std::max(s.x(),t.x());fx++) if(!check2(fx,t.y(),s,t)){QPointF(fx,t.y());}
}
