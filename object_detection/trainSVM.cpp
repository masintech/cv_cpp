#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/ml.hpp>


// draw one HOG over one cell
void drawHOG(std::vector<float>::const_iterator hog, // iterator to the HOG
	         int numberOfBins,        // number of bins inHOG
	         cv::Mat &image,          // image of the cell
	         float scale=1.0) {       // lenght multiplier

	const float PI = 3.1415927;
	float binStep = PI / numberOfBins;
	float maxLength = image.rows;
	float cx = image.cols / 2.;
	float cy = image.rows / 2.;

	// for each bin
	for (int bin = 0; bin < numberOfBins; bin++) {

		// bin orientation
		float angle = bin*binStep;
		float dirX = cos(angle);
		float dirY = sin(angle);
		// length of line proportion to bin size
		float length = 0.5*maxLength* *(hog+bin);

		// drawing the line
		float x1 = cx - dirX * length * scale;
		float y1 = cy - dirY * length * scale;
		float x2 = cx + dirX * length * scale;
		float y2 = cy + dirY * length * scale;
		cv::line(image, cv::Point(x1, y1), cv::Point(x2, y2), CV_RGB(255, 255, 255), 1);
	}
}

// Draw HOG over an image
void drawHOGDescriptors(const cv::Mat &image,  // the input image 
	                    cv::Mat &hogImage,     // the resulting HOG image
	                    cv::Size cellSize,     // size of each cell (blocks are ignored)
	                    int nBins) {           // number of bins

	// block size is image size
	cv::HOGDescriptor hog(cv::Size((image.cols / cellSize.width) * cellSize.width, 
		                           (image.rows / cellSize.height) * cellSize.height),
		cv::Size((image.cols / cellSize.width) * cellSize.width,
			(image.rows / cellSize.height) * cellSize.height),	
		cellSize,    // block stride (ony 1 block here)
		cellSize,    // cell size
		nBins);      // number of bins

	// compute HOG
	std::vector<float> descriptors;
	hog.compute(image, descriptors);

	float scale= 2.0 / *std::max_element(descriptors.begin(), descriptors.end());

	hogImage.create(image.rows, image.cols, CV_8U);

	std::vector<float>::const_iterator itDesc= descriptors.begin();

	for (int i = 0; i < image.rows / cellSize.height; i++) {
		for (int j = 0; j < image.cols / cellSize.width; j++) {
			// draw wach cell
			hogImage(cv::Rect(j*cellSize.width, i*cellSize.height, cellSize.width, cellSize.height));
            cv::Mat image =hogImage(cv::Rect(j*cellSize.width, i*cellSize.height,
				                           cellSize.width, cellSize.height));
			drawHOG(itDesc, nBins,image , scale);
			itDesc += nBins;
		}
	}
}




int main()
{
    cv::Mat image = imread("../images/girl.jpg", cv::IMREAD_GRAYSCALE);
	cv::imshow("Original image", image);

    cv::HOGDescriptor hog(cv::Size((image.cols/16)*16, (image.rows/16)*16),//size of the window
        cv::Size(16,16),   // block size
        cv::Size(16,16),  // block stride
        cv::Size(4,4),    // cell size
        9);             // number of bins

    std::vector<float> descriptors;

    // Draw a representation of HOG cells
    cv::Mat hogImage = image.clone();
    drawHOGDescriptors(image, hogImage, cv::Size(16,16), 9);
    cv::imshow("HOG image", hogImage);

    cv::waitKey();
    cv::destroyAllWindows();

}