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
  
  /*
  if ( l_fEventRatio>l_fPaintRatio ){
    m_pPaintRect->setLeft(0);
    m_pPaintRect->setRight(event->size().width());
    int adjHeight = event->size.width()
      *m_pPaintImage->size().height()
      /m_pPaintImage->size().width();
    m_pPaintRect->setTop(event->size.height()/2 - adjHeight/2);
    m_pPaintRect->setBottom(event->size().height()/2 + adjHeight/2);

    
  }else if( l_fEventRatio<l_fPaintRatio ){
    m_pPaintRect->setTop(0);
    m_pPaintRect->setBottom(event->size().height());

    int adjWidth = event->size().height()
      *m_pPaintImage->size().width()
      /m_pPaintImage->size().height(); 

    m_pPaintRect->setLeft(event->size().width()/2 - adjWidth/2);
    m_pPaintRect->setRight(event->size().width()/2 + adjWidth/2);

  }else{
    m_pPaintRect->setRect(rect());
    return;
    }*/
  
}
