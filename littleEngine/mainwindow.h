#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "RenderTarget.h"
#include "../PBR_d12/LittleEngineResource.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

	littlemm::LittleEngineResource* engine;

	QWidget* centralwidget;
	RenderTarget* render;

	QListView* list;
	QMenuBar *menubar;
	QStatusBar *statusbar;

private:
	
	
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

	//void DrawCommond();
};

#endif // MAINWINDOW_H
