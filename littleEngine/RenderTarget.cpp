#include "RenderTarget.h"


RenderTarget::RenderTarget(QWidget *parent):QWidget(parent)
{

	//QObject::connect(this, this->DrawComplete(), this, this->update());

}


RenderTarget::~RenderTarget()
{
	
}



//自定义槽函数
void RenderTarget::update()
{
	QWidget::update();
	//emit drawcomplete();
}



