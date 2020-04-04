#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/xfeatures2d.hpp>
void sift_match(cv::Mat &image3, cv::Mat &image4){
   
    std::vector<cv::KeyPoint> keypoints3;
	std::vector<cv::KeyPoint> keypoints4;
    cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SIFT::create(74);
    cv::Mat descriptors3;
    cv::Mat descriptors4;
    ptrFeature2D->detect(image3, keypoints3,descriptors3);
    ptrFeature2D->detect(image4, keypoints4,descriptors4);
    cv::Mat featureImage;
    cv::drawKeypoints(image3,keypoints4,featureImage, cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

   

    std::cout << "Number of SIFT keypoints (image 3): " << keypoints3.size() << std::endl; 
	std::cout << "Number of SIFT keypoints (image 4): " << keypoints4.size() << std::endl; 

    // Extract the keypoints and decriptors
    cv::Ptr<cv::Feature2D> ptrFeature2D_2 = cv::xfeatures2d::SIFT::create();
    ptrFeature2D_2->detectAndCompute(image3, cv::noArray(), keypoints3, descriptors3);
    ptrFeature2D_2->detectAndCompute(image4, cv::noArray(), keypoints4, descriptors4);
     
   
    cv::BFMatcher matcher(cv::NORM_L2,true); //with crosscheck
    std::vector<cv::DMatch> matches;
    // Match the two images descriptors
    matcher.match(descriptors3, descriptors4, matches);
    // extract the 50 beest matches
    std::nth_element(matches.begin(), matches.begin()+50,matches.end());
    matches.erase(matches.begin()+50,matches.end());


    // // draw matches
    cv::Mat imageMatches;
	cv::drawMatches(
		image3, keypoints3, // 1st image and its keypoints
		image4, keypoints4, // 2nd image and its keypoints
		matches,            // the matches
		imageMatches,      // the image produced
		cv::Scalar(255, 255, 255),  // color of lines
		cv::Scalar(255, 255, 255), // color of points
		std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS| cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // Display the image of matches
	cv::namedWindow("Multi-scale SIFT Matches");
	cv::imshow("Multi-scale SIFT Matches",imageMatches);

    std::cout<< "Number of matches: "<<matches.size()<<std::endl;
}

int main()
{
    //   *******Using SURF************
    // 1. Read input images
    cv::Mat image1= cv::imread("../images/church01.jpg",cv::IMREAD_GRAYSCALE);
	cv::Mat image2= cv::imread("../images/church02.jpg",cv::IMREAD_GRAYSCALE);

    // 2. Define keypoints vector
	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;

    // // 3. Deefinee feature detector
    // // Construct the SURF feature detector object
    cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SURF::create(2000.0);
   

    //4. Keypoint detection
    // Detect the SURF features
    ptrFeature2D->detect(image1, keypoints1); //keypoints
    ptrFeature2D->detect(image2, keypoints2); //features

    // // Draw feature points
    cv::Mat featureImage;
    cv::drawKeypoints(image1,keypoints1,featureImage, cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // // Display the corners
	cv::namedWindow("SURF");
	cv::imshow("SURF",featureImage);
    

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
    // note: must NOT be used in conjunction with ratio test
    // cv::BFMatcher matcher(cv::NORM_L2,true); //with crosscheck with better result
    std::vector<cv::DMatch> matches, matches_cross;
    matcher.match(descriptors1, descriptors2, matches);
    cv::BFMatcher matcher_cross(cv::NORM_L2,true); //with crosscheck with better result
    matcher_cross.match(descriptors1, descriptors2, matches_cross);
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

    // draw matches with cross check 
    cv::drawMatches(
    image1, keypoints1,
    image2, keypoints2,
    matches_cross,
    imageMatches,
    cv::Scalar(255,255,255),
    cv::Scalar(255,255,255),
    std::vector<char> (),
    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // Display the image of matches
	cv::namedWindow("SURF Matches with cross check");
	cv::imshow("SURF Matches with cross check",imageMatches);
	std::cout << "Number of matches: " << matches.size() << std::endl; 
    std::cout << "Number of matches with cross check: " << matches_cross.size() << std::endl; 

    // *** Perfor Ratio Test ***

    // find the best two matches of each keypoint
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
  
    // **** Radius Match ****
    float maxDist = 0.3;
    matches2.clear();
    matcher.radiusMatch(descriptors1, descriptors2, matches2,
                     maxDist); // maximum acceptable distance
                              // between the 2 descriptors

    cv::drawMatches(
            image1, keypoints1,
            image2, keypoints2,
            matches2,  // the matches
            imageMatches, // the image produced
            cv::Scalar(255, 255, 255),  // color of lines
		    cv::Scalar(255, 255, 255),  // color of points
            std::vector<std::vector<char>>(), //masks if any
            cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS
    );      

    int nmatches = 0;
    for (int i =0; i <matches2.size();i++) nmatches += matches2[i].size();                  
    std::cout<<" Number of matches (with max radius): "<<nmatches<<std::endl;

    // // Display the image of matches
	cv::namedWindow("SURF Matches (with max radius)");
	cv::imshow("SURF Matches (with max radius)", imageMatches);


    // ***** scale-invariance test SIFT ******
    cv::Mat image3= cv::imread("../images/church01.jpg",cv::IMREAD_GRAYSCALE);
	cv::Mat image4= cv::imread("../images/church03.jpg",cv::IMREAD_GRAYSCALE);
    sift_match(image3,image4);
    
    

    cv::waitKey(0);
    cv::destroyAllWindows();
}