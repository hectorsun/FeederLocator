#include <CSettingDlg.h>
#include <iostream>
using std::cout;
using std::endl;

#include <misc/imgProc.h>
#include <Camera/CCamera.h>

CSettingDlg::CSettingDlg(CPaintWidget* pPaint,QWidget* parent)
  :QDialog(parent),
   m_pPaint(pPaint)
{
  this->setWindowTitle(tr("setting"));
  
  QVBoxLayout *topLayout = new QVBoxLayout();

  m_pButtonShow = new QPushButton(tr("show"));
  connect(m_pButtonShow, SIGNAL(clicked()),
	  this, SLOT(showRubber()));
  topLayout->addWidget(m_pButtonShow);
    
  m_pButtonTest = new QPushButton(tr("test"));
  connect(m_pButtonTest, SIGNAL(clicked()),
	  this, SLOT(test()));

  topLayout->addWidget(m_pButtonTest);

  m_pButtonSetFirstChip = new QPushButton("First chip");
  connect(m_pButtonSetFirstChip, SIGNAL(clicked()),
	  this, SLOT(setFirstChip()));
  topLayout->addWidget(m_pButtonSetFirstChip);
  
  m_pButtonSetSecondChip = new QPushButton("Second chip");
  connect(m_pButtonSetSecondChip, SIGNAL(clicked()),
	  this, SLOT(setSecondtChip()));
  topLayout->addWidget(m_pButtonSetSecondChip);

  m_pButtonGetWidthOfPixel = new QPushButton("get width of pixel");
  connect(m_pButtonGetWidthOfPixel, SIGNAL(clicked()),
	  this, SLOT(getWidthOfPixel()));
  topLayout->addWidget(m_pButtonGetWidthOfPixel);

  m_pButtonGetLocateArea = new QPushButton("Get Locate Area");
  connect(m_pButtonGetLocateArea, SIGNAL(clicked()),
	  this, SLOT(getLocateArea()));
  topLayout->addWidget(m_pButtonGetLocateArea);
  
  this->setLayout(topLayout);
}

void
CSettingDlg::showRubber()
{
  static bool visible = false;
  visible = !visible;
  m_pButtonShow->setText(visible?
			 tr("hidden") :
			 tr("show"));
  m_pPaint->setRubberVisible(visible);
}
void
CSettingDlg::test()
{
  cout << "CSettingDlg::test()"<<endl;
  const QRect& l_rectSelected = m_pPaint->getSelectedRect();
  miscRect roi = miscRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  imgTest(CCamera::getInstance().getData(),
	  CCamera::getInstance().getWidth(),
	  CCamera::getInstance().getHeight(),
	  roi);
  
}

void
CSettingDlg::setFirstChip(){
  const QRect& l_rectSelected = m_pPaint->getSelectedRect();
  miscRect roi = miscRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  miscRect result;
  int err;
  if (0 !=(err = imgChipLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    
  }else{
    m_firstChip = l_rectSelected;
  }
}

void
CSettingDlg::setSecondChip(){
const QRect& l_rectSelected = m_pPaint->getSelectedRect();
  miscRect roi = miscRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  miscRect result;
  int err;
  if (0 != (err =imgChipLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    // failed to  locate chip

  }
  else{
    // success to locate chip
    m_secondChip = l_rectSelected;
  }

}

void
CSettingDlg::getWidthOfPixel(){
  
}

void
CSettingDlg::getLocateArea(){

}
