#ifndef PEDESTRIANDETECTION_H
#define PEDESTRIANDETECTION_H
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class PedestrianDetection
{
public:
    PedestrianDetection();
    void detect(const Mat &frame, vector<Rect> &pedestrians);

private:
    HOGDescriptor hog;
};

#endif // PEDESTRIANDETECTION_H
