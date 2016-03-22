#include <CStepDlg.h>


CStepDlg::CStepDlg(CPaintWidget* pPaint, QListWidget* pList, QWidget* parent)
  : QDialog(parent),
    m_pPaint(pPaint),
    m_pList(pList)
{

  this->setWindowTitle(tr("step"));
}
