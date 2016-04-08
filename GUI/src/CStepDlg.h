#ifndef CSTEPDLG_H
#define CSTEPDLG_H
//#define WIN32_LEAN_AND_MEAN 
//#include <misc/CSuperTerminal.h>
#include <misc/CSuperTerminal.h>
#include <QtWidgets>
#include <QListWidget>
#include <QMessageBox>


#include <CPaintWidget.h>
//#include <CSuperTerminal.h>


class CStepDlg : public QDialog{
Q_OBJECT


public:
  CStepDlg(CPaintWidget* pPaint, QListWidget* m_pList ,QWidget* parent=0);
  
private:
  CPaintWidget *m_pPaint;
  QListWidget *m_pList;
  //SuperTerminal sp;

  QTabWidget *m_pTabWidget;
  QPushButton *m_pButtonMove;//移动
  QPushButton *m_pButtonRecord;//记录
  QPushButton *m_pButtonErrnum;//无法矫正齿位
  QPushButton *m_pButtonZerocorrect;//零位调整
  QPushButton *m_pButtonSinglecorrect;//单齿调整
  QPushButton *m_pButtonDatareset;//数据重置
  QPushButton *m_pButtonForward;//前进
  QPushButton *m_pButtonBackward;//后退
  QPushButton *m_pButtonReset;//复位

  QComboBox *m_pComboPace;//布距下拉框
  QComboBox *m_pComboDataReset;//数据重置下拉框

  QLabel *m_pLabelPace;
  
  QLineEdit *m_pLineMove;//移动lineedit
  QTextEdit *m_pTextShow;


  QMessageBox *m_pBoxMove1;
  QMessageBox *m_pBoxMove2;


 // QPushButton *m_pButtonTest;	
  
  short MoveValueSum;//用于零位调整和单齿调整的和
  char MoveValue;//
  int CorrectNum;//用于矫正计数
  int GearNum;


  //全局变量
  int fd;
  //struct termios oldtio,newtio;
 // char buf[256];
  /**********slot function**********/
private slots:	
  void MoveButton();//移动slot
  void RecordButton();//记录slot
  void ErrnumButton();//无法矫正齿位slot
  void ZerocorrectButton();//零位调整slot
  void SinglecorrectButton();//单齿调整slot
  void DataresetButton();//数据重置slot
  void ForwardButton();//前进slot
  void BackwardButton();//后退slot
  void ResetButton();//复位slot
  void setPosition();
 // void ComReceive();
 // void ComSend(char* string);
 // void ComOpen();
 // void openCom();
 // void test();
};


#endif
