#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "defs.h"
#include "facedetection.h"
#include "nose_detection.h"
#include "personrecognizer.h"
#include "pedestrian_detection.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

/*Function declaration*/
static void processDetectedFaces(Mat &frame, Mat &result, vector<Rect> &faces, PersonRecognizer &pr, NoseDetection &nd);
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels);

int main(int argc, char *argv[])
{
    if (argc < 4) {
        cout << "Wrong arguments" << endl;
        cout << "Syntax: filename face_cascade nose_cascade person_training_csv_filepath" << endl;
        return -1;
    }

	FaceDetection fd(argv[1]);
	NoseDetection nd(argv[2]);

	/* Read training and init Person Recognizer */
    vector<Mat>  training_set;
    vector<int> labels;
    read_csv(argv[3], training_set, labels);
    PersonRecognizer pr(training_set, labels);

	VideoCapture cap(0);
	if(!cap.isOpened()) {
        cerr << "Capture Device ID " << 0 << "cannot be opened." << endl;
        return -1;
    }

    Mat frame, original;
    vector<Rect> faces;

    for(;;) {
        cap >> frame;
        /* Clone the current frame */
        original = frame.clone();

		high_resolution_clock::time_point tp_start = high_resolution_clock::now();
		/* Detect face */
		fd.detectFaces(frame, faces);
		high_resolution_clock::time_point tp_end_detect = high_resolution_clock::now();
		processDetectedFaces(frame, original, faces, pr, nd);
		high_resolution_clock::time_point tp_end_reg = high_resolution_clock::now();
		duration<double, milli> detect_duration = tp_end_detect - tp_start;
		auto reg_duration = duration_cast<microseconds>( tp_end_reg - tp_end_detect ).count();
		auto total_duration = duration_cast<microseconds>( tp_end_reg - tp_start ).count();
		cout << "Dectect duration = " << detect_duration.count() << " ms, Reg duration = " << reg_duration << ", total duration = " << total_duration << endl;
		/* Show the result and write out the for streamer */
		VideoWriter outStream(OUT_FILE, OUT_FOURCC, OUT_FPS, original.size());
		if (outStream.isOpened()) {
			outStream.write(original);
		} else {
			cout << "Cannot write to file" << endl;
		}
#if APP_CONFIG_HOST_DISPLAY
		imshow("Camera Node", original);
		// And display it:
        char key = (char) waitKey(20);
        // Exit this loop on escape:
        if(key == 27)
            break;
#endif
    }
    return 0;
}

static void processDetectedFaces(Mat &frame, Mat &result, vector<Rect> &faces, PersonRecognizer &pr, NoseDetection &nd) {
    for( size_t i = 0; i < faces.size(); i++ ) {
        Mat face_img = frame( faces[i] );
#if 1
        /* Check if nose exist in detected face*/
        vector<Rect> nose;
        nd.detect(face_img, nose);

        if (nose.size() > 0)
#endif
        {
            Scalar color = NO_MATCH_COLOR;
            double confidence = 0;
            int label = -1;

            //try to recognize the face
            pr.recognize(face_img, label, confidence);
            cout << "Recognize with confidence: " << confidence << " and id: " << label << endl;
            if (confidence < RECOGNIZE_THRESHOLD) {
                color = MATCH_COLOR;
            }

            //draw detection image
            Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
            ellipse( result, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, color, 4, 8, 0 );
			putText(result, "Hello", Point( faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1, color);
        }
    }
}

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, ';');
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
			Mat training_img;
			training_img = imread(path, 0);
			if ( !training_img.data) {
				cout << "Could not open or find the training image at location: " << path << endl;
				exit(EXIT_FAILURE);
			}
            images.push_back(training_img);
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
