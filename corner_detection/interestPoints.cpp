
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include "harrisDetector.h"


int main()
{
    cv::Mat image = cv::imread("church01.jpg",0);

    if(!image.data)
        return 0;
    

    cv::transpose(image,image);
    cv::flip(image, image, 0);

    cv::namedWindow("Original");
    cv::imshow("Original", image);

    cv::Mat cornerStrengh;
    cv::cornerHarris(image, cornerStrengh,
                    3,//block size
                    3,// speerturesize
                    0.01);//k
    
    cv::Mat harrisCorners;
    double threshold= 0.001;
    cv::threshold(cornerStrengh, harrisCorners,
                threshold, 255, cv::THRESH_BINARY_INV);

    cv::namedWindow("Harris");
    cv::imshow("Harris", harrisCorners);

    HarrisDetector harris;
    // Compute Harris values
    harris.detect(image);
    // Detect Harris corners
    std::vector<cv::Point> pts;
    harris.getCorners(pts, 0.02);
    
    //Draw Harris corners
    harris.drawOnImage(image, pts);

    //Display the corners
    cv::namedWindow("Corners");
    cv::imshow("Corners",image);

    //Using GFTTDetector
    std::vector<cv::KeyPoint> keypoints;
    cv::Ptr<cv::GFTTDetector> ptrGFTT = cv::GFTTDetector::create(
        500,
        0.01,
        10
    );

    ptrGFTT->detect(image,keypoints);

    std::vector<cv::KeyPoint>::const_iterator it= keypoints.begin();
    while(it!=keypoints.end()){

        cv::circle(image,it->pt,3,cv::Scalar(255,255,255),1);
        ++it;
    }

    cv::namedWindow("GFTT");
    cv::imshow("GFTT",image);
    cv::waitKey(0);
    cv::destroyAllWindows();

}