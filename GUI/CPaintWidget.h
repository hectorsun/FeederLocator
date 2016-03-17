#ifndef CPAINT_WIDGET_H
#define CPAINT_WIDGET_H

#include <QtWidgets>

class CPaintWidget : public QWidget{
  Q_OBJECT
public:
  CPaintWidget(QWidget* parent = 0);

signals:
  void refresh();
		
private slots:
  void refreshPaint();
  
protected:
  void paintEvent(QPaintEvent* event);
  void resizeEvent(QResizeEvent* event);

private:
  QImage* m_pImage;
  QRect* m_pPaintRect;
  
};
#endif
