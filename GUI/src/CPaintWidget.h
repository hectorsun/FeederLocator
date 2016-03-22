#ifndef CPAINT_WIDGET_H
#define CPAINT_WIDGET_H

#include <QtWidgets>
#include <QListWidget>
class CPaintWidget : public QWidget{
  Q_OBJECT
public:
  /**
     @brief construction function
   */
  CPaintWidget(QListWidget* pList,QWidget* parent = 0);


  QRect& getSelectedRect(){return m_selectedRect;}

  /**
     @breif 
  */
  void setRubberVisible(bool visible);

  /**
     @brief show mode
   */
  enum showMode{
    onlyImage = 0,
    withLocateArea,
    withOneChip,
    withTwoChip,
    withBase,
    withBaseAndChip,
  };
  
  /**
     @brief set show mode
   */
  void setShowMode(showMode mode){m_mode = mode;}

  void setOneChip(const QRect& roi_, const QRect& pos_)
  {
    m_firstChipRoi = roi_;
    m_firstChipPos = pos_;
  }

  void setTwoChip(const QRect& roi1_, const QRect& pos1_,
		  const QRect& roi2_, const QRect& pos2_)
  {
    m_firstChipRoi = roi1_;
    m_firstChipPos = pos1_;
    m_secondChipRoi = roi2_;	
    m_secondChipPos = pos2_;
  }

  void setBase(const QRect& roi_, const QRect& pos_){
    m_baseRoi = roi_;
    m_basePos = pos_;

  }
  
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

  /** @brief conv from gui to image
   */
  QPoint guiToImg(const QPoint& _point);

  /** @brief conv from image to gui
   */
  QPoint imgToGui(const QPoint& _point);
private:
  QListWidget* m_pList;
  
  QImage* m_pPaintImage;//< image to paint in the screen
  QRect*  m_pPaintRect; //< reactangle of target when paint
  QRubberBand* m_pRubberBand;
  QPoint origin;
  QPoint cur;
  QRect m_rubberRect;  //< selected rect in widget coordinate
  QRect m_selectedRect;//< selected rect in Image coordinate

  bool m_bRubberVisible;
  showMode m_mode;

  QRect m_firstChipRoi;
  QRect m_firstChipPos;
  QRect m_secondChipRoi;
  QRect m_secondChipPos;
  
  QRect m_baseRoi;
  QRect m_basePos;

  QPen m_penRoi;
  QPen m_penPos;
  QPen m_penCross;
};
#endif
