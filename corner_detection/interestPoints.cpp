
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

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
    // cv::waitKey(0);
    // cv::destroyAllWindows();

    // FAST feature
    
    // Read input image
    image= cv::imread("church01.jpg", 0);
    // rotate the image
    cv::transpose(image, image);
    cv::flip(image,image,0);
    keypoints.clear();
    // FAST detector
    cv::Ptr<cv::FastFeatureDetector> ptrFAST = cv::FastFeatureDetector::create(40);
    // detect the keypoints
    ptrFAST->detect(image, keypoints);
    // draw the keypoints
    cv::drawKeypoints(image, keypoints, image, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    std::cout<<"Number of keypoints(FAST): "<<keypoints.size()<<std::endl;

    // Display the keypoints
    cv::namedWindow("FAST");
    cv::imshow("FAST",image);

    // FAST feature without non-max suppression
    // Read input image
    image=cv::imread("church01.jpg",0);
    // rotate the image
    cv::transpose(image, image);
    cv::flip(image,image,0);

    keypoints.clear();
    // detect the keypoints
    ptrFAST->setNonmaxSuppression(false);
    ptrFAST->detect(image,keypoints);
    // draw the keypoints
    cv::drawKeypoints(image,keypoints,image,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    cv::namedWindow("FAST Features(all)");
    cv::imshow("FAST Features (all)", image);

    // Read input image
    image = cv::imread("church01.jpg",0);
    // rotate the image
    cv::transpose(image, image);
    cv::flip(image,image,0);

    int total(100); // requested number of keypoints
    int hstep(5), vstep(3); // grid of 4 columns by 3 rows
    // hstep=vstep= 1; // trry without grid
    int hsize(image.cols/hstep), vsize(image.rows/ vstep);
    int subtotal(total/ (hstep*vstep)); // number of keypoints per grid
    cv::Mat imageROI;
    std::vector<cv::KeyPoint> gridpoints;
    
    std::cout <<"Grid of "<<vstep<<" by "<<hstep<<" each of size "<<vsize<<" by "<<hsize<<std::endl;
    
    // detection with low threshold
    ptrFAST->setThreshold(20);
    // non-max suppression
    ptrFAST->setNonmaxSuppression(true);
    
    // The final vector of keypoints
    keypoints.clear();
    //detect on each grid
    for (int i =0;i<vstep;i++)
        for(int j=0;j<hstep;j++){

            // create ROT over current grid
            imageROI = image(cv::Rect(j*hsize,i*vsize, hsize, vsize));
            //detect the keypoints in grid
            gridpoints.clear();
            ptrFAST->detect(imageROI,gridpoints);
            std::cout<<"Number of FAST in grid "<<i<<","<<j<<": "<<gridpoints.size()<<std::endl;
            if(gridpoints.size()>subtotal){
                for(auto it=gridpoints.begin();it!=gridpoints.end();it++){
                    std::cout<<" "<<it->response<<std::endl;
                }
            }
            // get the strongest FAST features
            auto itEnd(gridpoints.end());
            if(gridpoints.size()>subtotal){// select the strongest features
                std::nth_element(gridpoints.begin(), gridpoints.begin()+subtotal, gridpoints.end(),
                [](cv::KeyPoint&a, cv::KeyPoint&b){return a.response>b.response;}
                );
                itEnd = gridpoints.begin()+subtotal;
                
            }

            // addd them to the global keypoint vector
            for(auto it=gridpoints.begin();it !=itEnd;++it){
                it->pt +=cv::Point2f(j*hsize,i*vsize);//convert to image coordinate
                keypoints.push_back(*it);
                std::cout<<" "<<it->response<<std::endl;
            }
        
        }
    // draw the keypoints
    cv::drawKeypoints(image, keypoints, image, cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    //dISPLAY
    cv::namedWindow("FAST Features (grid)");
    cv::imshow("FAST Features (grid)", image);

    cv::waitKey(0);
    cv::destroyAllWindows();

    // SURF
    image = cv::imread("church01.jpg",0);
    // rotate the image
    cv::transpose(image, image);
    cv::flip(image,image,0);

    keypoints.clear();
    // Construct the SURF feature detector object
    cv::Ptr<cv::xfeatures2d::SurfFeatureDetector> ptrSURF = cv::xfeatures2d::SurfFeatureDetector::create(2000.0);
    // detect the SURF features
    ptrSURF->detect(image, keypoints);

    // Detect SURF features
    ptrSURF->detect(image,keypoints);

    cv::Mat featureImage;
    cv::drawKeypoints(image, keypoints, featureImage, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //Display
    cv::namedWindow("SURF");
    cv::imshow("SURF",featureImage);


}
