#ifndef CDATASET_H
#define CDATASET_H

#include <string>
#include "miscdef.h"

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
 private:
  CDataSet();

};





#endif
