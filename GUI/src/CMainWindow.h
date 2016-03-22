#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <CPaintWidget.h>
#include <QListWidget>
#include <QToolBar>
#include <CThread.h>
#include <CSettingDlg.h>
#include <CStepDlg.h>


class CMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CMainWindow();

private slots:
  void snapAPicture();
  
  /**@brief setting data
   */
  void setting();

  /** @brief save data into disk
   */
  void saveData();

  /** @brief load data into disk
   */
  void loadData();

  /**
   */
  void step();
private:
  void createActions();
  void createToolBars();
  void createStatusBar();
  
  //
  CPaintWidget *m_pPaint;
  QListWidget  *m_pList;
  QToolBar     *m_pEditToolBar;
  CThread      *m_pThread;
  CSettingDlg  *m_pSettingDlg;
  CStepDlg     *m_pStepDlg;

  
  // actions
  QAction *m_pSnapAPictureAction;
  QAction *m_pStartProcessAction;
  QAction *m_pStopProcessAction;
  QAction *m_pSettingAction;
  QAction *m_pSaveDataAction;
  QAction *m_pLoadDataAction;
  QAction *m_pStepAction;
};
#endif //CMAINWIDONW_H
