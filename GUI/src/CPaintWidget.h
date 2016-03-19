#ifndef CPAINT_WIDGET_H
#define CPAINT_WIDGET_H

#include <QtWidgets>

class CPaintWidget : public QWidget{
  Q_OBJECT
public:
  /**
     @brief construction function
   */
  CPaintWidget(QWidget* parent = 0);


    QRect& getSelectedRect(){return m_selectedRect;}
signals:
  /**
     @brief make refreshPaint()function called to update m_pPaintImage
   */
  void refresh();
		
private slots:
  /**
     @breif update m_pPaintImage
   */
  void refreshPaint();
  
protected:
  /**
     @breif event function to paint

     this function will put m_pImage in the area(defined by m_pPaintRect) 
     of widget.
   */
  void paintEvent(QPaintEvent* event);

  /**
     @brief event function to resize the widget

     this function will adjust m_pPaintRect, which force m_pPaintImage 
     has same rotate as in the screen
     
   */
  void resizeEvent(QResizeEvent* event);

  /**
   */
  void mousePressEvent(QMouseEvent* event);

  /**
   */
  void mouseMoveEvent(QMouseEvent* event);

  /**
   */
  void mouseReleaseEvent(QMouseEvent* event);


private:
  QImage* m_pPaintImage;//< image to paint in the screen
  QRect*  m_pPaintRect; //< reactangle of target when paint
  QRubberBand* m_pRubberBand;
  QPoint origin;
  QPoint cur;
  QRect m_rubberRect;
  QRect m_selectedRect;
};
#endif
