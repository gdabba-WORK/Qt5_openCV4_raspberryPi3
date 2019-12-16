#ifndef COLOR_PROCESSOR_HPP
#define COLOR_PROCESSOR_HPP

#include "includes.hpp"
using namespace cv;
using namespace std;

class Color : public QThread
{
    Q_OBJECT

private:
    VideoCapture capture;
    Mat frame, bgr[3], zero;
public:
    enum category flag;
    bool isRecord;

private:
    void run() override;

public:
    Color(QObject *parent = nullptr);
    ~Color() override;

    Mat& getFrame();
    VideoCapture& getCapture();

    void setFlag(enum category);
    void setIsRecord(bool);

    void cameraOn();
    void cameraOff();
    void display();
    void splitToRGB();

signals:
    void pixmapReady(const QPixmap& result);
    void frameReady(const QImage& result);

};
#endif // COLOR_PROCESSOR_HPP
