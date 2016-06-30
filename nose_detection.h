#ifndef NOSEDETECTION_H
#define NOSEDETECTION_H
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class NoseDetection
{
public:
    NoseDetection(const string &cascadePath);
    void detect(const Mat &frame, vector<Rect> &noseRects);

private:
    CascadeClassifier _cascade;
    bool _isValidCascade;
};

#endif // NOSEDETECTION_H
