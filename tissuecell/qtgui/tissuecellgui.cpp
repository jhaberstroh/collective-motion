#include <chrono>
#include <thread>
#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>
#include <QtWidgets/QMainWindow>
#include "tissuecell.h"
#include "tissuecellgui.h"

void RenderFrame1Sec(int argc, char ** argv, std::vector<TissueCell::RealType> pos){
	QGuiApplication app(argc, argv);
	
  QWindow ftw;
	ftw.show();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));

}
