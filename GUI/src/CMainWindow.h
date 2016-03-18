#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <CPaintWidget.h>
#include <QListWidget>
#include <QToolBar>
#include <CThread.h>

class CMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CMainWindow();

private slots:
  void snapAPicture();

  
private:
  void createActions();
  void createToolBars();
  //
  CPaintWidget * m_pPaint;
  QListWidget *m_pList;
  QToolBar *m_pEditToolBar;
  CThread* m_pThread;

  
  // actions
  QAction *m_pSnapAPictureAction;
  QAction *m_pStartProcessAction;
  QAction *m_pStopProcessAction;

};
#endif //CMAINWIDONW_H
