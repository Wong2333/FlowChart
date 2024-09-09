#include <QSvgGenerator>
#include <QFileDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QGraphicsView>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include "mainwindow.h"
#include "custombaseitem.h"
#include "itemscene.h"
#include "./ui_mainwindow.h"
#include "./items/startitem.h"
#include "./items/processitem.h"
#include "./items/document.h"
#include "./items/enditem.h"
#include "./items/innerconnecteritem.h"
#include "./items/decisionitem.h"
#include "./items/outerconnecteritem.h"
#include "./items/commentitem.h"
#include "./items/predefineitem.h"
#include "./items/ioputitem.h"

ItemScene* scene;
std::vector<ItemScene*> scenes;
QGraphicsView *graphicsView;

int cnt=0,now=1;
std::vector<TextItem*> a;
std::vector<int> L[100],R[100];
QString ss;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPage();
    this->setWindowIcon(QIcon(":/images/icon.png"));
    this->setWindowTitle("BlueChart--深藏Blue");

    // ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // scene = new ItemScene();
    // ((ItemScene*)scene)->copyAction = ui->copyAction_2;
    // ((ItemScene*)scene)->pasteAction = ui->pasteAction_2;
    // ((ItemScene*)scene)->cutAction = ui->cutAction;
    // ((ItemScene*)scene)->undoAction = ui->undoAction;
    // ((ItemScene*)scene)->redoAction = ui->redoAction;
    // ((ItemScene*)scene)->imageAction = ui->imageAction;
    // // 绑定到editToolBar
    // initMenuBar();
    // initToolBar();
    // ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenuBar()
{
    connect(ui->actionSVG, &QAction::triggered, this, &MainWindow::exportSVG);
    connect(ui->actionPDF, &QAction::triggered, this, &MainWindow::exportPDF);
    connect(ui->actionPNG, &QAction::triggered, this, &MainWindow::exportPNG);
    connect(ui->actionTIFF, &QAction::triggered, this, &MainWindow::exportTIFF);
    connect(ui->saveAction,&QAction::triggered,scene,&ItemScene::save);
    connect(ui->saveToAction,&QAction::triggered,scene,&ItemScene::saveTo);
    connect(ui->openAction,&QAction::triggered,scene,&ItemScene::openFile);
    connect(ui->imageAction,&QAction::triggered,scene,&ItemScene::inputImage);

    ui->saveAction->setShortcut(QKeySequence::Save);//设置快捷键
    ui->copyAction_2->setShortcut(QKeySequence::Copy);
    ui->pasteAction_2->setShortcut(QKeySequence::Paste);
    ui->cutAction->setShortcut(QKeySequence::Cut);
    ui->undoAction->setShortcut(QKeySequence::Undo);
    ui->redoAction->setShortcut(QKeySequence::Redo);

    connect(ui->copyAction_2,&QAction::triggered,scene,&ItemScene::copy);
    connect(ui->pasteAction_2,&QAction::triggered,scene,&ItemScene::paste);
    connect(ui->cutAction,&QAction::triggered,scene,&ItemScene::cut);
    connect(ui->undoAction,&QAction::triggered,scene,&ItemScene::undo);
    connect(ui->redoAction,&QAction::triggered,scene,&ItemScene::redo);
}

void MainWindow::initToolBar()
{
    // 绑定到editToolBar
    ui->editToolBar->addWidget(ui->deleteButton);
    ui->editToolBar->addWidget(ui->frontButton);
    ui->editToolBar->addWidget(ui->backButton);
    // 绑定到transformToolBar
    ui->transformToolBar ->addWidget(ui->leftButton);
    ui->transformToolBar ->addWidget(ui->rightButton);
    ui->transformToolBar ->addWidget(ui->biggerButton);
    ui->transformToolBar ->addWidget(ui->samllerButton);
    // 绑定到clickToolBar
    ui->clickToolBar ->addWidget(ui->clickButton);
    ui->clickToolBar->addWidget(ui->findButton);
    ui->clickToolBar ->addWidget(ui->percentBox);
    // 绑定到fontToolBar
    ui->fontToolBar ->addWidget(ui->fontComboBox);
    ui->fontToolBar ->addWidget(ui->selectSizeBox);
    ui->fontToolBar ->addWidget(ui->boldButton);
    ui->fontToolBar ->addWidget(ui->italicButton);
    ui->fontToolBar ->addWidget(ui->underlineButton);
    // 绑定到colorToolBar
    ui->colorToolBar ->addWidget(ui->colorButton);

    ui->deleteAction->setShortcut(QKeySequence::Delete);
    ui->deleteButton->setDefaultAction(ui->deleteAction);
    connect(ui->deleteAction, &QAction::triggered,
            [=]{
                ((ItemScene*)scene)->saveSceneState();
                scene->deleteSelectItem();
            });

    // 切换字体
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged,
            this, &MainWindow::handleFontChange);
    // 切换字号
    ui->selectSizeBox->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        ui->selectSizeBox->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    ui->selectSizeBox->setValidator(validator);
    connect(ui->selectSizeBox, &QComboBox::currentTextChanged,
            this, &MainWindow::handleFontChange);
    // 字体的加粗、斜体、下划线
    ui->boldButton->setCheckable(true);
    ui->boldButton->setChecked(false);
    ui->italicButton->setCheckable(true);
    ui->italicButton->setChecked(false);
    ui->underlineButton->setCheckable(true);
    ui->underlineButton->setChecked(false);
    connect(ui->boldButton,&QToolButton::clicked,this,&MainWindow::handleFontChange);
    connect(ui->italicButton,&QToolButton::clicked,this,&MainWindow::handleFontChange);
    connect(ui->underlineButton,&QToolButton::clicked,this,&MainWindow::handleFontChange);

    // 颜色列表
    ui->colorButton->setPopupMode(QToolButton::MenuButtonPopup);
    ui->colorButton->setMenu(createColorMenu());
    ui->colorButton->setIcon(createColorToolButtonIcon(":/images/floodfill.png", scene->currentColor));
    ui->colorButton->setAutoFillBackground(true);
    connect(ui->colorButton, &QToolButton::clicked,
            this, &MainWindow::on_colorButton_clicked);

    // 缩放画布
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    ui->percentBox->addItems(scales);
    ui->percentBox->setCurrentIndex(2);
    connect(ui->percentBox, &QComboBox::currentTextChanged,
            this, &MainWindow::sceneScaleChanged);
}

void MainWindow::initPage()
{
    scene = new ItemScene();

    ((ItemScene*)scene)->copyAction = ui->copyAction_2;
    ((ItemScene*)scene)->pasteAction = ui->pasteAction_2;
    ((ItemScene*)scene)->cutAction = ui->cutAction;
    ((ItemScene*)scene)->undoAction = ui->undoAction;
    ((ItemScene*)scene)->redoAction = ui->redoAction;
    ((ItemScene*)scene)->imageAction = ui->imageAction;
    initMenuBar();
    initToolBar();

    buttonLayout = new QHBoxLayout();

    QPushButton *add = new QPushButton("添加界面");
    buttonLayout->addWidget(add);
    connect(add,&QPushButton::clicked,this,&MainWindow::on_add_clicked);

    QPushButton *delete1 = new QPushButton("删除界面");
    buttonLayout->addWidget(delete1);
    connect(delete1,&QPushButton::clicked,this,&MainWindow::on_delete_clicked);

    firstButton = new QPushButton("主界面");
    buttonLayout->addWidget(firstButton);

    ui->verticalLayout->addLayout(buttonLayout);

    stackedWidget = new QStackedWidget();
    ui->verticalLayout->addWidget(stackedWidget);

    QWidget *homePage = new QWidget;
    homePage->resize(600,600);
    stackedWidget->addWidget(homePage);

    connect(firstButton,&QPushButton::clicked,[=](){
        scene = scenes[0];
        stackedWidget->setCurrentIndex(0);
        nowButton = firstButton;
    });

    pageNum = 2;
    graphicsView = new QGraphicsView(scene, stackedWidget->currentWidget());
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    scenes.push_back(scene);
}

void MainWindow::on_graphicsButton_1_clicked()
{
    scene->insertItem(new ProcessItem());
}

void MainWindow::on_graphicsButton_2_clicked()
{
    scene->insertArr();
}

void MainWindow::on_graphicsButton_3_clicked()
{
    scene->insertItem(new Document());
}

void MainWindow::on_graphicsButton_4_clicked()
{
    scene->insertItem(new StartItem());
}

void MainWindow::on_graphicsButton_5_clicked()
{
    scene->insertText(new TextItem());
}

void MainWindow::on_graphicsButton_6_clicked()
{
    scene->insertItem(new DecisionItem());
}

void MainWindow::exportSVG() {
    QSvgGenerator svgGenerator;
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        tr("Save SVG File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("SVG Files (*.svg)")); // 过滤器
    svgGenerator.setFileName(fileName); // 设置输出文件路径
    svgGenerator.setSize(QSize(1000, 1000)); // 设置 SVG 文件的大小
    svgGenerator.setTitle("My SVG"); // 设置 SVG 文件的标题
    svgGenerator.setDescription("This is a description of my SVG"); // 设置 SVG 文件的描述

    // 将场景渲染到 SVG 生成器
    QPainter painter(&svgGenerator);
    scene->render(&painter);
}

void MainWindow::exportPDF() {
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        tr("Save PDF File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("PDF Files (*.pdf)")); // 过滤器

    if (!fileName.isEmpty()) {
        QPdfWriter pdfWriter(fileName);
        pdfWriter.setPageSize(QPageSize::A4); // 设置页面大小为A4
        pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15)); // 设置页边距

        QPainter painter(&pdfWriter);
        scene->render(&painter); // 将场景渲染到PDF生成器
        painter.end(); // 结束绘画，确保所有内容都被写入PDF
    }
}

void MainWindow::exportPNG() {
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        tr("Save PNG File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("PNG Files (*.png)")); // 过滤器

    if (!fileName.isEmpty()) {
        QImage image(QSize(1000, 1000), QImage::Format_ARGB32_Premultiplied); // 创建一个QImage对象
        image.fill(Qt::transparent); // 设置背景为透明

        QPainter painter(&image); // 创建一个QPainter对象用于在image上绘制
        scene->render(&painter); // 将场景渲染到QImage
        painter.end(); // 结束绘画

        image.save(fileName); // 保存QImage为PNG文件
    }
}

void MainWindow::exportTIFF() {
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        tr("Save TIFF File"), // 对话框标题
        QDir::currentPath(), // 初始目录
        tr("TIFF Files (*.tif *.tiff)")); // 过滤器

    if (!fileName.isEmpty()) {
        QImage image(QSize(1000, 1000), QImage::Format_ARGB32_Premultiplied); // 创建一个QImage对象
        image.fill(Qt::transparent); // 设置背景为透明

        QPainter painter(&image); // 创建一个QPainter对象用于在image上绘制
        scene->render(&painter); // 将场景渲染到QImage
        painter.end(); // 结束绘画

        image.save(fileName, "TIFF"); // 保存QImage为TIFF文件
    }
}

// 管理字体
void MainWindow::handleFontChange()
{
    QFont font = ui->fontComboBox->currentFont();  // 字体
    font.setPointSize(ui->selectSizeBox->currentText().toInt());  // 字号
    font.setWeight(ui->boldButton->isChecked() ? QFont::Bold : QFont::Normal);  // 加粗
    font.setItalic(ui->italicButton->isChecked());  // 斜体
    font.setUnderline(ui->underlineButton->isChecked());  // 下划线
    scene->defaultFont = font;

    auto list = scene->selectedItems();
    for(auto item : list){
        // 设置文本框TextItem的字体
        if(qgraphicsitem_cast<TextItem*>(item)){
            TextItem* thisText = qgraphicsitem_cast<TextItem*>(item);
            thisText->defaultFont = font;
            scene->defaultFont = font;
            thisText->setFont(font);
            thisText->updatePosition();
        }
        // 设置图形CustomBaseItem中的字体
        else if(item->type() > QGraphicsItem::UserType + 20){
            CustomBaseItem* thisBaseItem = (CustomBaseItem*)item;
            TextItem* thisText = &thisBaseItem->text;
            thisText->defaultFont = font;
            scene->defaultFont = font;
            thisText->setFont(font);
            thisText->updatePosition();
        }
    }
}

// 管理颜色
QMenu *MainWindow::createColorMenu()
{
    QStringList names;
    names << tr("图形颜色") << tr("文本颜色") << tr("线条颜色");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < scene->mySceneColors.count(); ++i) {
        // 创建Action
        QAction *action = new QAction(names.at(i), this);
        action->setData(scene->mySceneColors.at(i));
        action->setIcon(createColorIcon(scene->mySceneColors.at(i)));
        connect(action, &QAction::triggered, [=]{
            // 从画盘中选择颜色
            QColor color = QColorDialog::getColor(Qt::white, this);
            if (color.isValid()){
                // 修改colorButton颜色
                scene->currentColor = color;
                ui->colorButton->setIcon(createColorToolButtonIcon(":/images/floodfill.png", scene->currentColor));
                // 修改菜单颜色
                scene->mySceneColors[i] = color;
                action->setData(scene->mySceneColors.at(i));
                action->setIcon(createColorIcon(scene->mySceneColors.at(i)));
                // 获取选中列表
                auto list = scene->selectedItems();
                if(names.at(i) == "图形颜色"){
                    scene->pair.first = "图形颜色";
                    scene->pair.second = color;
                    for(auto item : list){
                        // 设置图形CustomBaseItem的颜色
                        if(item->type() > QGraphicsItem::UserType + 20){
                            CustomBaseItem* thisBaseItem = (CustomBaseItem*)item;
                            thisBaseItem->myColor = color;
                            thisBaseItem->update();
                        }
                    }
                }
                else if(names.at(i) == "文本颜色"){
                    scene->pair.first = "文本颜色";
                    scene->pair.second = color;
                    for(auto item : list){
                        // 设置文本框TextItem的字体颜色
                        if(qgraphicsitem_cast<TextItem*>(item)){
                            TextItem* thisText = qgraphicsitem_cast<TextItem*>(item);
                            thisText->myColor = color;
                            thisText->setDefaultTextColor(color);
                        }
                        // 设置图形CustomBaseItem中的字体颜色
                        else if(item->type() > QGraphicsItem::UserType + 20){
                            CustomBaseItem* thisBaseItem = (CustomBaseItem*)item;
                            TextItem* thisText = &thisBaseItem->text;
                            thisText->myColor = color;
                            thisText->setDefaultTextColor(color);
                        }
                    }
                }
                else if(names.at(i) == "线条颜色"){
                    scene->pair.first = "线条颜色";
                    scene->pair.second = color;
                    for(auto item : list){
                        // 设置线条Arrow的颜色
                        if(qgraphicsitem_cast<Arrow*>(item)){
                            Arrow* thisArrow = qgraphicsitem_cast<Arrow*>(item);
                            thisArrow->myColor = color;
                            thisArrow->update();
                        }
                    }
                }
            }
        });
        colorMenu->addAction(action);
    }
    return colorMenu;
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

// colorButton的颜色
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = graphicsView->transform();
    graphicsView->resetTransform();
    graphicsView->translate(oldMatrix.dx(), oldMatrix.dy());
    graphicsView->scale(newScale, newScale);
}

void MainWindow::on_clickButton_clicked()
{
    scene->setMoveItem();
}



void MainWindow::on_backgroundButton_1_clicked()
{
    scene->setBackgroundBrush(QPixmap(":/images/vellum.png"));
}


void MainWindow::on_backgroundButton_2_clicked()
{
    scene->setBackgroundBrush(QPixmap(":/images/sandpaper.png"));
}


void MainWindow::on_backgroundButton_3_clicked()
{
    scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
}


void MainWindow::on_backgroundButton_4_clicked()
{
    scene->setBackgroundBrush(QPixmap(":/images/background4.png"));
}


void MainWindow::on_colorButton_clicked()
{
    auto list = scene->selectedItems();
    for(auto item : list){
        if(scene->pair.first == "图形颜色"){
            // 设置图形CustomBaseItem的颜色
            if(item->type() > QGraphicsItem::UserType + 20){
                CustomBaseItem* thisBaseItem = (CustomBaseItem*)item;
                thisBaseItem->myColor = scene->pair.second;
                thisBaseItem->update();
            }
        }
        else if(scene->pair.first == "文本颜色"){
            // 设置文本框TextItem的字体颜色
            if(qgraphicsitem_cast<TextItem*>(item)){
                TextItem* thisText = qgraphicsitem_cast<TextItem*>(item);
                thisText->myColor = scene->pair.second;
                thisText->setDefaultTextColor(scene->pair.second);
            }
            // 设置图形CustomBaseItem中的字体颜色
            else if(item->type() > QGraphicsItem::UserType + 20){
                CustomBaseItem* thisBaseItem = (CustomBaseItem*)item;
                TextItem* thisText = &thisBaseItem->text;
                thisText->myColor = scene->pair.second;
                thisText->setDefaultTextColor(scene->pair.second);
            }
        }
        else if(scene->pair.first == "线条颜色"){
            // 设置线条Arrow的颜色
            if(qgraphicsitem_cast<Arrow*>(item)){
                Arrow* thisArrow = qgraphicsitem_cast<Arrow*>(item);
                thisArrow->myColor = scene->pair.second;
                thisArrow->update();
            }
        }
    }
}


void MainWindow::on_frontButton_clicked()
{
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(qgraphicsitem_cast<Arrow*>(i))
            continue;
        i->setZValue(i->zValue()+1);
    }
}


void MainWindow::on_backButton_clicked()
{
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(qgraphicsitem_cast<Arrow*>(i))
            continue;
        i->setZValue(i->zValue()-1);
    }
}


void MainWindow::on_leftButton_clicked()
{
    ((ItemScene*)scene)->saveSceneState();
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->doRotation(-10);
        }
    }
}


void MainWindow::on_rightButton_clicked()
{
    ((ItemScene*)scene)->saveSceneState();
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->doRotation(10);
        }
    }
}


void MainWindow::on_biggerButton_clicked()
{
    ((ItemScene*)scene)->saveSceneState();
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->doSize(1.1,1.1);
        }
    }
}


void MainWindow::on_samllerButton_clicked()
{
    ((ItemScene*)scene)->saveSceneState();
    auto items = scene->selectedItems();
    for(auto i : items)
    {
        if(i->type() > QGraphicsItem::UserType + 20)
        {
            ((CustomBaseItem*)i)->doSize(1/1.1,1/1.1);
        }
    }
}

void MainWindow::on_findButton_clicked()
{
    // 创建自定义 QDialog
    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/images/icon.png"));
    dialog->setWindowTitle("文字查找替换");
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // 添加编辑框
    QLineEdit *searchEdit = new QLineEdit(dialog);
    searchEdit->setPlaceholderText("搜索内容...");
    connect(searchEdit,&QLineEdit::textChanged,[=]{
        cnt=0,now=1;
        a.clear();
        for(int i=0;i<=50;i++) L[i].clear(),R[i].clear();
        for(auto p:scene->items())
        {
            if(qgraphicsitem_cast<TextItem*>(p)){
                TextItem*textItem = qgraphicsitem_cast<TextItem*>(p);
                textItem->LowText(0,textItem->toPlainText().size());
            }
        }
        QString s2=searchEdit->text();
        int n,m,pi[2000];
        s2=" "+s2;
        m=s2.size();
        m--;
        qDebug()<<"asdasdasd"<<m;
        int j=0;
        for(int i=0;i<=100;i++) pi[i]=0;
        if(m>1)
            for(int i=2;i<=m;i++)
            {
                while(s2[j+1]!=s2[i]&&j) j=pi[j];
                if(s2[j+1]==s2[i])
                {
                    j++;
                }
                pi[i]=j;
            }
        qDebug()<<s2;
        for(auto p:scene->items())
        {
            if(qgraphicsitem_cast<TextItem*>(p)){
                TextItem*textItem = qgraphicsitem_cast<TextItem*>(p);
                QString s1=textItem->toPlainText();
                s1=" "+s1;
                n=s1.size();
                n--;
                qDebug()<<s1;
                j=0;
                int flag=0;
                std::vector<int> l,r;
                if(m>0)
                    for(int i=1;i<=n;i++)
                    {
                        while(s2[j+1]!=s1[i]&&j) j=pi[j];
                        if(s2[j+1]==s1[i])
                        {
                            j++;
                            if(j==m)
                            {
                                if(!flag)
                                {
                                    a.push_back(textItem);
                                    cnt++;
                                    flag=1;
                                }
                                //cout<<i-j+1<<"\n";
                                L[cnt-1].push_back(i-j);
                                R[cnt-1].push_back(i);
                                l.push_back(i-j+1);
                                r.push_back(i);
                                j=pi[j];
                            }
                        }
                    }

                for(int i=0;i<l.size();i++)
                {
                    qDebug()<<l[i]-1<<" "<<r[i];
                    textItem->HighText(l[i]-1,r[i]);
                }
            }
        }
    });
    layout->addWidget(searchEdit);

    QLineEdit *replaceEdit = new QLineEdit(dialog);
    replaceEdit->setPlaceholderText("替换内容...");
    layout->addWidget(replaceEdit);
    connect(replaceEdit,&QLineEdit::textChanged,[=]{
        ss=replaceEdit->text();
    });

    //qDebug()<<ss<<"asdsasds ";
    QHBoxLayout *buttonLayout = new QHBoxLayout(dialog);
    layout->addLayout(buttonLayout);

    // 添加按钮
    QPushButton *lastButton = new QPushButton("查找上一个", dialog);
    buttonLayout->addWidget(lastButton);
    connect(lastButton,&QToolButton::clicked,[=]{
        for(int i=0;i<cnt;i++)
        {
            for(int j=0;j<L[i].size();j++)
            {
                a[i]->HighText(L[i][j],R[i][j]);
            }
        }
        now--;
        if(now==-1) now=cnt-1;
        for(int i=0;i<L[now].size();i++)
        {
            qDebug()<<now<<"shangyige: "<<L[now][i]<<" "<<R[now][i];
            a[now]->HighTextExtra(L[now][i],R[now][i]);
        }
    });
    QPushButton *nextButton = new QPushButton("查找下一个", dialog);
    buttonLayout->addWidget(nextButton);
    connect(nextButton,&QToolButton::clicked,[=]{
        for(int i=0;i<cnt;i++)
        {
            for(int j=0;j<L[i].size();j++)
            {
                a[i]->HighText(L[i][j],R[i][j]);
            }
        }
        now++;
        if(now==cnt) now=0;
        for(int i=0;i<L[now].size();i++)
        {
            qDebug()<<now<<"shangyige: "<<L[now][i]<<" "<<R[now][i];
            a[now]->HighTextExtra(L[now][i],R[now][i]);
        }
    });
    buttonLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QPushButton *searchButton = new QPushButton("替换全部", dialog);
    buttonLayout->addWidget(searchButton);
    connect(searchButton,&QToolButton::clicked,[=]{
        int whe[123];
        for(int i=0;i<cnt;i++)
        {
            QString as=a[i]->toPlainText();
            QString nows="";
            for(int j=0;j<as.size();j++) whe[j]=0;
            for(int j=0;j<L[i].size();j++)
            {
                for(int k=L[i][j];k<R[i][j];k++)
                {
                    whe[k]=1;
                    if(k==R[i][j]-1)
                        whe[k]=2;
                }
            }
            int hah=0;
            for(int j=0;j<as.size();j++)
            {
                if(!whe[j])
                {
                    nows+=as[j];
                    hah=0;
                }
                else
                {
                    if(!hah)
                    {
                        qDebug()<<ss<<"nowsnows ";
                        nows+=ss;
                    }
                    hah=1;
                    if(whe[j]==2) hah=0;
                }
            }
            a[i]->setPlainText(nows);
        }
        QString asd=searchEdit->text(),qwe;
        qwe=asd;
        asd+=" ";
        searchEdit->setText(asd);
        searchEdit->setText(qwe);
    });
    QPushButton *replaceButton = new QPushButton("替换", dialog);
    buttonLayout->addWidget(replaceButton);
    connect(replaceButton,&QToolButton::clicked,[=]{
        int whe[123];
        QString as=a[now]->toPlainText();
        QString nows="";
        for(int j=0;j<as.size();j++) whe[j]=0;
        for(int j=0;j<L[now].size();j++)
        {
            for(int k=L[now][j];k<R[now][j];k++)
            {
                whe[k]=1;
                if(k==R[now][j]-1)
                    whe[k]=2;
            }
        }
        int hah=0;
        for(int j=0;j<as.size();j++)
        {
            if(!whe[j])
            {
                nows+=as[j];
                hah=0;
            }
            else
            {
                if(!hah)
                {
                    qDebug()<<ss<<"nowsnows ";
                    nows+=ss;
                }
                hah=1;
                if(whe[j]==2) hah=0;
            }
        }
        a[now]->setPlainText(nows);

        QString asd=searchEdit->text(),qwe;
        qwe=asd;
        asd+=" ";
        searchEdit->setText(asd);
        searchEdit->setText(qwe);
    });
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // 添加标签
    QLabel *advancedLabel = new QLabel("高级查找", dialog);
    layout->addWidget(advancedLabel);

    // 添加一组可多选的复选框
    QCheckBox *checkBox1 = new QCheckBox("忽略空格", dialog);
    QCheckBox *checkBox2 = new QCheckBox("忽略引号", dialog);
    QCheckBox *checkBox3 = new QCheckBox("忽略换行", dialog);

    // 将复选框添加到布局中
    layout->addWidget(checkBox1);
    layout->addWidget(checkBox2);
    layout->addWidget(checkBox3);

    // 设置样式表
    QString styleSheet = R"(
    QDialog {
        background-color: #f0f0f0;
    }
    QLineEdit {
        border: 1px solid #ccc;
        border-radius: 5px;
        padding: 5px;
    }
    QLabel {
        font-weight: bold;
        font-size: 12pt;
    }
    QCheckBox {
        margin: 5px;
    }
    )";

    // 应用样式表
    dialog->setStyleSheet(styleSheet);
    dialog->setLayout(layout);
    dialog->exec();
    for(auto p:scene->items())
    {
        if(qgraphicsitem_cast<TextItem*>(p)){
            TextItem*textItem = qgraphicsitem_cast<TextItem*>(p);
            textItem->LowText(0,textItem->toPlainText().size());
        }
    }
}

void MainWindow::on_graphicsButton_7_clicked()
{
    scene->insertItem(new OuterConnecterItem());
}


void MainWindow::on_graphicsButton_11_clicked()
{
    scene->insertItem(new EndItem());
}


void MainWindow::on_graphicsButton_10_clicked()
{
    scene->insertItem(new InnerConnecterItem());
}


void MainWindow::on_graphicsButton_8_clicked()
{
    scene->insertItem(new CommentItem());
}


void MainWindow::on_graphicsButton_9_clicked()
{
    scene->insertItem(new PredefineItem());
}


void MainWindow::on_graphicsButton_12_clicked()
{
    scene->insertAutoArrow();
}


void MainWindow::on_template_1_clicked()
{

    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/images/icon.png"));
    dialog->setWindowTitle("循环流程图");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap(":/images/template1.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setPixmap(pixmap.scaled(dialog->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *textLabel = new QLabel;
    textLabel->setText("循环流程图");
    textLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(textLabel);
    QString styleSheet = R"(
    QLabel {
        font-weight: bold;
        font-size: 12pt;
    }
    )";
    dialog->setStyleSheet(styleSheet);

    QHBoxLayout *buttonLayout = new QHBoxLayout(dialog);
    layout->addLayout(buttonLayout);
    QPushButton *cancelButton = new QPushButton("取消", dialog);
    buttonLayout->addWidget(cancelButton);
    QPushButton *sureButton = new QPushButton("确定", dialog);
    buttonLayout->addWidget(sureButton);


    connect(cancelButton,&QToolButton::clicked,[=]{
        dialog->close();
    });

    connect(sureButton,&QToolButton::clicked,[=]{
        for(auto i : scene->items())
            i->setSelected(true);
        scene->deleteSelectItem();
        QFile file = QFile(":/images/template1.fct");
        auto list = scene->readFrom(file);
        for(auto l : list)
            scene->addItem(l);
        dialog->close();
    });

    dialog->setLayout(layout);
    dialog->resize(400, 300);
    dialog->exec();
}


void MainWindow::on_template_2_clicked()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/images/icon.png"));
    dialog->setWindowTitle("分支流程图");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap(":/images/template2.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setPixmap(pixmap.scaled(dialog->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *textLabel = new QLabel;
    textLabel->setText("分支流程图");
    textLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(textLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout(dialog);
    layout->addLayout(buttonLayout);
    QPushButton *cancelButton = new QPushButton("取消", dialog);
    buttonLayout->addWidget(cancelButton);
    QPushButton *sureButton = new QPushButton("确定", dialog);
    buttonLayout->addWidget(sureButton);

    connect(cancelButton,&QToolButton::clicked,[=]{
        dialog->close();
    });

    connect(sureButton,&QToolButton::clicked,[=]{
        for(auto i : scene->items())
            i->setSelected(true);
        scene->deleteSelectItem();
        QFile file = QFile(":/images/template2.fct");
        auto list = scene->readFrom(file);
        for(auto l : list)
            scene->addItem(l);
        dialog->close();
    });
    QString styleSheet = R"(
    QLabel {
        font-weight: bold;
        font-size: 12pt;
    }
    )";
    dialog->setStyleSheet(styleSheet);
    dialog->setLayout(layout);
    dialog->resize(400, 300);
    dialog->exec();
}


void MainWindow::on_template_3_clicked()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/images/icon.png"));
    dialog->setWindowTitle("多条件流程图");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap(":/images/template3.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setPixmap(pixmap.scaled(dialog->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *textLabel = new QLabel;
    textLabel->setText("多条件流程图");
    textLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(textLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout(dialog);
    layout->addLayout(buttonLayout);
    QPushButton *cancelButton = new QPushButton("取消", dialog);
    buttonLayout->addWidget(cancelButton);
    QPushButton *sureButton = new QPushButton("确定", dialog);
    buttonLayout->addWidget(sureButton);

    connect(cancelButton,&QToolButton::clicked,[=]{
        dialog->close();
    });

    connect(sureButton,&QToolButton::clicked,[=]{
        for(auto i : scene->items())
            i->setSelected(true);
        scene->deleteSelectItem();
        QFile file = QFile(":/images/template3.fct");
        auto list = scene->readFrom(file);
        for(auto l : list)
            scene->addItem(l);
        dialog->close();
    });
    QString styleSheet = R"(
    QLabel {
        font-weight: bold;
        font-size: 12pt;
    }
    )";
    dialog->setStyleSheet(styleSheet);
    dialog->setLayout(layout);
    dialog->resize(400, 300);
    dialog->exec();
}

void MainWindow::on_add_clicked()
{
    QPushButton *pushButton = new QPushButton("界面" + QString::number(pageNum));
    buttonLayout->addWidget(pushButton);

    QWidget *thisPage = new QWidget;
    thisPage->resize(600,600);
    stackedWidget->addWidget(thisPage);

    ItemScene *thisScene = new ItemScene();
    scenes.push_back(thisScene);

    // QGraphicsView *view = new QGraphicsView(thisScene,thisPage);
    // graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    int thisNum = pageNum - 1;
    connect(pushButton,&QPushButton::clicked,[=](){
        scene = scenes[thisNum];
        QGraphicsView *view = new QGraphicsView(thisScene,thisPage);
        view->setDragMode(QGraphicsView::RubberBandDrag);
        stackedWidget->setCurrentIndex(thisNum);
        nowButton = pushButton;
    });

    pageNum++;
}

void MainWindow::on_delete_clicked(){
    if(nowButton != firstButton){
        buttonLayout->removeWidget(nowButton);
        delete nowButton;
        stackedWidget->setCurrentIndex(0);
        nowButton = firstButton;
    }else{
        QMessageBox::warning(this, "警报！", "不能删除主界面", QMessageBox::Yes);
    }
}

void MainWindow::on_graphicsButton_13_clicked()
{
    scene->insertItem(new ioputItem());
}

