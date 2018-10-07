#include "mainwindow.h"
#include <QKeyEvent>
#include <QWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include "../PBR_d12/Setting.h"
#include <atlstr.h>
#include <QtWidgets/QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

	littlemm::Setting::Height = 500;
	littlemm::Setting::Width = 500;

	
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("littleEngine"));
	this->resize(1000, 1000);
	centralwidget = new QWidget(this);
	centralwidget->setObjectName(QStringLiteral("rendertarget"));
	render = new RenderTarget(centralwidget);
	render->setObjectName(QStringLiteral("widget"));
	render->setGeometry(QRect(260, 130, littlemm::Setting::Width, littlemm::Setting::Height));


	list = new QListView(centralwidget);
	list->setObjectName("List");
	list->setGeometry(QRect(20, 24, 181, 561));
	//QObject::connect(render, &RenderTarget::drawcomplete, render, &RenderTarget::update);
	
	this->setCentralWidget(centralwidget);
	menubar = new QMenuBar(this);
	menubar->setObjectName(QStringLiteral("menubar"));
	menubar->setGeometry(QRect(0, 0, 969, 23));
	this->setMenuBar(menubar);
	statusbar = new QStatusBar(this);
	statusbar->setObjectName(QStringLiteral("statusbar"));
	//statusbar->showMessage("ssss",10000);
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
	
	std::wstring fpsstr = L"FPS: "+ std::to_wstring(engine->mfps);
	
	/*CString str(fpsstr.c_str());
	OutputDebugString((std::to_wstring(engine->mTimer.TotalTime())+L"\n").c_str());
	this->setWindowIconText(QString::fromWCharArray(str, str.GetLength()));*/

	SetWindowText((HWND)this->winId(), fpsstr.c_str());
	statusbar->clearMessage();
	engine->Update(engine->mTimer);
	engine->Draw(engine->mTimer);
	//render->drawcomplete();
	render->update();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	littlemm::Setting::Height = height();
	littlemm::Setting::Width = width();
	engine->OnResize();
}


//void 

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
