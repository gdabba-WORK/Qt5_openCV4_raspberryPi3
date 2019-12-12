#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "includes.hpp"
using namespace cv;
using namespace std;

class Storage : public QThread
{
    Q_OBJECT
private:
    VideoWriter writer;
    Mat frame;

private:
    void run() override;

public:
    Storage(QObject *parent = nullptr);
    ~Storage() override;
    void recorderOn();
    void recorderOff();
//    void record();

public slots:
    void handleFrame(const QImage& result);
};

#endif // STORAGE_HPP
