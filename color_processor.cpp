#include "color_processor.hpp"

void Color::run()
{
    cout << "Color::run() excuted!" << endl;
//    int step = 0;
    while(capture.isOpened())
    {
        display();
//        cout << ++step << "setps" << endl;
    }
}

Color::Color(QObject *parent)
    : QThread(parent),
      isRecord(false)
{
    cout << "Color Obejct Created!" << endl;
}

Color::~Color()
{
    cout << "Color Object deleted!" << endl;
}

Mat& Color::getFrame()
{
    return frame;
}

VideoCapture& Color::getCapture()
{
    return capture;
}

void Color::setFlag(enum category value)
{
    flag = value;
}

void Color::setIsRecord(bool value)
{
    isRecord = value;
}

void Color::cameraOn()
{
    if (!capture.isOpened())
    {
        capture.open(0);
//        capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
//        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
        cout << capture.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
        cout << capture.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
    }
    CV_Assert(capture.isOpened());
}
void Color::cameraOff()
{
    if (capture.isOpened())
        capture.release();
    CV_Assert(!capture.isOpened());
}

void Color::display()
{
    capture >> frame;
    if (!frame.empty())
    {
        if (flag == DEFAULT);
        else
        {
            splitToRGB();
        }
        QImage qimg(frame.data,
                    frame.cols,
                    frame.rows,
                    frame.step,
                    QImage::Format_RGB888);
        const QPixmap a = QPixmap::fromImage(qimg.rgbSwapped());

        emit pixmapReady(QPixmap::fromImage(qimg.rgbSwapped()));
        if (isRecord){
            emit frameReady(qimg.scaled(640, 480, Qt::KeepAspectRatio));
        }
    }
}

void Color::splitToRGB()
{
    //    double frame_rate = capture.get(CV_CAP_PROP_FPS);
    //    int delay = cvRound(1000 / frame_rate);
    Size_<double> video_size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT));

    Mat bgr[3], zero;
    zero = Mat::zeros(video_size, CV_8UC1);

    split(frame, bgr);
    switch (flag) {
    case BLUE :
        zero.copyTo(bgr[1]);
        zero.copyTo(bgr[2]);
        merge(bgr, 3, frame);
        break;
    case GREEN :
        zero.copyTo(bgr[0]);
        zero.copyTo(bgr[2]);
        merge(bgr, 3, frame);
        break;
    case RED :
        zero.copyTo(bgr[0]);
        zero.copyTo(bgr[1]);
        merge(bgr, 3, frame);
    }
}
