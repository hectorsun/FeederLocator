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
  QHBoxLayout *topLayout = new QHBoxLayout();
  m_pButtonShow = new QPushButton(tr("show"));
  connect(m_pButtonShow, SIGNAL(clicked()),
	  this, SLOT(showRubber()));
  topLayout->addWidget(m_pButtonShow);
    
  m_pButtonTest = new QPushButton(tr("test"));
  connect(m_pButtonTest, SIGNAL(clicked()),
	  this, SLOT(test()));

  topLayout->addWidget(m_pButtonTest);

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
  const QRect& rect = m_pPaint->getSelectedRect();

  imgTest(CCamera::getInstance().getData(),
	  CCamera::getInstance().getWidth(),
	  CCamera::getInstance().getHeight(),
	  rect.top(),
	  rect.bottom(),
	  rect.left(),
	  rect.right());
  
}
