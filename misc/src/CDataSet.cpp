#include <misc/CDataSet.h>


#include <iostream>
using std::cout;
using std::endl;


CDataSet::CDataSet()
{
  m_baseRect.top =1;
  m_dWidthOfPixel = 0.1;
}

int
CDataSet::saveData(const std::string path)
{
  cout << "save configure into file:"<< path<<endl;
  boost::property_tree::ptree pt;
  
  pt.put("config.file_name", path);

  
  pt.put("config.Width_Of_Pixel", m_dWidthOfPixel);
  saveRect(pt, std::string("config.baseRect"), m_baseRect);
  saveRect(pt, std::string("config.chipRect"), m_chipRect);
  
  boost::property_tree::write_xml(path, pt);
  return 0;
}

  
int
CDataSet::loadData(const std::string path)
{
  cout << "load configure from file:" << path << endl;
  boost::property_tree::ptree pt;
  boost::property_tree::read_xml(path, pt);

  m_dWidthOfPixel = pt.get<double>("config.Width_Of_Pixel");
  
  loadRect(pt, "config.baseRect", m_baseRect);
  loadRect(pt, "config.chipRect", m_chipRect);

  return 0;
}


void
CDataSet::saveRect(boost::property_tree::ptree& pt,
		   std::string node,
		   const miscRect& rect_)
{
  pt.put(node+".top",rect_.top);
  pt.put(node+".bottom",rect_.bottom);
  pt.put(node+".left",rect_.left);
  pt.put(node+".right",rect_.right);

}


void
CDataSet::loadRect(boost::property_tree::ptree& pt,
		   std::string node,
		   miscRect& rect_){

  rect_.top     = pt.get<int>(node+".top");
  rect_.bottom  = pt.get<int>(node+".bottom");
  rect_.left    = pt.get<int>(node+".left");
  rect_.right   = pt.get<int>(node+".right");
}


void
CDataSet::savePoint(boost::property_tree::ptree& pt,
		    std::string node,
		    const miscPoint& point_){
  pt.put(node+".x", point_.x);
  pt.put(node+".y", point_.y);
}

void
CDataSet::loadPoint(boost::property_tree::ptree& pt,
		    std::string node,
		    miscPoint& point_){
  point_.x = pt.get<int>(node+".x");
  point_.y = pt.get<int>(node+".y");
}
