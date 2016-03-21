#include <CSettingDlg.h>
#include <iostream>
using std::cout;
using std::endl;

#include <misc/imgProc.h>
#include <Camera/CCamera.h>

CSettingDlg::CSettingDlg(CPaintWidget* pPaint,  QListWidget *pList,QWidget* parent)
  :QDialog(parent),
   m_pPaint(pPaint),
   m_pList(pList)
{
  this->setWindowTitle(tr("setting"));
  
  QVBoxLayout *topLayout = new QVBoxLayout();

  m_pButtonShow = new QPushButton(tr("show"));
  connect(m_pButtonShow, SIGNAL(clicked()),
	  this, SLOT(showRubber()));
  topLayout->addWidget(m_pButtonShow);

  m_pTabWidget = new QTabWidget(this);
  m_pTabWidget->addTab(new CSettingGetWidthOfPixel(m_pPaint, m_pList, this),
		       tr("width of pixel"));
  m_pTabWidget->addTab(new CSettingBaseAndChip(m_pPaint, m_pList, this),
		       tr("Base and chip"));
  topLayout->addWidget(m_pTabWidget);
  /*
  
  m_pButtonTest = new QPushButton(tr("test"));
  connect(m_pButtonTest, SIGNAL(clicked()),
	  this, SLOT(test()));

  topLayout->addWidget(m_pButtonTest);

  

  
  */
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





/************************************************************\

\************************************************************/
CSettingGetWidthOfPixel::CSettingGetWidthOfPixel(CPaintWidget* pPaint, QListWidget* pList ,QWidget* parent)
  : m_pPaint(pPaint),
    m_pList(pList),
    QWidget(parent){

  QVBoxLayout *topLayout = new QVBoxLayout(this);

  
  m_pButtonSetFirstChip = new QPushButton("First chip");
  connect(m_pButtonSetFirstChip, SIGNAL(clicked()),
	  this, SLOT(setFirstChip()));
  topLayout->addWidget(m_pButtonSetFirstChip);
  
  m_pButtonSetSecondChip = new QPushButton("Second chip");
  connect(m_pButtonSetSecondChip, SIGNAL(clicked()),
	  this, SLOT(setSecondChip()));
  topLayout->addWidget(m_pButtonSetSecondChip);

  m_pButtonGetWidthOfPixel = new QPushButton("get width of pixel");
  connect(m_pButtonGetWidthOfPixel, SIGNAL(clicked()),
	  this, SLOT(getWidthOfPixel()));
  topLayout->addWidget(m_pButtonGetWidthOfPixel);

  this->setLayout(topLayout);
}


void
CSettingGetWidthOfPixel::setFirstChip(){
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
    m_firstChip = l_rectSelected;

    QRect l_qRes;
    l_qRes.setTop(result.top);
    l_qRes.setBottom(result.bottom);
    l_qRes.setLeft(result.left);
    l_qRes.setRight(result.right);

    
    m_pPaint->setOneChip(l_rectSelected, l_qRes);
    m_pPaint->setShowMode(CPaintWidget::withOneChip);
    emit m_pPaint->refresh();
  }
}

void
CSettingGetWidthOfPixel::setSecondChip(){
  m_pList->addItem("setSecondChip");
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

    QRect l_qRes;
    l_qRes.setTop(result.top);
    l_qRes.setBottom(result.bottom);
    l_qRes.setLeft(result.left);
    l_qRes.setRight(result.right);

    
    m_pPaint->setOneChip(l_rectSelected, l_qRes);
    m_pPaint->setShowMode(CPaintWidget::withOneChip);
    emit m_pPaint->refresh();
  }

}

void
CSettingGetWidthOfPixel::getWidthOfPixel(){
  
}



/************************************************************\

\************************************************************/
CSettingBaseAndChip::CSettingBaseAndChip(CPaintWidget* pPaint, QListWidget* pList ,QWidget* parent)
  : m_pPaint(pPaint),
    m_pList(pList),
    QWidget(parent)
{

  QVBoxLayout *topLayout = new QVBoxLayout(this);

  
  m_pButtonGetLocateArea = new QPushButton("Get Locate Area");
  connect(m_pButtonGetLocateArea, SIGNAL(clicked()),
	  this, SLOT(getLocateArea()));
  topLayout->addWidget(m_pButtonGetLocateArea);

  this->setLayout(topLayout);
}


void
CSettingBaseAndChip::getLocateArea(){

}
