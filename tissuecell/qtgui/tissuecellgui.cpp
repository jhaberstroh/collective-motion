#include <chrono>
#include <thread>
#include <QtGui/QWindow>
#include <QtGui/QBackingStore>
#include <QtCore/QRect>
#include <QtGui/QPicture>
#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>
#include "tissuecell.h"
#include "tissuecellgui.h"

void RenderFrame1Sec(std::vector<TissueCell::RealType> pos){
  QWindow ftw;
  QBackingStore *bkst = new QBackingStore(&ftw);
	ftw.create();
	ftw.setGeometry(100,100,300,200);
	ftw.setVisible(true);


	QRect rect(0, 0, ftw.width(), ftw.height());
	bkst->beginPaint(rect);

	QPaintDevice *brush = bkst->paintDevice();
	QPainter painter(brush);

	painter.fillRect(0, 0, ftw.width(), ftw.height(), Qt::white);

	bkst->endPaint();
	bkst->flush(rect);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	delete bkst;
}
