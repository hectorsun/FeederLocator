#ifndef CCAMERA_H
#define CCAMERA_H

#include "cameradef.h"

class CAM_EXPORTS CCamera{
public:
  CCamera(){}
  ~CCamera(){}

  static CCamera& getInstance(){
    static CCamera* ins = new CCamera();
    return *ins;
  }

  //////////////////////////////////////////
  void init();
  
  //////////////////////////////////////////
  int getWidht(){return m_imgWidth;}
  int getHeight() {return m_imgHeight;}
  unsigned char* getData() {return m_imgData;}
private:
  int m_imgWidth;
  int m_imgHeight;
  unsigned char*  m_imgData;
};


#endif //CCAMERA_H
