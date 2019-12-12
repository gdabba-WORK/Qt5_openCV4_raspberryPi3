#include "processor.hpp"

Processor::Processor(QObject *parent)
    : QThread(parent)
{
    cout << "Processor Obejct Created!" << endl;
}

Processor::~Processor()
{
    cout << "Processor Object deleted!" << endl;
}

void Processor::run()
{
    cout << "Processing::run() excuted!" << endl;
    int step = 0;
    CV_Assert(capture.isOpened());

    while (capture.isOpened())
    {
        display();
        cout << ++step << "setps" << endl;
    }
}

Mat& Processor::getFrame()
{
    return frame;
}

VideoCapture& Processor::getCapture()
{
    return capture;
}

VideoWriter& Processor::getWriter()
{
    return writer;
}

void Processor::display()
{
//    capture.set(CAP_PROP_FRAME_WIDTH, 640);
//    capture.set(CAP_PROP_FRAME_HEIGHT, 360);
    capture.read(frame);
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

        emit resultReady(QPixmap::fromImage(qimg.rgbSwapped()));
    }
}

void Processor::setFlag(enum category num)
{
    flag = num;
}

void Processor::cameraOn()
{
    if (!capture.isOpened())
    {
        capture.open(0);
//        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        cout << capture.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
        cout << capture.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
    }
}
void Processor::cameraOff()
{
    if (capture.isOpened())
        capture.release();
}

void Processor::splitToRGB()
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

void Processor::record()
{
    CV_Assert(capture.isOpened());
    double frame_rate = capture.get(CV_CAP_PROP_FPS);
    int delay = cvRound(1000 / frame_rate);
    Size size(640, 360);
    int  fourcc = VideoWriter::fourcc('D', 'X', '5', '0');

    capture.set(CAP_PROP_FRAME_WIDTH, size.width);
    capture.set(CAP_PROP_FRAME_HEIGHT, size.height);


    writer.open("video_file.avi", fourcc, frame_rate, size);
    CV_Assert(writer.isOpened());


    while(true) {
        capture >> frame;
        writer << frame;
        //        imshow("RECORD", frame);
        if (waitKey(delay) >= 0) break;
    }
}
