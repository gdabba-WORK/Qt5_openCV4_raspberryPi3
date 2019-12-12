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
    void on_btn_cam_clicked();
    void on_btn_record_clicked();
};
#endif // MAINWINDOW_HPP
