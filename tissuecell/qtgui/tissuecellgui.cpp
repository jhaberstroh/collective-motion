#include <chrono>
#include <thread>
#include <QtGui/QWindow>
#include "tissuecell.h"
#include "tissuecellgui.h"

void RenderFrame1Sec(std::vector<TissueCell::RealType> pos){
	QWindow ftw;
	ftw.create();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	ftw.destroy();

}
