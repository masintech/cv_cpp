#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/xfeatures2d.hpp>

int main()
{

    // 1. Read input images
    cv::Mat image1= cv::imread("../images/church01.jpg",cv::IMREAD_GRAYSCALE);
	cv::Mat image2= cv::imread("../images/church02.jpg",cv::IMREAD_GRAYSCALE);

    // 2. Define keypoints vector
	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;

    // 3. Deefinee feature detector
    // Construct the SURF feature detector object
    cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SURF::create(2000.0);
    // to test with SIFT instead of SURF
    // cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SIFT::create(74);


    //4. Keypoint detection
    // Detect the SURF features
    ptrFeature2D->detect(image1, keypoints1);
    ptrFeature2D->detect(image2, keypoints2);

    // Draw feature points
    cv::Mat featureImage;
    cv::drawKeypoints(image1,keypoints1,featureImage, cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // Display the corners
	cv::namedWindow("SURF");
	cv::imshow("SURF",featureImage);
    // cv::namedWindow("SIFT");
	// cv::imshow("SIFT",featureImage);

    std::cout << "Number of SURF keypoints (image 1): " << keypoints1.size() << std::endl; 
	std::cout << "Number of SURF keypoints (image 2): " << keypoints2.size() << std::endl; 

    //SURF includes bothe detector and descriptor extractor

    // 5. Extract the descriptor
    cv::Mat descriptors1;
    cv::Mat descriptors2;
    ptrFeature2D->compute(image1, keypoints1,descriptors1);
    ptrFeature2D->compute(image2, keypoints2,descriptors2);

    // Construction of the matcher
    cv::BFMatcher matcher(cv::NORM_L2);
    // to test with crosscheck (sysmmetry) test
    // note: must not be useed in conjunction with ratio test
    // cv::BFMatcher matcher(cv::NORM_L2,true); //with crosscheck
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);
    
    // draw matches
    cv::Mat imageMatches;
    cv::drawMatches(
    image1, keypoints1,
    image2, keypoints2,
    matches,
    imageMatches,
    cv::Scalar(255,255,255),
    cv::Scalar(255,255,255),
    std::vector<char> (),
    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // Display the image of matches
	cv::namedWindow("SURF Matches");
	cv::imshow("SURF Matches",imageMatches);

	std::cout << "Number of matches: " << matches.size() << std::endl; 

    // perform the ratio test

    // find the beest two matches of each keypoint
    std::vector<std::vector<cv::DMatch>> matches2;
    matcher.knnMatch(descriptors1,descriptors2,
    matches2,
    2); // find the k(2) best matches
    matches.clear();

    // perform ratio test
    double ratioMax=0.6;
    std::vector<std::vector<cv::DMatch>>::iterator it;
    for(it=matches2.begin(); it!=matches2.end(); ++it){
        // first best match/second best match
        if ((*it)[0].distance/(*it)[1].distance<ratioMax){
            matches.emplace_back((*it)[0]);
        }
    }
    // matches is the new match set

    cv::drawMatches(
        image1, keypoints1,
        image2, keypoints2,
        matches,  // the matches
        imageMatches, // the image produced
        cv::Scalar(255,255,255), //color of lines
        cv::Scalar(255,255,255), // color of points
        std::vector<char>(), // masks if any
        cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    

    // Display the image of matches
    cv::namedWindow("SURF Matches (ratio test at 0.6)");
	cv::imshow("SURF Matches (ratio test at 0.6)",imageMatches);








    cv::waitKey(0);
    cv::destroyAllWindows();
}