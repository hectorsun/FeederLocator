#include <misc/CDataSet.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>

#include <iostream>
using std::cout;
using std::endl;


CDataSet::CDataSet()
{

}

int
CDataSet::saveData(const std::string path)
{
  cout << "save configure into file:"<< path<<endl;
  boost::property_tree::ptree pt;

  pt.put("config.file_name", path);

  pt.put("config.baseRect.top",m_baseRect.top);
  pt.put("config.baseRect.bottom",m_baseRect.bottom);
  pt.put("config.baseRect.left",m_baseRect.left);
  pt.put("config.baseRect.right",m_baseRect.right);

  pt.put("config.chipRect.top",m_chipRect.top);
  pt.put("config.chipRect.bottom",m_chipRect.bottom);
  pt.put("config.chipRect.left",m_chipRect.left);
  pt.put("config.chipRect.right",m_chipRect.right);
  

  boost::property_tree::write_xml(path, pt);
  return 0;
}

  
int
CDataSet::loadData(const std::string path)
{
  cout << "load configure from file:" << path << endl;
  boost::property_tree::ptree pt;
  boost::property_tree::read_xml(path, pt);

  m_baseRect.top  = pt.get<int>("config.baseRect.top");
  m_baseRect.bottom  = pt.get<int>("config.baseRect.bottom");
  m_baseRect.left  = pt.get<int>("config.baseRect.left");
  m_baseRect.right  = pt.get<int>("config.baseRect.right");

  m_chipRect.top  = pt.get<int>("config.chipRect.top");
  m_chipRect.bottom  = pt.get<int>("config.chipRect.bottom");
  m_chipRect.left  = pt.get<int>("config.chipRect.left");
  m_chipRect.right  = pt.get<int>("config.chipRect.right");
  

  return 0;
}
