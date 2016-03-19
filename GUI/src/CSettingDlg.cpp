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
  m_pButtonTest = new QPushButton(tr("test"));
  connect(m_pButtonTest, SIGNAL(clicked()),
	  this, SLOT(test()));
  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addWidget(m_pButtonTest);

  this->setLayout(topLayout);
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
