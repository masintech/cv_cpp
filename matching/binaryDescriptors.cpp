#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/features2d.hpp>
#include<opencv2/objdetect.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<iostream>
#define USEORB 1
#define USEFREAK 0
int main()
{
    // image matching

	// 1. Read input images
	cv::Mat image1= cv::imread("../images/church01.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat image2= cv::imread("../images/church02.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	// 2. Define keypoint vectors and descriptors
	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptors1;
	cv::Mat descriptors2;

	// Construct the ORB feature object
#if USEORB
    cv::Ptr<cv::Feature2D> feature = cv::ORB::create(60);
#else
    cv::Ptr<cv::Feature2D> feature = cv::BRISK::create(80);
#endif

     //BRISK
    // cv::Ptr<cv::Feature2D> feature = cv::BRISK::create(80);
    // 4. Keypoint detection and description
    // Detect the ORB features
    feature->detectAndCompute(image1,cv::noArray(),keypoints1,descriptors1);
    feature->detectAndCompute(image2,cv::noArray(),keypoints2,descriptors2);

    // Draw feature points
    cv::Mat featureImage;
    cv::drawKeypoints(image1,keypoints1,featureImage,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
 #if USEORB   
    // Display the corners
	cv::namedWindow("ORB");
	cv::imshow("ORB",featureImage);
    std::cout << "Number of ORB keypoints (image 1): " << keypoints1.size() << std::endl; 
	std::cout << "Number of ORB keypoints (image 2): " << keypoints2.size() << std::endl; 
#else
    // Display the corners
	cv::namedWindow("BRISK");
	cv::imshow("BRISK",featureImage);
    std::cout << "Number of BRISK keypoints (image 1): " << keypoints1.size() << std::endl; 
	std::cout << "Number of BRISK keypoints (image 2): " << keypoints2.size() << std::endl; 
#endif
#if USEFREAK
    feature = cv::xfeatures2d::FREAK::create();
	feature->compute(image1, keypoints1, descriptors1);
	feature->compute(image1, keypoints2, descriptors2);
#endif
    // Construction of matcher
    cv::BFMatcher matcher(
        cv::NORM_HAMMING); // always use hamming norm for binary deescriptor
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // draw matches
   cv::Mat imageMatches;
   cv::drawMatches(
     image1,keypoints1, // 1st image and its keypoints
     image2,keypoints2, // 2nd image and its keypoints
     matches,           // the matches
     imageMatches,      // the image produced
     cv::Scalar(255,255,255),  // color of lines
     cv::Scalar(255,255,255),  // color of points
	 std::vector< char >(),    // masks if any 
	 cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
#if USEORB     
     // Display the image of matches
    cv::namedWindow("ORB Matches");
    cv::imshow("ORB Matches", imageMatches);
#endif
#if USEFREAK
    cv::namedWindow("FREAK Matches");
    cv::imshow("FREAK Matches", imageMatches);
#endif
    std::cout << "Number of matches: " << matches.size() << std::endl; 

    cv::waitKey(0);
    cv::destroyAllWindows();
    

}