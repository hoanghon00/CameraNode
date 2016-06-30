#include "personrecognizer.h"

PersonRecognizer::PersonRecognizer(const vector<Mat> &imgs, const vector<int> &labels) {
    //all images are faces of the same person, so initialize the same label for all.
    _faceSize = Size(imgs[0].size().width, imgs[0].size().height);

    //build recognizer model:
    _model = createFisherFaceRecognizer();
    _model->setThreshold(RECOGNIZE_THRESHOLD);
    _model->train(imgs, labels);
}

PersonRecognizer::~PersonRecognizer() {}

void PersonRecognizer::recognize(const Mat &face, int &label, double &confidence) const {
    Mat gray;
    cvtColor(face, gray, CV_BGR2GRAY);
    resize(gray, gray, _faceSize);
    _model->predict(gray, label, confidence);
}
