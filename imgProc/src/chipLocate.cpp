#include <imgProc/imgProc.h>

#include <opencv2/opencv.hpp>
#include <misc/CDataSet.h>

#include <vector>

/**
 a simple implement of chop locate algorithm for test
 it should be refined later!!!
 by SUN Hao sunhaohit0@gmail.com
 */

int  imgChipLocate(unsigned char* data, int width, int height,
		   imgRect& roi, imgRect* chipPosition)
{

  // get roi of image
  cv::Mat img =  cv::Mat( height,width, CV_8UC3, data);
  cv::Mat imgRoi = cv::Mat(img, cv::Rect(roi.left,
					 roi.top,
					 (roi.right-roi.left), 
					 (roi.bottom-roi.top) ));
  /*
  cv::namedWindow("Disp", cv::WINDOW_AUTOSIZE);
  cv::imshow("Disp", imgRoi);
  cv::waitKey(0);
  */

  // Gray
  cv::Mat imgRoiGray;
  cv::cvtColor(imgRoi, imgRoiGray, cv::COLOR_RGB2GRAY);
  /*  
  cv::namedWindow("gray", cv::WINDOW_AUTOSIZE);
  cv::imshow("gray", imgRoiGray);
  cv::waitKey(0);
  */
  // threshold
  cv::Mat imgThreshold;
  cv::threshold(imgRoiGray, imgThreshold, 0, 255, cv::THRESH_OTSU);
  cv::threshold(imgThreshold, imgThreshold, 128, 255, cv::THRESH_BINARY_INV);

  /*
  cv::namedWindow("threshold", cv::WINDOW_AUTOSIZE);
  cv::imshow("threshold", imgThreshold);
  cv::waitKey(0);
  */
  //
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(imgThreshold, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

  double maxArea = 0;
  std::vector<cv::Point> maxContour;
  int nMaxArea = 0;
  for (size_t i =0; i<contours.size(); i++){
    double area = cv::contourArea(contours[i]);

    if (area > maxArea){
      maxArea = area;
      maxContour = contours[i];
      nMaxArea = i;
    }
  }

  
  // erase all areas except for max area
  //cv::Mat res1;
  //imgThreshold.copyTo(res1);
  
  
  // show max area
  cv::Mat res2;
  imgThreshold.copyTo(res2);
  cv::Rect maxRect = cv::boundingRect(maxContour);
  /*
  cv::rectangle(res2, maxRect, cv::Scalar(255));
  cv::imshow("lag", res2);
  cv::waitKey(0);
  */

  ///////////////////
  chipPosition->top    = roi.top  + maxRect.tl().y;
  chipPosition->bottom = roi.top  + maxRect.br().y;
  chipPosition->left   = roi.left + maxRect.tl().x;
  chipPosition->right  = roi.left + maxRect.br().x;
  return 0;
}


double 
imgGetDiff(const imgPoint& _center){
  imgPoint a = _center - CDataSet::getInstance().getBaseRect().getCenter();
  imgPoint b = CDataSet::getInstance().getFirstChipCenter() -
    CDataSet::getInstance().getSecondChipCenter();

  return (a.x*b.x+a.y*b.y)*CDataSet::getInstance().getWidthOfPixel();
   
}
