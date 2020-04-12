
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
    cv::Mat image = cv::imread("church09.jpg",0);
    if(!image.data)
        return 0;

    
    
    
    size_t srcImge_len =image.rows*image.cols;
    
    
    uint8_t *srcImg = (uint8_t*)malloc( sizeof(uint8_t) *srcImge_len);
    uint8_t *srcPtr= srcImg;
    uint8_t *imPtr= image.data;
    // uint8_t *imPtr= (uint8_t *)image.ptr<uchar>(0);
    cv::Scalar intensity = image.at<uchar>(20,20);

    std::cout<<"(20,20): "<<intensity<<std::endl;
    int value_1_1 = imPtr[image.cols*20+20];
    std::cout<<"value_1_1: "<<value_1_1<<std::endl;
    int stride=image.step;
    std::cout<<"stride of image "<<stride<<std::endl;
    std::cout<<"cols of image "<<image.cols<<std::endl;

    for (int i =0; i <image.rows;i++){
        for(int j=0;j<image.cols;j++){
            *srcPtr++ = *imPtr++;}
    }
    int value_1_1_src = srcImg[image.cols*1+1];
    std::cout<<"value_1_1_src: "<<value_1_1_src<<std::endl;
    // uchar * data00 = image.ptr<uchar>(0); // POINTEER TO ROW 0 COL 0 
    // uchar * data10 = image.ptr<uchar>(1); // POINTEER TO ROW 1 COL 0 
    // uchar * data01 = image.ptr<uchar>(0)[1]; // POINTEER TO ROW 1 COL 1
    // std::cout<<image.data<<std::endl;
   
    cv::Mat imageWithData = cv::Mat(srcImge_len, 1, CV_8U, srcImg).clone();
    cv::Mat reshapedImage = imageWithData.reshape(0, image.rows);

    // std::cout<<image.ptr<uchar>(0)<<std::endl;
    // // cv::transpose(image,image);
    // // cv::flip(image, image, 0);

    cv::namedWindow("Original");
    cv::imshow("Original", image);

    cv::namedWindow("srcPtr");
    cv::imshow("srcPtr", reshapedImage);


   // cropping ****


    // cv::Mat image2 = cv::imread("church09.jpg",0);
    //         printf("stdddddying\n");
    
    // uint32_t offset_x = 20;
    // uint32_t offset_y = 20;
    // uint32_t srcWidth = image.cols-2*offset_x;
    // uint32_t srcHeight = image.rows-2*offset_y;
    // uint32_t srcLen =srcWidth*srcHeight;
    // uint32_t srcStride =image.cols;
    // uint8_t *dstImg =  (uint8_t *)malloc(srcLen*sizeof(uint8_t));
    // uint8_t *dstPtr =dstImg;


    // cv::Rect roi;
    // roi.x = offset_x;
    // roi.y = offset_y;
    // roi.width = image2.size().width - (offset_x*2);
    // roi.height = image2.size().height - (offset_y*2);


    // uint8_t *imPtr_2;

    // printf("start copying\n");
    // for (int i =0; i <image2.rows;i++){
    //     imPtr_2=image.ptr<uchar>(i);
    //     for(int j=0;j<image2.cols;j++){
    //         if(j>=offset_x || j<(image2.cols-offset_x)){*dstPtr++ = *imPtr_2++;}
    //         else{ ++imPtr_2;}
    //         }
    // }


    // cv::Mat crop = image2(roi);
    // cv::namedWindow("crop opencv");
    // cv::imshow("crop opencv", crop);
    // cv::waitKey(0);

    // cv::Mat imageWithData_2 = cv::Mat(srcLen, 1, CV_8U, dstImg).clone();
    // cv::Mat reshapedImage_2 = imageWithData_2.reshape(0, srcHeight);
    // cv::namedWindow("dstImg");
    // cv::imshow("dstImg", reshapedImage_2);





    // cv::Mat cornerStrengh;
    // cv::cornerHarris(image, cornerStrengh,
    //                 3,//block size
    //                 3,// speerturesize
    //                 0.01);//k
    
    // cv::Mat harrisCorners;
    // double threshold= 0.001;
    // cv::threshold(cornerStrengh, harrisCorners,
    //             threshold, 255, cv::THRESH_BINARY_INV);

    // cv::namedWindow("Harris");
    // cv::imshow("Harris", harrisCorners);

    // HarrisDetector harris;
    // // Compute Harris values
    // harris.detect(image);
    // // Detect Harris corners
    // std::vector<cv::Point> pts;
    // harris.getCorners(pts, 0.02);
    
    // //Draw Harris corners
    // harris.drawOnImage(image, pts);

    // //Display the corners
    // cv::namedWindow("Corners");
    // cv::imshow("Corners",image);

    // //Using GFTTDetector
    // std::vector<cv::KeyPoint> keypoints;
    // cv::Ptr<cv::GFTTDetector> ptrGFTT = cv::GFTTDetector::create(
    //     500,
    //     0.01,
    //     10
    // );

    // ptrGFTT->detect(image,keypoints);

    // std::vector<cv::KeyPoint>::const_iterator it= keypoints.begin();
    // while(it!=keypoints.end()){

    //     cv::circle(image,it->pt,3,cv::Scalar(255,255,255),1);
    //     ++it;
    // }

    // cv::namedWindow("GFTT");
    // cv::imshow("GFTT",image);
    // // cv::waitKey(0);
    // // cv::destroyAllWindows();

    // // FAST feature
    
    // // Read input image
    // image= cv::imread("church00.jpg", 0);
    // // rotate the image
    // cv::transpose(image, image);
    // cv::flip(image,image,0);
    // keypoints.clear();
    // // FAST detector
    // cv::Ptr<cv::FastFeatureDetector> ptrFAST = cv::FastFeatureDetector::create(40);
    // // detect the keypoints
    // ptrFAST->detect(image, keypoints);
    // // draw the keypoints
    // cv::drawKeypoints(image, keypoints, image, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    // std::cout<<"Number of keypoints(FAST): "<<keypoints.size()<<std::endl;

    // // Display the keypoints
    // cv::namedWindow("FAST");
    // cv::imshow("FAST",image);

    // // FAST feature without non-max suppression
    // // Read input image
    // image=cv::imread("church00.jpg",0);
    // // rotate the image
    // cv::transpose(image, image);
    // cv::flip(image,image,0);

    // keypoints.clear();
    // // detect the keypoints
    // ptrFAST->setNonmaxSuppression(false);
    // ptrFAST->detect(image,keypoints);
    // // draw the keypoints
    // cv::drawKeypoints(image,keypoints,image,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    // cv::namedWindow("FAST Features(all) without non-max suppression");
    // cv::imshow("FAST Features (all)", image);

    // // Read input image
    // image = cv::imread("church00.jpg",0);
    // // rotate the image
    // cv::transpose(image, image);
    // cv::flip(image,image,0);

    // int total(100); // requested number of keypoints
    // int hstep(5), vstep(3); // grid of 4 columns by 3 rows
    // // hstep=vstep= 1; // trry without grid
    // int hsize(image.cols/hstep), vsize(image.rows/ vstep);
    // int subtotal(total/ (hstep*vstep)); // number of keypoints per grid
    // cv::Mat imageROI;
    // std::vector<cv::KeyPoint> gridpoints;
    
    // std::cout <<"Grid of "<<vstep<<" by "<<hstep<<" each of size "<<vsize<<" by "<<hsize<<std::endl;
    
    // // detection with low threshold
    // ptrFAST->setThreshold(20);
    // // non-max suppression
    // ptrFAST->setNonmaxSuppression(true);
    
    // // The final vector of keypoints
    // keypoints.clear();
    // //detect on each grid
    // for (int i =0;i<vstep;i++)
    //     for(int j=0;j<hstep;j++){

    //         // create ROT over current grid
    //         imageROI = image(cv::Rect(j*hsize,i*vsize, hsize, vsize));
    //         //detect the keypoints in grid
    //         gridpoints.clear();
    //         ptrFAST->detect(imageROI,gridpoints);
    //         std::cout<<"Number of FAST in grid "<<i<<","<<j<<": "<<gridpoints.size()<<std::endl;
    //         if(gridpoints.size()>subtotal){
    //             for(auto it=gridpoints.begin();it!=gridpoints.end();it++){
    //                 std::cout<<" "<<it->response<<std::endl;
    //             }
    //         }
    //         // get the strongest FAST features
    //         auto itEnd(gridpoints.end());
    //         if(gridpoints.size()>subtotal){// select the strongest features
    //             std::nth_element(gridpoints.begin(), gridpoints.begin()+subtotal, gridpoints.end(),
    //             [](cv::KeyPoint&a, cv::KeyPoint&b){return a.response>b.response;}
    //             );
    //             itEnd = gridpoints.begin()+subtotal;
                
    //         }

    //         // addd them to the global keypoint vector
    //         for(auto it=gridpoints.begin();it !=itEnd;++it){
    //             it->pt +=cv::Point2f(j*hsize,i*vsize);//convert to image coordinate
    //             keypoints.push_back(*it);
    //             std::cout<<" "<<it->response<<std::endl;
    //         }
        
    //     }
    
    // // draw the keypoints
    // cv::drawKeypoints(image, keypoints, image, cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    // //dISPLAY
    // cv::namedWindow("FAST Features (grid)");
    // cv::imshow("FAST Features (grid)", image);

    

    // // SURF
    // image = cv::imread("church00.jpg",0);
    // // rotate the image
    // cv::transpose(image, image);
    // cv::flip(image,image,0);

    // keypoints.clear();
    // // Construct the SURF feature detector object
    // cv::Ptr<cv::xfeatures2d::SurfFeatureDetector> ptrSURF = cv::xfeatures2d::SurfFeatureDetector::create(2000.0);
    // // detect the SURF features
    // ptrSURF->detect(image, keypoints);

    // // Detect SURF features
    // ptrSURF->detect(image,keypoints);

    // cv::Mat featureImage;
    // cv::drawKeypoints(image, keypoints, featureImage, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // //Display
    // cv::namedWindow("SURF");
    // cv::imshow("SURF",featureImage);


    // //SIFT:

    // // Read input image
    // image=cv::imread("church00.jpg",0);

    // // rotate the image
    // cv::transpose(image,image);
    // cv::flip(image,image, 0);

    // keypoints.clear();
    // // Construct the SIFT feature detector object
    // cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> ptrSIFT =cv::xfeatures2d::SiftFeatureDetector::create();
    // // detect the keypoints
    // ptrSIFT->detect(image, keypoints);

    // // Detect the SIFT features
    // ptrSIFT->detect(image,keypoints);

    // cv::drawKeypoints(image,keypoints, featureImage, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // // Display the keypoints
    // cv::namedWindow("SIFT");
    // cv::imshow("SIFT", featureImage);

    // std::cout<<"Number of SIFT keypoints: "<<keypoints.size()<<std::endl;


    // // BRISK;

    // image=cv::imread("church00.jpg",0);
    // cv::transpose(image, image);
	// cv::flip(image, image, 0);

    // keypoints.clear();

    // cv::Ptr<cv::BRISK> ptrBRISK = cv::BRISK::create(
    //     60, // threshold for BRISK point to be accpeted
    //     5 //# of octaves
    // );

    // // Detect the BRISK features
    // ptrBRISK->detect(image, keypoints);

    // cv::drawKeypoints(image, keypoints, featureImage, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // // Display the keypoints
	// cv::namedWindow("BRISK");
	// cv::imshow("BRISK", featureImage);
    // std::cout<<"Number of BRISK keypoints: "<<keypoints.size()<<std::endl;
    


    // //ORB

    // image=cv::imread("church00.jpg",0);
    // cv::transpose(image, image);
	// cv::flip(image, image, 0);

    // keypoints.clear();
    // // Consttruct the BRISK feature detector obkect
    // cv::Ptr<cv::ORB> ptrORB = cv::ORB::create(
    //     75, // total number of keypoints
    //     1.2,    // scale factor between layers
    //     8 // number of layers in pyramid
    // );
    // // detetct the keypoints
    // ptrORB->detect(image, keypoints);


    // cv::drawKeypoints(image, keypoints, featureImage, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // // Display
    // cv::namedWindow("ORB");
    // cv::imshow("ORB", featureImage);
    // std::cout<<"Number of ORB keypoints: "<<keypoints.size()<<std::endl;


    cv::waitKey(0);
    cv::destroyAllWindows();
}


//