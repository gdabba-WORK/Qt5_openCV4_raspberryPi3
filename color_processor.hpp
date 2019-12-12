#ifndef IMAGEPROCESSING_HPP
#define IMAGEPROCESSING_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/hal/interface.h>
#include <QThread>
#include <QObject>
#include <QMainWindow>
#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include "macro_types.hpp"
#include <QString>

using namespace cv;
using namespace std;

class Processor : public QThread
{
    Q_OBJECT

private:
    VideoCapture capture;
    VideoWriter  writer;
    Mat frame;
    enum category flag;

private:
    void run() override;

public:
    Processor(QObject *parent = nullptr);
    ~Processor() override;

    Mat& getFrame();
    VideoCapture& getCapture();
    VideoWriter& getWriter();

    void setFlag(enum category);
    void cameraOn();
    void cameraOff();
    void display();
    void splitToRGB();
    void record();

signals:
    void resultReady(const QPixmap& result);

};
#endif // IMAGEPROCESSING_HPP
