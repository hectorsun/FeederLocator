#include <Camera/CCamera.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using std::cout;
using std::endl;

#include <memory>

void 
CCamera::init()
{
  //const char szPicPath[] = "./1.bmp";
  cout<<"===CameraSimu CCamera::init()==="<<endl;
  cout<<"Path:"<<PicPath<<endl;
  cv::Mat img = cv::imread(PicPath);
  if (!img.data){
    cout<<"failed to load image"<<endl;
    return;
  }
  m_imgWidth = img.cols;
  m_imgHeight = img.rows;
  int l_size = img.elemSize()*img.cols*img.rows;
  m_imgData = new unsigned char[l_size];
  memcpy(m_imgData, img.data, l_size);
  std::cout <<"width="<< m_imgWidth
	    <<" ,height="<<m_imgHeight
	    << ", size="<< l_size
	    << ",type="<<img.type()
	    <<std::endl;
  cout<<"================================"<<endl;
}

int
CCamera::snap()
{
  cout<<"CCamera::snape()"<<endl;
  return 0;
}
