#include <Camera/CCamera.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using std::cout;
using std::endl;

#include <memory>

class CCameraSimuImpl : public CCamera{
public:
  CCameraSimuImpl(){};
  ~CCameraSimuImpl(){};

  ////////////////////////////
  virtual int init();
  virtual int snap();

  ///////////////////////////
  virtual int getWidth();
  virtual int getHeight();
  virtual unsigned char* getData();
private:
  int m_imgWidth;
  int m_imgHeight;
  unsigned char* m_imgData;
};


int
CCameraSimuImpl::init()
{
  //const char szPicPath[] = "./1.bmp";
  cout<<"===CameraSimu CCamera::init()==="<<endl;
  cout<<"Path:"<<PicPath<<endl;
  cv::Mat img = cv::imread(PicPath);
  if (!img.data){
    cout<<"failed to load image"<<endl;
    return 1;
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
  return 0;
}

int
CCameraSimuImpl::snap()
{
  cout<<"CCamera::snape()"<<endl;
  return 0;
}

int 
CCameraSimuImpl::getWidth(){
  return m_imgWidth;
}

int
CCameraSimuImpl::getHeight(){
  return m_imgHeight;
}

unsigned char*
CCameraSimuImpl::getData(){
  return m_imgData;
}

//////////////////////////////////////////////////////////////////////
int 
CCamera::init(){
  m_pImpl = new CCameraSimuImpl;
  return m_pImpl->init();
}
