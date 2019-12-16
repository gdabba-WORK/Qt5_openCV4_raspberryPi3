#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "includes.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Color* color;
    Storage* storage;
    Adjust* adjust;
    QGraphicsPixmapItem pixmap;
    int prev1, prev2;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Color* getColor();


protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void handlePixmap(const QPixmap& result);

private slots:
    void on_btn_default_clicked();
    void on_btn_red_clicked();
    void on_btn_green_clicked();
    void on_btn_blue_clicked();
    void on_btn_redgreen_clicked();
    void on_btn_redblue_clicked();
    void on_btn_greenblue_clicked();
    void on_btn_cam_clicked();
    void on_btn_record_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalScrollBar_valueChanged(int value);
};
#endif // MAINWINDOW_HPP
