#ifndef CSTEPDLG_H
#define CSTEPDLG_H

#include <QtWidgets>
#include <CPaintWidget.h>
#include <QListWidget>


class CStepDlg: public QDialog{
  Q_OBJECT

public:
  CStepDlg(CPaintWidget* pPaint, QListWidget* m_pList, QWidget* parent=0);

private:
  CPaintWidget *m_pPaint;
  QListWidget *m_pList;
};


#endif
