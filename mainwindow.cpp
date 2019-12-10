#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), proc(new Processor)
{
    cout << "Mainwindow constructor start!" << endl;
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);
//    ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
    connect(proc, &Processor::resultReady, this, &MainWindow::handleResult);
//    proc->start();
}

MainWindow::~MainWindow()
{
    cout << "Mainwindow destructor start!" << endl;
    delete ui;
    while ( proc->isRunning() ) {
        std::cout << "Thread proc is running" << std::endl;
        proc->cameraOff();
    }
    delete proc;
}

Processor* MainWindow::getProc()
{
    return proc;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(proc->getCapture().isOpened())
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Stop the video before closing the application!");
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void MainWindow::handleResult(const QPixmap& result)
{
    pixmap.setPixmap(result);
    ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
}

void MainWindow::on_btn_default_clicked()
{
//    qApp->processEvents();
    proc->setFlag(DEFAULT);
}

void MainWindow::on_btn_red_clicked()
{
    proc->setFlag(RED);
//    getProc().cameraOn();
//    getProc().splitToRGB(2);
//    Mat frame = getProc().getFrame();
//    while(!frame.empty())
//    {
//        QImage qimg(frame.data,
//                    frame.cols,
//                    frame.rows,
//                    frame.step,
//                    QImage::Format_RGB888);
//        pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
//        ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

//        qApp->processEvents();
//        getProc().splitToRGB(2);
//        getProc().getFrame().copyTo(frame);
//    }
}

void MainWindow::on_btn_green_clicked()
{
    proc->setFlag(GREEN);
}

void MainWindow::on_btn_blue_clicked()
{
    proc->setFlag(BLUE);
}

void MainWindow::on_btn_OnOff_clicked()
{
    if (ui->btn_OnOff->text().toStdString() == "CamOn")
    {
        proc->cameraOn();
        ui->btn_OnOff->setText("CamOff");
        proc->start();
    }
    else
    {
        proc->cameraOff();
        ui->btn_OnOff->setText("CamOn");
    }
}



