
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main ()
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

      cv::waitKey(0);
    cv::destroyAllWindows();
}