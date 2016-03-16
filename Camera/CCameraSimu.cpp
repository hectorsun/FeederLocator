#include "CCamera.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using std::cout;
using std::endl;


void 
CCamera::init()
{
  const char szPicPath[] = "./1.bmp";
  std::cout<<"CameraSimu CCamera::init()"<<std::endl;
  //std::cout<<"PicPath="<<szPicPath<<std::endl;
  cv::Mat img = cv::imread(szPicPath);
  if (!img.data){
    cout<<"failed to load image"<<endl;
    return;
  }
  m_imgWidth = img.cols;
  m_imgHeight = img.rows;
  m_imgData = img.data;
  std::cout <<"width="<< m_imgWidth<<" ,height="<<m_imgHeight<<std::endl;
}


