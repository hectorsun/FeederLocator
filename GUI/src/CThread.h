#ifndef CTHREAD_H
#define CTHREAD_H

#include <QtWidgets>


class CThread: public QThread{
  Q_OBJECT
 public:
  CThread();


 protected:
  void run();


};
#endif
