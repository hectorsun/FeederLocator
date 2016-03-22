#ifndef MISC_IMG_PROC_H
#define MISC_IMG_PROC_H

#include "miscdef.h"

class MISC_EXPORTS miscPoint{
 public:
  miscPoint(int x_=0, int y_=0){
    x = x_;
    y = y_;
  }
  int x;
  int y;
};

class MISC_EXPORTS miscRect{
 public:
  miscRect(int top_=0, int bottom_=0, int left_=0, int right_=0)
    {
      top =top_;
      bottom=bottom_;
      left=left_;
      right=right_;
    }
  miscPoint getCenter(){
    return miscPoint((left+right)/2,
		     (top+bottom)/2);
  }
  int top;
  int bottom;
  int left;
  int right;
};




int MISC_EXPORTS imgTest(unsigned char* data, int width, int height,
			 int roiTop, int roiBottom, int roiLeft, int roiRight);
int MISC_EXPORTS imgTest(unsigned char* data, int width, int height,
			 miscRect& roi);

int MISC_EXPORTS imgChipLocate(unsigned char* data, int width, int height,
			      miscRect& roi, miscRect* chipLocation);


int MISC_EXPORTS imgBaseLocate(unsigned char* data, int width, int height,
			       miscRect& roi, miscRect* baseLocation);

#endif
