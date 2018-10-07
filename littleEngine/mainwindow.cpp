#include "mainwindow.h"
#include <QKeyEvent>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>

#include "../PBR_d12/Setting.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

	littlemm::Setting::Height = 960;
	littlemm::Setting::Width = 720;

	
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("littleEngine"));
	this->resize(1000, 1000);
	centralwidget = new QWidget(this);
	centralwidget->setObjectName(QStringLiteral("rendertarget"));
	render = new QWidget(centralwidget);
	render->setObjectName(QStringLiteral("widget"));
	render->setGeometry(QRect(260, 130, littlemm::Setting::Width, littlemm::Setting::Height));
	

	this->setCentralWidget(centralwidget);
	menubar = new QMenuBar(this);
	menubar->setObjectName(QStringLiteral("menubar"));
	menubar->setGeometry(QRect(0, 0, 969, 23));
	this->setMenuBar(menubar);
	statusbar = new QStatusBar(this);
	statusbar->setObjectName(QStringLiteral("statusbar"));
	this->setStatusBar(statusbar);

	engine = new littlemm::LittleEngineResource((HWND)render->winId());
	//render.setGeometry(QRect(80, 130, 321, 291));

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	engine->Initialize();
	engine->mTimer.Reset();
	engine->mTimer.Start();
	//engine((HWND)winId());
	//	engine.Initialize();

}

void MainWindow::paintEvent(QPaintEvent* event)
{
	engine->CalculateFrameStats();
	engine->mTimer.Tick();
	//printf("%f", mTimer.TotalTime());

	OutputDebugString((std::to_wstring(engine->mTimer.TotalTime())+L"\n").c_str());

	engine->Update(engine->mTimer);
	engine->Draw(engine->mTimer);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	littlemm::Setting::Height = height();
	littlemm::Setting::Width = width();
	engine->OnResize();
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
	engine->OnKeyboardInput(engine->mTimer);

}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	int key = event->button();

 	//if (key == Qt::LeftButton)
		engine->OnMouseMove(MK_LBUTTON, event->x(), event->y());
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	engine->OnMouseDown(0, event->x(), event->y());
}


void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	engine->OnMouseUp(0, 0, 0);
}





MainWindow::~MainWindow()
{

}
