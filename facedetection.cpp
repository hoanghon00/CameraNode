#include <iostream>
#include "opencv2/opencv.hpp"
#include "facedetection.h"

using namespace std;
using namespace cv;

#define REDUCE_SIZE	1

FaceDetection::FaceDetection(const string &cascadePath)
{
    if( !_cascade.load( cascadePath ) ){
        cerr << "--(!)Error loading face detection trainning file path\n" << cascadePath << endl;
        exit(EXIT_FAILURE);
    }
}

void FaceDetection::detectFaces(Mat &frame, vector<Rect> &res) {
	Mat frame_tmp;
#if REDUCE_SIZE
	/** Reduce size of image to reduce computation power */
	resize(frame, frame_tmp, Size(), 0.5, 0.5, INTER_AREA);
#else
	frame_tmp = frame.clone();
#endif
    cvtColor( frame_tmp, frame_tmp, CV_BGR2GRAY );
    equalizeHist( frame_tmp, frame_tmp );

    /*Detect faces*/
    _cascade.detectMultiScale( frame_tmp, res, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
#if REDUCE_SIZE
    for( size_t i = 0; i < res.size(); i++ ) {
		if (((res[i].x + res[i].width) * 2 <= frame.size().width) && ((res[i].y + res[i].height) * 2 <= frame.size().height)) {
			res[i].x = res[i].x * 2;
			res[i].y = res[i].y * 2;
			res[i].height = res[i].height * 2;
			res[i].width = res[i].width * 2;
		}
	}
#endif
}
