#ifndef CTHREAD_H
#define CTHREAD_H

#include <QtWidgets>
#include <QThread>
#include <CPaintWidget.h>

/** @breif: thread class

The class include thread functions, which can be  

*/
class CThread : public QThread{
  Q_OBJECT
  
public:
  /**
     constructure function
   */
  CThread(QListWidget* pList, CPaintWidget* pPaint,QObject *parent=0);

  enum runMode{
    modeIdle=0,
    modeProcess,
    modeCapture,
    modeQuit,
  };

  bool isCapturing() {return m_curMode == modeCapture;}
public slots:
  /**
     @brief make thread start process
   */
  void startProcess();

  /**
     @brief make thread stop process
   */
  void stopProcess();

  /**
   */
  void startCapture();
  /**
   */
  void stopCapture();

  /**
     @brief make thread quit
   */
  void quitThread();
protected:
  /** @brief thread function
   */
  void run() Q_DECL_OVERRIDE;

private:
  void process();
  void capture();

private:


  QListWidget* m_pList;//< log widget
  CPaintWidget* m_pPaint;

  // wakeup and quit thread
  QMutex m_muxWakeup;
  bool m_bWakeup;
  bool m_bQuit;
  QWaitCondition m_cndWakeup;

  // stop process
  QMutex m_muxStop;
  bool m_bStop;
  QWaitCondition m_cndStop;
  
  // feedback
  QMutex m_muxFeedback;
  bool m_bFeedback;
  QWaitCondition m_cndFeedback;

  // status
  QMutex m_muxStatus;
  runMode m_curMode;
  runMode m_nextMode;
};
#endif
