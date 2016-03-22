#include <misc/CDataSet.h>


#include <iostream>
using std::cout;
using std::endl;


CDataSet::CDataSet()
{
  m_baseRect.top =1;
}

int
CDataSet::saveData(const std::string path)
{
  cout << "save configure into file:"<< path<<endl;
  boost::property_tree::ptree pt;

  pt.put("config.file_name", path);
  
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

  loadRect(pt, "config.baseRect", m_baseRect);
  loadRect(pt, "config.chipRect", m_chipRect);

  return 0;
}


void
CDataSet::saveRect(boost::property_tree::ptree& pt, std::string node, miscRect& rect_)
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

  rect_.top  = pt.get<int>(node+".top");
  rect_.bottom  = pt.get<int>(node+".bottom");
  rect_.left  = pt.get<int>(node+".left");
  rect_.right  = pt.get<int>(node+".right");
}
