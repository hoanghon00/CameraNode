#include <iostream>
#include "opencv2/opencv.hpp"
#include "facedetection.h"

using namespace std;
using namespace cv;

FaceDetection::FaceDetection(const string &cascadePath)
{
    if( !_cascade.load( cascadePath ) ){
        cerr << "--(!)Error loading face detection trainning file path\n" << cascadePath << endl;
        _isValidCascade = false;
    } else {
        _isValidCascade = true;
    }
}

void FaceDetection::detectFaces(Mat &frame, vector<Rect> &res) {
    Mat frame_gray;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    /*Detect faces*/
    if (_isValidCascade) {
        _cascade.detectMultiScale( frame_gray, res, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    }
}
