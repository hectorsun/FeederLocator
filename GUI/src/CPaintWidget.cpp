#include <CPaintWidget.h>
#include <Camera/CCamera.h>


#include <iostream>
using std::cout;
using std::endl;

CPaintWidget::CPaintWidget(QWidget* paint/*=0*/)
{
  connect(this, SIGNAL(refresh()),
	  this, SLOT(refreshPaint()));

  
  m_pImage = new QImage(size(),
			QImage::Format_RGB888);
  QPainter imagePainter(m_pImage);
  imagePainter.initFrom(this);
  imagePainter.setRenderHint(QPainter::Antialiasing, true);
  imagePainter.eraseRect(rect());
  imagePainter.drawEllipse(m_pImage->width()/2, m_pImage->height()/2,
			   m_pImage->width()/2, m_pImage->height()/2);
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
  
  QPainter imagePainter(m_pImage);
  imagePainter.initFrom(this);
  imagePainter.setRenderHint(QPainter::Antialiasing, true);
  imagePainter.eraseRect(rect());
  imagePainter.drawImage(rect(), image, image.rect());
  imagePainter.end();
  
  update();

}


void
CPaintWidget::paintEvent(QPaintEvent* event){
  //cout<<"CPaintWidget::paintEvent()"<<endl;
  if (m_pImage != NULL){
    QPainter widgetPainter(this);
    widgetPainter.drawImage(*m_pPaintRect,*m_pImage);
  }
}

void
CPaintWidget::resizeEvent(QResizeEvent* event){
  m_pImage->scaled(event->size());

  m_pPaintRect->setRect(0,
			0,
			event->size().width(),
			event->size().height());
}
