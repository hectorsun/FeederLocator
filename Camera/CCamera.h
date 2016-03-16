#ifndef CCAMERA_H
#define CCAMERA_H

#include "cameradef.h"

class CAM_EXPORTS CCamera{
public:
  CCamera(){}
  ~CCamera(){}

  
  void init();
  unsigned char* getData();


};


#endif //CCAMERA_H
