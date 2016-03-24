#include <CSettingDlg.h>
#include <iostream>
using std::cout;
using std::endl;

#include <imgProc/imgProc.h>
#include <Camera/CCamera.h>
#include <misc/CDataSet.h>

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
  imgRect roi = imgRect(l_rectSelected.top(),
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
  imgRect roi = imgRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  imgRect result;
  int err;
  if (0 != (err =imgChipLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    // failed to  locate chip
    int r = QMessageBox::warning(this, tr("set first chip"),
				 tr("Failed to locate chip in the area\n"
				    "please setting again"),
				 QMessageBox::Yes);
    return;
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
  //m_pList->addItem("setSecondChip");
  const QRect& l_rectSelected = m_pPaint->getSelectedRect();
  imgRect roi = imgRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  imgRect result;
  int err;
  if (0 != (err =imgChipLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    // Failed to  locate chip
    int r = QMessageBox::warning(this, tr("set second chip"),
				 tr("Failed to locate chip in the area\n"
				    "please setting again"),
				 QMessageBox::Yes);

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
  imgRect roi1 = imgRect(m_firstChip.top(),
			  m_firstChip.bottom(),
			  m_firstChip.left(),
			  m_firstChip.right());
  imgRect roi2 = imgRect(m_secondChip.top(),
			  m_secondChip.bottom(),
			  m_secondChip.left(),
			  m_secondChip.right());
  imgRect result1, result2;
  
  int err1 =imgChipLocate(CCamera::getInstance().getData(),
			  CCamera::getInstance().getWidth(),
			  CCamera::getInstance().getHeight(),
			  roi1, &result1);

  int err2 =imgChipLocate(CCamera::getInstance().getData(),
			  CCamera::getInstance().getWidth(),
			  CCamera::getInstance().getHeight(),
			  roi2, &result2);			       

  if (err1 == 0 && err2 ==0){
     QRect l_qRes1;
    l_qRes1.setTop(result1.top);
    l_qRes1.setBottom(result1.bottom);
    l_qRes1.setLeft(result1.left);
    l_qRes1.setRight(result1.right);

    QRect l_qRes2;
    l_qRes2.setTop(result2.top);
    l_qRes2.setBottom(result2.bottom);
    l_qRes2.setLeft(result2.left);
    l_qRes2.setRight(result2.right);

    m_pPaint->setTwoChip(m_firstChip, l_qRes1, m_secondChip, l_qRes2);
    m_pPaint->setShowMode(CPaintWidget::withTwoChip);
    emit m_pPaint->refresh();

  }else{


  }
  

}



/************************************************************\

\************************************************************/
CSettingBaseAndChip::CSettingBaseAndChip(CPaintWidget* pPaint, QListWidget* pList ,QWidget* parent)
  : m_pPaint(pPaint),
    m_pList(pList),
    QWidget(parent)
{

  QVBoxLayout *topLayout = new QVBoxLayout(this);

  m_pButtonSetBaseArea = new QPushButton("Set base area");
  connect(m_pButtonSetBaseArea, SIGNAL(clicked()),
	  this, SLOT(setBaseArea()));
  topLayout->addWidget(m_pButtonSetBaseArea);
  
  m_pButtonSetChipArea = new QPushButton("Set Locate Area");
  connect(m_pButtonSetChipArea, SIGNAL(clicked()),
	  this, SLOT(setChipArea()));
  topLayout->addWidget(m_pButtonSetChipArea);

  this->setLayout(topLayout);
}


void
CSettingBaseAndChip::setBaseArea(){
  const QRect& l_rectSelected = m_pPaint->getSelectedRect();
#if 1
  m_pPaint->setBase(l_rectSelected, l_rectSelected);
  m_pPaint->setShowMode(CPaintWidget::withBase);
  m_pPaint->refreshPaint();
#else
  imgRect roi = imgRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  imgRect result;
  int err;
  if (0 != (err =imgBaseLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    // Failed to  locate chip
    int r = QMessageBox::warning(this, tr("set base area"),
				 tr("Failed to locate chip in the area\n"
				    "please setting again"),
				 QMessageBox::Yes);

  }
  else{
    CDataSet::getInstance().setChipRect(roi);

    QRect l_qRes;
    l_qRes.setTop(result.top);
    l_qRes.setBottom(result.bottom);
    l_qRes.setLeft(result.left);
    l_qRes.setRight(result.right);
    
    m_pPaint->setBase(l_rectSelected, l_qRes);
    m_pPaint->setShowMode(CPaintWidget::withBase);
    emit m_pPaint->refresh();
  }
#endif
}

void
CSettingBaseAndChip::setChipArea(){
 const QRect& l_rectSelected = m_pPaint->getSelectedRect();
  imgRect roi = imgRect(l_rectSelected.top(),
			  l_rectSelected.bottom(),
			  l_rectSelected.left(),
			  l_rectSelected.right());
  imgRect result;
  int err;
  if (0 != (err =imgChipLocate(CCamera::getInstance().getData(),
			       CCamera::getInstance().getWidth(),
			       CCamera::getInstance().getHeight(),
			       roi, &result))){
    // Failed to  locate chip
    int r = QMessageBox::warning(this, tr("set second chip"),
				 tr("Failed to locate chip in the area\n"
				    "please setting again"),
				 QMessageBox::Yes);

  }
  else{
    CDataSet::getInstance().setChipRect(roi);

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
