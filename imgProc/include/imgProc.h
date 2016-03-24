#ifndef MISC_IMG_PROC_H
#define MISC_IMG_PROC_H

#include "imgprocdef.h"

class IMGPROC_EXPORTS imgPoint{
 public:
  imgPoint(int x_=0, int y_=0){
    x = x_;
    y = y_;
  }
  int x;
  int y;
};

class IMGPROC_EXPORTS imgRect{
 public:
  imgRect(int top_=0, int bottom_=0, int left_=0, int right_=0)
    {
      top =top_;
      bottom=bottom_;
      left=left_;
      right=right_;
    }
  imgPoint getCenter(){
    return imgPoint((left+right)/2,
		     (top+bottom)/2);
  }
  int top;
  int bottom;
  int left;
  int right;
};




int IMGPROC_EXPORTS imgTest(unsigned char* data, int width, int height,
			 int roiTop, int roiBottom, int roiLeft, int roiRight);
int IMGPROC_EXPORTS imgTest(unsigned char* data, int width, int height,
			    imgRect& roi);

int IMGPROC_EXPORTS imgChipLocate(unsigned char* data, int width, int height,
				  imgRect& roi, imgRect* chipLocation);


int IMGPROC_EXPORTS imgBaseLocate(unsigned char* data, int width, int height,
				  imgRect& roi, imgRect* baseLocation);

#endif
