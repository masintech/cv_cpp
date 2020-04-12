#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "targetMatcher.h"

int main()
{
    // Read input images
	cv::Mat target= cv::imread("../images/cookbook1.bmp",0);
	cv::Mat image= cv::imread("../images/objects.jpg",0);
	if (!target.data || !image.data)
		return 0; 
    printf("image read\n");
    // Display the images
	cv::namedWindow("Target");
	cv::imshow("Target",target);
	cv::namedWindow("Image");
	cv::imshow("Image", image);

    // Prepare the matcher
    TargetMatcher tmatcher(cv::FastFeatureDetector::create(10), cv::BRISK::create());
    tmatcher.setNormType(cv::NORM_HAMMING);

    // definition of the output data
    std::vector<cv::DMatch> matches;
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    std::vector<cv::Point2f> corners;


    // set the target image
    tmatcher.setTarget(target);

    // matche image with target
    tmatcher.detectTtarget(image, corners);
    // draw the target corners on the image
    if( corners.size()==4){
        cv::line(image, cv::Point(corners[0]), cv::Point(corners[1]), cv::Scalar(255,255,255),3);
        cv::line(image, cv::Point(corners[1]), cv::Point(corners[2]), cv::Scalar(255,255,255),3);
        cv::line(image, cv::Point(corners[2]), cv::Point(corners[3]), cv::Scalar(255,255,255),3);
        cv::line(image, cv::Point(corners[3]), cv::Point(corners[4]), cv::Scalar(255,255,255),3);

    }

    cv::namedWindow("Target detection");
    cv::imshow("Target detection" ,image);


    cv::waitKey();
    cv::destroyAllWindows();


    
}