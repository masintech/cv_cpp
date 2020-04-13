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
      std::cout<<"number "<<i * 2 + j<<std::endl;
      referenceImages[i * 2 + j].copyTo(positveImages(cv::Rect(
          j * referenceImages[i * 2 + j].cols,// 0 1 2 3 
          i * referenceImages[i * 2 + j].rows, referenceImages[i * 2 + j].cols,
          referenceImages[i * 2 + j].rows)));
    }

  cv::imshow("Positive samples", positveImages);

  cv::Mat negative = cv::imread("../images/stopSamples/bg01.png");
  cv::resize(negative, negative,cv::Size(),0.33,0.33);
  cv::imshow("One negative sample", negative);


  cv::waitKey();
  cv::destroyAllWindows();
}