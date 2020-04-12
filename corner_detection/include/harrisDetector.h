#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class HarrisDetector{

private:
    cv::Mat cornerStrength;//
    cv::Mat cornerTh;// 32 bits image of threshold of corners
    cv::Mat localMax;// 32 bits image of local maxima
    int neighborhood; // for derivative smoothing
    int aperture; // gradient compution
    double k; //harris parameters
    double maxStrength; // max of strength for threshold 
    double threshold; // calculate threshold 
    int nonMaxSize; // for non max expression
    cv::Mat kernel;

public:
    HarrisDetector(): neighborhood(3), aperture(3), k(0.1), maxStrength(0.0), threshold(0.01),
    nonMaxSize(3){
        setLocalMaxWindowSize(nonMaxSize);
    }

    void setLocalMaxWindowSize(int size){
        nonMaxSize= size;
        kernel.create(nonMaxSize, nonMaxSize, CV_8U);// create an array of size,size and type CV_8U

    }

    void detect(const cv::Mat& image){

        cv::cornerHarris(image, cornerStrength,
                        neighborhood,
                        aperture,
                        k);
        // internal threshold computation
        cv::minMaxLoc(cornerStrength,0, &maxStrength);
        // find local maximum detection
        cv::Mat dilated;
        cv::dilate(cornerStrength, dilated, cv::Mat());
        cv::compare(cornerStrength, dilated, localMax, cv::CMP_EQ);
    }

    cv::Mat getCornerMap(double qualityLevel1){
        
        cv::Mat cornerMap;

        threshold= qualityLevel1*maxStrength;
        cv::threshold(cornerStrength,cornerTh,threshold,255,cv::THRESH_BINARY);

        cornerTh.convertTo(cornerMap,CV_8U);

        cv::bitwise_and(cornerMap, localMax, cornerMap);

        return cornerMap;
    }

    void getCorners(std::vector<cv::Point> &points, double qualityLevel){

        cv::Mat cornerMap = getCornerMap(qualityLevel);
        
        for(int y=0;y< cornerMap.rows;y++){

            const uchar* rowPtr = cornerMap.ptr<uchar>(y);

            for(int x=0;x<cornerMap.cols;x++){
                if(rowPtr[x]){
                    points.push_back(cv::Point(x,y));
                }
            }
        }
    }

    void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points, 
    cv::Scalar color=cv::Scalar(255,2555,255), int radius=3, int thickness=1){
        
        std::vector<cv::Point>::const_iterator it = points.begin();

        while(it!=points.end()){

            cv::circle(image,*it,radius,color,thickness);
            ++it;
        }


    }

};