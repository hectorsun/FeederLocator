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


  /////////////////
  virtual int init();

  virtual int snap(){
    return m_pImpl->snap();
  }


  /////////////////////////////////////////
  virtual int getWidth(){
    return m_pImpl->getWidth();
  }

  virtual int getHeight(){
    return m_pImpl->getHeight();
  }

  virtual unsigned char* getData(){
    return m_pImpl->getData();
  }


 private:  
  CCamera* m_pImpl;
};


#endif //CCAMERA_H
