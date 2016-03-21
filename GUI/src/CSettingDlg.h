#ifndef _CSETTING_DLG_H
#define _CSETTING_DLG_H


#include <QtWidgets>
#include <CPaintWidget.h>

class CSettingDlg : public QDialog{
Q_OBJECT
public:
 CSettingDlg(CPaintWidget* pPaint ,  QListWidget *pList, QWidget *parent=0);
						      
private slots:
  void showRubber();
  void test();


private:
  // other widget
  CPaintWidget* m_pPaint;
  QListWidget *m_pList;

  QTabWidget *m_pTabWidget;
  
  QPushButton *m_pButtonShow;
  QPushButton *m_pButtonTest;


  

};


class CSettingGetWidthOfPixel : public QWidget{
  Q_OBJECT
 public:
  CSettingGetWidthOfPixel(CPaintWidget* pPaint, QListWidget* pList ,QWidget* parent=0);

private slots:
  void setFirstChip();
  void setSecondChip();
  void getWidthOfPixel();
  
 private:
  CPaintWidget* m_pPaint;
  QListWidget *m_pList;

  QPushButton *m_pButtonSetFirstChip;
  QPushButton *m_pButtonSetSecondChip;
  QPushButton *m_pButtonGetWidthOfPixel;

    
  QRect m_firstChip;
  QRect m_secondChip;  
};


class CSettingBaseAndChip : public QWidget{
  Q_OBJECT
public:
  CSettingBaseAndChip(CPaintWidget* pPaint, QListWidget* pList ,QWidget* parent=0);

private slots:
  void setBaseArea();
  void setChipArea();


private:
  CPaintWidget* m_pPaint;
  QListWidget *m_pList;

  QPushButton *m_pButtonSetBaseArea;
  QPushButton *m_pButtonSetChipArea;
};
#endif
