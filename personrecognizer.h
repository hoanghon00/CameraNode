#ifndef PERSONRECOGNIZER_H
#define PERSONRECOGNIZER_H

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/face/facerec.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

#define RECOGNIZE_THRESHOLD 81

class PersonRecognizer {
public:
    PersonRecognizer(const vector<Mat> &imgs, const vector<int> &labels);
    virtual ~PersonRecognizer();
    void recognize(const Mat &face, int &label, double &confidence) const;
private:
    Ptr<LBPHFaceRecognizer> _model;
    Size _faceSize;
};

#endif // PERSONRECOGNIZER_H
