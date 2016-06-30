#include "nose_detection.h"

NoseDetection::NoseDetection(const string &cascadePath) {
    if( !_cascade.load( cascadePath ) ){
        cerr << "--(!)Error loading face detection trainning file path\n" << cascadePath << endl;
        _isValidCascade = false;
    } else {
        _isValidCascade = true;
    }
}

void NoseDetection::detect(const Mat &frame, vector<Rect> &noseRects) {
    Mat frame_gray;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    /*Detect noses*/
    if (_isValidCascade) {
        //_cascade.detectMultiScale( frame_gray, noseRects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        _cascade.detectMultiScale( frame_gray, noseRects, 1.3, 3);
    }
}
