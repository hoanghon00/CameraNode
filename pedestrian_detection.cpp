#include "pedestrian_detection.h"

PedestrianDetection::PedestrianDetection() {
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

void PedestrianDetection::detect(const Mat &frame, vector<Rect> &pedestrians) {
    hog.detectMultiScale(frame, pedestrians);
}
