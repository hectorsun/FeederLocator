

#include <misc/imgProc.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int imgBaseLocate(unsigned char* data, int width, int height,
		  miscRect& roi, miscRect* basePosition)
{

  int l_width = roi.right - roi.left;
  int l_height = roi.bottom - roi.top;
  basePosition->top = roi.top + l_height/4;
  basePosition->bottom = roi.bottom - l_height/4;
  basePosition->left = roi.left + l_width/4;
  basePosition->right = roi.right - l_width/4;

  return 0;
}
