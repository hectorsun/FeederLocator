
#include <misc/imgProc.h>
#include <iostream>
using std::cout;
using std::endl;

#include <opencv2/highgui.hpp>
using namespace cv;

int imgTest(unsigned char* data, int width, int height,
	    int roiTop, int roiBottom, int roiLeft, int roiRight)
{

  cout<<"imgTest"<<endl;

  Mat img =  Mat( height,width, CV_8UC3, data);
  Mat subImg = Mat(img, Rect(roiLeft,roiTop,
			     (roiRight-roiLeft), (roiBottom-roiTop) ));
  namedWindow("Disp", WINDOW_AUTOSIZE);
  imshow("Disp", subImg);
  waitKey(0);
  
  return 0;
}
