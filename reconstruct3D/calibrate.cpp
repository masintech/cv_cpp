#include <iostream>
#include <iomanip>
#include <vector>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core/ocl.hpp>

#include "CameraCalibrator.h"
using namespace std;

int main()
{
    cv::ocl::setUseOpenCL(true);
    if (!cv::ocl::haveOpenCL())
    {
        cout << "OpenCL is not avaiable..." << endl;
    }
    cv::ocl::Context context;
    if (!context.create(cv::ocl::Device::TYPE_GPU))
    {
        cout << "Failed creating the context..." << endl;
    }

    // In OpenCV 3.0.0 beta, only a single device is detected.
    cout << context.ndevices() << " GPU devices are detected." << endl;
    for (int i = 0; i < context.ndevices(); i++)
    {
        cv::ocl::Device device = context.device(i);
        cout << "name                 : " << device.name() << endl;
        cout << "available            : " << device.available() << endl;
        cout << "imageSupport         : " << device.imageSupport() << endl;
        cout << "OpenCL_C_Version     : " << device.OpenCL_C_Version() << endl;
        cout << endl;
    }
    cv::Mat image;
	std::vector<std::string> filelist;

	// generate list of chessboard image filename
	// named chessboard01 to chessboard27 in chessboard sub-dir
    for (int i=1; i<=27; i++) {

        std::stringstream str;
		str << "chessboards/chessboard" << std::setw(2) << std::setfill('0') << i << ".jpg";
		std::cout << str.str() << std::endl;

		filelist.push_back(str.str());
		image= cv::imread(str.str(),0);
        // cv::imshow("Board Image",image);
		// cv::waitKey();
    }
    // Create calibrator object
    CameraCalibrator cameraCalibrator;
	// add the corners from the chessboard
	cv::Size boardSize(7,5);
    cameraCalibrator.addChessboardPoints(
		filelist,	// filenames of chessboard image
		boardSize, "Detected points");	// size of chessboard
   
    // calibrate the camera
    // cameraCalibrator.setCalibrationFlag(true,true);
	cameraCalibrator.calibrate(image.size());

    // Example of Image Undistortion
    image = cv::imread(filelist[14],0);
	cv::Size newSize(static_cast<int>(image.cols*1.5), static_cast<int>(image.rows*1.5));
	cv::Mat uImage= cameraCalibrator.remap(image, newSize);

    // display camera matrix
	cv::Mat cameraMatrix= cameraCalibrator.getCameraMatrix();
	std::cout << " Camera intrinsic: " << cameraMatrix.rows << "x" << cameraMatrix.cols << std::endl;
	std::cout << cameraMatrix.at<double>(0,0) << " " << cameraMatrix.at<double>(0,1) << " " << cameraMatrix.at<double>(0,2) << std::endl;
	std::cout << cameraMatrix.at<double>(1,0) << " " << cameraMatrix.at<double>(1,1) << " " << cameraMatrix.at<double>(1,2) << std::endl;
	std::cout << cameraMatrix.at<double>(2,0) << " " << cameraMatrix.at<double>(2,1) << " " << cameraMatrix.at<double>(2,2) << std::endl;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image", image);
	cv::namedWindow("Undistorted Image");
    cv::imshow("Undistorted Image", uImage);


    // Store everything in a xml file
	cv::FileStorage fs("calib.xml", cv::FileStorage::WRITE);
	fs << "Intrinsic" << cameraMatrix;
	fs << "Distortion" << cameraCalibrator.getDistCoeffs();
    cv::waitKey();
	return 0;
}