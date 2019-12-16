#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), color(new Color), storage(new Storage), adjust(new Adjust),
      prev1(0), prev2(0)
{
    cout << "Mainwindow constructor start!" << endl;
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    connect(color, &Color::pixmapReady, this, &MainWindow::handlePixmap);
    connect(color, &Color::frameReady, storage, &Storage::handleFrame);
//    connect(color, &Color::finished, color, &QObject::deleteLater);
//    connect(storage, &Storage::finished, storage, &QObject::deleteLater);
}

MainWindow::~MainWindow()
{
    cout << "Mainwindow destructor start!" << endl;
    delete ui;
    while ( color->isRunning() ) {
        std::cout << "Thread color is running" << std::endl;
        color->cameraOff();
    }
    delete color;
}

Color* MainWindow::getColor()
{
    return color;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(color->getCapture().isOpened())
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

void MainWindow::handlePixmap(const QPixmap& result)
{
    pixmap.setPixmap(result);
    ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
}

void MainWindow::on_btn_default_clicked()
{
//    qApp->processEvents();
    color->setFlag(DEFAULT);
}

void MainWindow::on_btn_red_clicked()
{
    color->setFlag(RED);
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
    color->setFlag(GREEN);
}

void MainWindow::on_btn_blue_clicked()
{
    color->setFlag(BLUE);
}

void MainWindow::on_btn_redgreen_clicked()
{
    color->setFlag(RED_GREEN);
}

void MainWindow::on_btn_redblue_clicked()
{
    color->setFlag(RED_BLUE);
}

void MainWindow::on_btn_greenblue_clicked()
{
    color->setFlag(GREEN_BLUE);
}

void MainWindow::on_btn_cam_clicked()
{
    if (ui->btn_cam->text().toStdString() == "Cam-On")
    {
        color->cameraOn();
        color->start();
        ui->btn_cam->setText("Cam-Off");
    }
    else if(ui->btn_record->text().toStdString() == "Record-On")
    {
        color->cameraOff();
        ui->btn_cam->setText("Cam-On");
    }
}

void MainWindow::on_btn_record_clicked()
{
    if (ui->btn_cam->text().toStdString() == "Cam-On")
        return;

    if (ui->btn_record->text().toStdString() == "Record-On")
    {
        storage->recorderOn();
        storage->start();
        color->setIsRecord(true);
        ui->btn_record->setText("Record-Off");
    }
    else
    {
        color->setIsRecord(false);
        storage->recorderOff();
        ui->btn_record->setText("Record-On");
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->graphicsView->rotate(value-prev1);
    prev1 = value;
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->graphicsView->move(value, 10);
}


