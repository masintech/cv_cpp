#include <iomanip>
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <string>
#include "videoprocessor.h"

void draw(const cv::Mat &img, cv::Mat &out) {
  img.copyTo(out);
  cv::circle(out, cv::Point(100, 100), 5, cv::Scalar(255, 0, 0), 2);
}

// processing function
void canny(cv::Mat &img, cv::Mat &out) {
  // Convert to gray
  if (img.channels() == 3)
    cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
  // Compute Canny edges
  cv::Canny(out, out, 100, 200);
  // Invert the image
  cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);
}

int main() {
  // Open the video file
  cv::VideoCapture capture("./images/bike.avi");

  // check if video successfully opened
  if (!capture.isOpened())
    return 1;

  // Get the frame rate
  double rate = capture.get(cv::CAP_PROP_FPS);
  std::cout << "Frame rate: " << rate << "fps" << std::endl;

  bool stop(false);
  cv::Mat frame; // current video frame
  cv::namedWindow("Extracted Frame");

  // Delay between each frame
  // correponds to video frame rate
  int delay = 1000 / rate;
  long long i = 0;
  std::string b = "bike";
  std::string ext = ".bmp";

  // for all frames in video
  while (!stop) {

    // read next frame if any
    if (!capture.read(frame))
      break;
    cv::imshow("Extracted Frame", frame);

    std::string name(b);
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(3) << i;
    name += ss.str();
    i++;
    name += ext;

    cv::Mat test;
    cv::resize(frame, test, cv::Size(), 0.2, 0.2);
    cv::imwrite(name, frame);
    // cv::imwrite(name, test);
    // introduce a delay
    // or press key to stop
    if (cv::waitKey(delay) >= 0)
      stop = true;
  }

  // close the video file
  capture.release();

  // Now using the VideoProcessor class
 // Create instance
	VideoProcessor processor;
    // Open video file
	processor.setInput("./images/bike.avi");
    // Declare a window to display the video
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");
    
    // Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());

	// Set the frame processor callback function
	processor.setFrameProcessor(canny);


  cv::waitKey();
  cv::destroyAllWindows();
}