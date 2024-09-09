#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exportSVG();
    void exportPDF();
    void exportPNG();
    void exportTIFF();
    void handleFontChange();
    void colorBoxChanged();
    QMenu *createColorMenu();
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);
    void sceneScaleChanged(const QString &scale);
    int pageNum;
    QStackedWidget *stackedWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *nowButton;
    QPushButton *firstButton;

private slots:
    void on_graphicsButton_1_clicked();
    void on_graphicsButton_2_clicked();
    void on_graphicsButton_3_clicked();
    void on_graphicsButton_4_clicked();
    void on_graphicsButton_5_clicked();
    void on_graphicsButton_6_clicked();

    void on_clickButton_clicked();

    void on_backgroundButton_1_clicked();

    void on_backgroundButton_2_clicked();

    void on_backgroundButton_3_clicked();

    void on_backgroundButton_4_clicked();

    void on_colorButton_clicked();

    void on_frontButton_clicked();

    void on_backButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_biggerButton_clicked();

    void on_samllerButton_clicked();

    void on_findButton_clicked();

    void on_graphicsButton_7_clicked();

    void on_graphicsButton_11_clicked();

    void on_graphicsButton_10_clicked();

    void on_graphicsButton_8_clicked();

    void on_graphicsButton_9_clicked();

    void on_graphicsButton_12_clicked();

    void on_template_1_clicked();

    void on_template_2_clicked();

    void on_template_3_clicked();

    void on_add_clicked();
    void on_delete_clicked();
    void initPage();

    void on_graphicsButton_13_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup* pointerTypeGroup;
    void initToolBar();
    void initMenuBar();
};
#endif // MAINWINDOW_H
