#include <QtGui>
#include <unistd.h>

void RenderFrame1Sec(std::vector<TissueCell::RealType> pos){
	QWindow::create();
	usleep(1000*1000);
	QWindow::destroy();

}
