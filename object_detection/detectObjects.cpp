#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

int main() {
  // open the positive sample images
  std::vector<cv::Mat> referenceImages;
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop00.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop01.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop02.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop03.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop04.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop05.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop06.png"));
  referenceImages.emplace_back(cv::imread("../images/stopSamples/stop07.png"));

  cv::Mat positveImages(2 * referenceImages[0].rows,
                        4 * referenceImages[0].cols, CV_8UC3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      std::cout << "number " << i * 2 + j << std::endl;
      referenceImages[i * 2 + j].copyTo(positveImages(cv::Rect(
          j * referenceImages[i * 2 + j].cols, // 0 1 2 3
          i * referenceImages[i * 2 + j].rows, referenceImages[i * 2 + j].cols,
          referenceImages[i * 2 + j].rows)));
    }

  cv::imshow("Positive samples", positveImages);

  cv::Mat negative = cv::imread("../images/stopSamples/bg01.jpg");
  cv::resize(negative, negative, cv::Size(), 0.33, 0.33);
  cv::imshow("One negative sample", negative);

  cv::Mat inputImage = cv::imread("../images/stopSamples/stop9.jpg");
  cv::resize(inputImage, inputImage, cv::Size(), 0.5, 0.5);

  cv::CascadeClassifier cascade;
  if (!cascade.load("../images/stopSamples/classifier/cascade.xml")) {
    std::cout << "Error when loading the cascade classifier!" << std::endl;
    return -1;
  }

  // predict the label of this image
  std::vector<cv::Rect> detections;

  cascade.detectMultiScale(
      inputImage,          // input image
      detections,          // detection results
      1.1,                 // scale reduction factor
      1,                   // number of required neighbor detections
      0,                   // flags (not used)
      cv::Size(48, 48),    // minimum object size to be detected
      cv::Size(128, 128)); // maximum object size to be detected

  std::cout << "detections= " << detections.size() << std::endl;
  for (int i = 0; i < detections.size(); i++)
    cv::rectangle(inputImage, detections[i], cv::Scalar(255, 255, 255), 2);

  cv::imshow("Stop sign detection", inputImage);

  // Detecting faces
  cv::Mat picture = cv::imread("../images/girl.jpg");
  cv::CascadeClassifier faceCascade;
  if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
    std::cout << "Error when loading the face cascade classfier!" << std::endl;
    return -1;
  }

  faceCascade.detectMultiScale(picture, detections, 1.1, 3, 0, cv::Size(48, 48),
                               cv::Size(128, 128));
  // draw deetections on image
  for (int i = 0; i < detections.size(); i++)
    cv::rectangle(picture, detections[i], cv::Scalar(255, 255, 255), 2);

  cv::CascadeClassifier eyeCascade;
  if (!eyeCascade.load("haarcascade_eye.xml")) {
    std::cout << "Error wheen loading the eye cascade classifier!" << std::endl;
    return -1;
  }

  eyeCascade.detectMultiScale(picture, detections, 1.1, 3, 0, cv::Size(24, 24),
                              cv::Size(64, 64)); 
  std::cout<<"detections= "<<detections.size()<<std::endl;
  // draw detections on image
  for(int i=0;i<detections.size();i++)
    cv::rectangle(picture,detections[i],cv::Scalar(0,0,0),2);

  
  cv::imshow("Detection results", picture);

  cv::waitKey();
  cv::destroyAllWindows();
}