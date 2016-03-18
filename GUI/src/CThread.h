#ifndef CTHREAD_H
#define CTHREAD_H

#include <QtWidgets>
#include <QThread>


/** @breif: thread class

The class include thread functions, which can be  

*/
class CThread : public QThread{
  Q_OBJECT
  
public:
  /**
     constructure function
   */
  CThread(QListWidget* pList, QObject *parent=0);

  /**
     @brief make thread start process
   */
  void startProcess();

  /**
     @brief make thread stop process
   */
  void stopProcess();

  /**
     @brief make thread quit
   */
  void quitThread();
protected:
  /** @brief thread function
   */
  void run() Q_DECL_OVERRIDE;
private:
  QListWidget* m_pList;//< log widget

};
#endif
