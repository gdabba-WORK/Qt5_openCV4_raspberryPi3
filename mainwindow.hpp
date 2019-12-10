#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "processor.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Processor* proc;
    QGraphicsPixmapItem pixmap;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Processor* getProc();


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void handleResult(const QPixmap& result);

private slots:
    void on_btn_default_clicked();
    void on_btn_red_clicked();
    void on_btn_green_clicked();
    void on_btn_blue_clicked();
    void on_btn_OnOff_clicked();
};
#endif // MAINWINDOW_H
