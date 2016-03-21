#ifndef _CSETTING_DLG_H
#define _CSETTING_DLG_H


#include <QtWidgets>
#include <CPaintWidget.h>

class CSettingDlg : public QDialog{
Q_OBJECT
public:
 CSettingDlg(CPaintWidget* pPaint , QWidget *parent=0);
						      
private slots:
  void showRubber();
  void test();
  void setFirstChip();
  void setSecondChip();
  void getWidthOfPixel();
  void getLocateArea();
private:
  CPaintWidget* m_pPaint;
  QPushButton *m_pButtonShow;
  QPushButton *m_pButtonTest;
  QPushButton *m_pButtonSetFirstChip;
  QPushButton *m_pButtonSetSecondChip;
  QPushButton *m_pButtonGetWidthOfPixel;

  QPushButton *m_pButtonGetLocateArea;
  
  QRect m_firstChip;
  QRect m_secondChip;
};
#endif
