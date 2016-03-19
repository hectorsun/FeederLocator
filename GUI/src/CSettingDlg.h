#ifndef _CSETTING_DLG_H
#define _CSETTING_DLG_H


#include <QtWidgets>
#include <CPaintWidget.h>

class CSettingDlg : public QDialog{
Q_OBJECT
public:
 CSettingDlg(CPaintWidget* pPaint , QWidget *parent=0);
						      
private slots:
  void test();
private:
  CPaintWidget* m_pPaint;
  QPushButton * m_pButtonTest;
};
#endif
