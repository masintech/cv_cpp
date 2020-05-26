#include <Eigen/Dense>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>

#include <opencv2/highgui.hpp>

using Eigen::MatrixXd;

Eigen::MatrixXd convol2d(Eigen::MatrixXd &image, Eigen::MatrixXd &kernal, int bias) {
  int m=kernal.rows();
  int n=kernal.cols();
  
  Eigen::MatrixXd new_image;
  if (m == n) {
    int y=image.rows();
    int x=image.cols();
    y = y - m + 1;
    x = x - m + 1;
    Eigen::MatrixXd newimage=Eigen::MatrixXd::Zero(image.rows(),image.cols());
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
          std::cout<<"0"<<std::endl;
            Eigen::MatrixXd roi =image.block(i,j,m,m);
            std::cout<<roi<<std::endl;
            std::cout<<kernal<<std::endl;
            std::cout<<"00"<<std::endl;
            Eigen::MatrixXd mul =roi*kernal;

            std::cout<<"1"<<std::endl;
            
            std::cout<<mul<<std::endl;
            std::cout<<mul.sum()+bias<<std::endl;

            // printf("i %d j %d sum %d",i,j,sum);
            new_image<<mul.sum() + bias;
            printf("adsfadf\n");
      }
    }
  }
  return new_image;
}

int main() {
  cv::Mat image = cv::imread("church00.jpg", 0);
  if (!image.data)
    return 0;
  MatrixXd kernal(3, 3);
  kernal << -1, 0, 1, -2, 0, 2, -1, 0, 1;
  MatrixXd image2;
  cv::cv2eigen(image,image2);
  printf("conv\n");
  Eigen::MatrixXd conv=convol2d(image2,kernal,3);
  std::cout << kernal << std::endl;
//   cv::imshow("conv",conv);
//   cv::namedWindow("conv");
//   cv::imshow("image",image);
//   cv::namedWindow("image");
//   cv::waitKey();
  cv::destroyAllWindows();
}