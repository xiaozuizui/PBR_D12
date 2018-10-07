#pragma once
#include <QtWidgets/QWidget>


class RenderTarget:public QWidget
{
	Q_OBJECT
public:
	RenderTarget(QWidget *parent = 0);
	~RenderTarget();



public :

	void update();

};
