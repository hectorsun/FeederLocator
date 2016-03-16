#ifndef CTHREAD_H
#define CTHREAD_H

#include <QtWidgets>


class CThread: public QThread{

 public:
  CThread();


 protected:
  void run();


};
#endif
