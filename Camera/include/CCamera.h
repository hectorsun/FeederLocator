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
  virtual int init();

  virtual int snap();
  
  //////////////////////////////////////////
  virtual int getWidth();
  virtual int getHeight() ;
  virtual unsigned char* getData();
 private:
  
  CCamera* m_pImpl;
};


#endif //CCAMERA_H
