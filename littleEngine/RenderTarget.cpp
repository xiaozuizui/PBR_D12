#include "RenderTarget.h"


RenderTarget::RenderTarget(QWidget *parent):QWidget(parent)
{

	//QObject::connect(this, this->DrawComplete(), this, this->update());

}


RenderTarget::~RenderTarget()
{
	
}



//�Զ���ۺ���
void RenderTarget::update()
{
	QWidget::update();
	//emit drawcomplete();
}



