#include "storage_processor.hpp"

void Storage::run()
{
    cout << "Storage::run() excuted!" << endl;
    while(writer.isOpened());
    cout << "Storage::run() exit!" << endl;
}

Storage::Storage(QObject *parent)
    : QThread(parent)
{
    cout << "Storage Object Created!" << endl;
}

Storage::~Storage()
{
    cout << "Storage Object Deleted!" << endl;
}

void Storage::recorderOn()
{
    Size size(640, 480);
    int  fourcc = VideoWriter::fourcc('D', 'X', '5', '0');

    writer.open("video_file.avi", fourcc, 8, size);
    CV_Assert(writer.isOpened());
}

void Storage::recorderOff()
{
    writer.release();
    CV_Assert(!writer.isOpened());
}

//void Storage::record()
//{
//    writer << frame;
//}

void Storage::handleFrame(const QImage& result)
{
    Mat mat(result.height(), result.width(), CV_8UC3, (void *)result.constBits(), result.bytesPerLine());
    mat.copyTo(frame);
    writer << frame;    // Storage::record()¿Í °°´Ù
}
