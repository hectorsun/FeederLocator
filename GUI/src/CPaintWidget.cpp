#include <CPaintWidget.h>
#include <Camera/CCamera.h>


#include <iostream>
using std::cout;
using std::endl;

CPaintWidget::CPaintWidget(QWidget* paint/*=0*/)
{
  connect(this, SIGNAL(refresh()),
	  this, SLOT(refreshPaint()));

   
  m_pPaintImage = new QImage(QSize(CCamera::getInstance().getWidth(),
				   CCamera::getInstance().getHeight()),
			     QImage::Format_RGB888);
  QPainter imagePainter(m_pPaintImage);
  imagePainter.initFrom(this);
  imagePainter.setRenderHint(QPainter::Antialiasing, true);
  imagePainter.eraseRect(m_pPaintImage->rect());
  imagePainter.drawEllipse(QPoint(m_pPaintImage->width()/2,
				  m_pPaintImage->height()/2),
			   m_pPaintImage->width()/4,
			   m_pPaintImage->width()/4);
  imagePainter.end();

  m_pPaintRect = new QRect();
}


void
CPaintWidget::refreshPaint()
{
  cout<<"CPaintWidget::refreshPaint()"<<endl;

  QImage image(CCamera::getInstance().getData(),
	       CCamera::getInstance().getWidth(),
	       CCamera::getInstance().getHeight(),
	       QImage::Format_RGB888);
  
  QPainter imagePainter(m_pPaintImage);
  imagePainter.initFrom(this);
  imagePainter.setRenderHint(QPainter::Antialiasing, true);
  imagePainter.eraseRect(m_pPaintImage->rect());

  
  imagePainter.drawImage(m_pPaintImage->rect(), image, image.rect());


  imagePainter.end();
  
  update();

}


void
CPaintWidget::paintEvent(QPaintEvent* event){
  //cout<<"CPaintWidget::paintEvent()"<<endl;
  if (m_pPaintImage != NULL){
    QPainter widgetPainter(this);
    
    widgetPainter.drawImage(*m_pPaintRect,*m_pPaintImage);
  }
}

void
CPaintWidget::resizeEvent(QResizeEvent* event){

  
  if (m_pPaintImage->size().height() ==0 ||
      m_pPaintImage->size().height() ==0){
    
    cout<<"CPaintWidget::resizeEvent() ==0"<<endl;
    return;
  }
  float l_fEventRatio = float(event->size().width() ) /
                        float( event->size().height());
  float l_fPaintRatio = float(m_pPaintImage->size().width()) /
                        float(m_pPaintImage->size().height());

  int adjHeight, adjWidth = 0;
  if ( l_fEventRatio<l_fPaintRatio ){
    adjWidth = event->size().width();
    adjHeight = event->size().width()
                *m_pPaintImage->size().height()
                /m_pPaintImage->size().width();
  }else if( l_fEventRatio>l_fPaintRatio ){
    adjWidth = event->size().height()
              *m_pPaintImage->size().width()
              /m_pPaintImage->size().height(); 
    adjHeight = event->size().height();
  }else{
    adjWidth = event->size().width();
    adjHeight = event->size().height();
    return;
  }
  
  m_pPaintRect->setLeft(event->size().width()/2 - adjWidth/2);
  m_pPaintRect->setRight(event->size().width()/2 + adjWidth/2);
  m_pPaintRect->setTop(event->size().height()/2 - adjHeight/2);
  m_pPaintRect->setBottom(event->size().height()/2 + adjHeight/2);
}


void
CPaintWidget::mousePressEvent(QMouseEvent* event)
{
  if (! m_pPaintRect->contains(event->pos())){
    return ;
  }
  origin = event->pos();
  if (!m_pRubberBand){
    m_pRubberBand = new QRubberBand(QRubberBand::Rectangle,this);
  }
  m_pRubberBand->setGeometry(QRect(origin, QSize()));
  m_pRubberBand->show();

}
void
CPaintWidget::mouseMoveEvent(QMouseEvent* event)
{
  if (m_pRubberBand){
    cur = event->pos();
    if (cur.x() < m_pPaintRect->left()){
      cur.setX( m_pPaintRect->left());
    }else if (cur.x() > m_pPaintRect->right()){
      cur.setX(m_pPaintRect->right());
    }

    if (cur.y() < m_pPaintRect->top()){
      cur.setY(m_pPaintRect->top());
    }else if (cur.y() > m_pPaintRect->bottom()){
	cur.setY(m_pPaintRect->bottom());
    }
    m_pRubberBand->setGeometry(QRect(origin, cur).normalized());
  }
}



void
CPaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
  if (m_pRubberBand){
    m_rubberRect=QRect(origin, cur).normalized();
    cout <<"m_rubberRect: "
	 << " top() :"<< m_rubberRect.top()
	 << " bottom():" << m_rubberRect.bottom()
	 << " left(): " << m_rubberRect.left()
	 << " right():" <<m_rubberRect.right()
	 <<endl;

    m_selectedRect.setTop(m_pPaintImage->height()/2 + 
			  (m_rubberRect.top() - m_pPaintRect->height()/2)*
			  m_pPaintImage->height()/m_pPaintRect->height());

    
    m_selectedRect.setBottom(m_pPaintImage->height()/2 + 
			     (m_rubberRect.bottom() - m_pPaintRect->height()/2)*
			     m_pPaintImage->height()/m_pPaintRect->height());

    
    m_selectedRect.setLeft(m_pPaintImage->width()/2 +
			  (m_rubberRect.left() - m_pPaintRect->width()/2)*
			  m_pPaintImage->width()/m_pPaintRect->width());

    
    m_selectedRect.setRight(m_pPaintImage->width()/2 + 
			  (m_rubberRect.right() - m_pPaintRect->width()/2)*
			  m_pPaintImage->width()/m_pPaintRect->width());
  }
}
