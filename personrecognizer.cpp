#include "personrecognizer.h"

PersonRecognizer::PersonRecognizer(const vector<Mat> &imgs, const vector<int> &labels) {
    _model = createLBPHFaceRecognizer();
    _model->setThreshold(RECOGNIZE_THRESHOLD);
    _model->train(imgs, labels);
}

PersonRecognizer::~PersonRecognizer() {}

void PersonRecognizer::recognize(const Mat &face, int &label, double &confidence) const {
    Mat gray;
    cvtColor(face, gray, CV_BGR2GRAY);
    _model->predict(gray, label, confidence);
}
