#ifndef CDATASET_H
#define CDATASET_H

#include <string>
#include "miscdef.h"
#include "imgProc.h"

class MISC_EXPORTS CDataSet{
public:
  static CDataSet&
  getInstance(){
    static CDataSet* ins = new CDataSet();
    return *ins;
  }

  /** @brief save data form disk
   */
  int saveData(const std::string path);

  /** @brief load data into disk
   */
  int loadData(const std::string path);

  /**
  
   */
  void setBaseRect(const miscRect base){
    m_baseRect = base;
  }
  miscRect& getBaseRect(){
    return m_baseRect;
  }

  void setChipRect(const miscRect chip){
    m_chipRect = chip;
  }
  miscRect& getChipRect(){
    return m_chipRect;
  }
  
 private:
  CDataSet();

  
  miscRect m_baseRect;
  miscRect m_chipRect;
};





#endif
