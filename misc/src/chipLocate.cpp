#include <misc/imgProc.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int  imgChipLocate(unsigned char* data, int width, int height,
			       miscRect& roi, miscRect* chipPosition)
{
  int l_width = roi.right - roi.left;
  int l_height = roi.bottom - roi.top;
  chipPosition->top = roi.top + l_height/4;
  chipPosition->bottom = roi.bottom - l_height/4;
  chipPosition->left = roi.left + l_width/4;
  chipPosition->right = roi.right - l_width/4;
  return 0;
}
