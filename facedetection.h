#ifndef FACEDETECTION_H
#define FACEDETECTION_H
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class FaceDetection
{
public:
    FaceDetection(const string &cascadePath);
    void detectFaces(Mat &frame, vector<Rect> &res);

private:
    CascadeClassifier _cascade;
    bool _isValidCascade;
};

#endif // FACEDETECTION_H
