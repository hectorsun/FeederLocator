#ifndef CDATASET_H
#define CDATASET_H

#include <string>
#include "miscdef.h"
#include <imgProc/imgProc.h>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>


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

  void setWidthOfPixel(double w_){
    m_dWidthOfPixel = w_;
  }

  double getWidthOfPixel(){
    return m_dWidthOfPixel;
  }
  /**
  
   */
  void setBaseRect(const imgRect base){
    m_baseRect = base;
  }
  imgRect& getBaseRect(){
    return m_baseRect;
  }

  void setChipRect(const imgRect chip){
    m_chipRect = chip;
  }
  imgRect& getChipRect(){
    return m_chipRect;
  }
  
 private:
  CDataSet();

  /**
   */
  void saveRect(boost::property_tree::ptree& pt,
		std::string node,
		const imgRect& rect_);
  /**
   */
  void loadRect(boost::property_tree::ptree& pt,
		std::string node,
		imgRect& rect_);

  /**
   */
  void savePoint(boost::property_tree::ptree& pt,
		 std::string node,
		 const imgPoint& point_);

  /**
   */  
  void loadPoint(boost::property_tree::ptree& pt,
		 std::string node,
		 imgPoint& point_);
private:
  double   m_dWidthOfPixel;
  imgRect m_baseRect;
  imgRect m_chipRect;
};





#endif
