#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/face.hpp>

// compute local binary patterns of a grap-level image
void lbp(const cv::Mat &image, cv::Mat &result){

    assert(image.channels() ==1 ); // input image must be grap scale

    result.create(image.size(), CV_8U); // allocate if necessary

    for( int j = 1; j < image.rows-1; j++){ // for all rows (except first and last)

        const uchar* previous = image.ptr<const uchar>(j-1); // previous row
        const uchar* current = image.ptr<const uchar>(j-1);  // currnet row
        const uchar* next = image.ptr<const uchar>(j+1);     // next row

        uchar* output = result.ptr<uchar>(j); // output row

        for (int i =1; i < image.cols - 1;i++){
            // compose elocal binary pattern
            *output = previous[i-1] > current[i] ? 1:0;
            *output |= previous[i] > current[i] ? 2:0;
            *output |= previous[i+1] > current[i] ? 4:0;

            *output |= previous[i-1] > current[i] ? 8:0;
            *output |= previous[i+1] > current[i] ? 16:0;


            *output |= previous[i-1] > current[i] ? 32:0;
            *output |= previous[i] > current[i] ? 64:0;
            *output |= previous[i+1] > current[i] ? 128:0;

            output++; // next pixel
        }
    }


    // Set the unprocess pixels to 9
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols - 1).setTo(cv::Scalar(0));

}
