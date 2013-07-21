#include "simtemplate.h"
#include <iostream>

void Sim::doWork(const QString &parameter) {
		//qDebug() << "Pre-send: ";
		for (int i = 0 ; i < 25; i++){
			sim.TimeStep();
		}
		formatAndEmit();
}

void Sim::formatAndEmit() {
		QList<double> dat_out;
		for (auto cell : sim.ViewRaw()){
			dat_out.append(cell.x);
			dat_out.append(cell.y);
			dat_out.append(cell.angle);
		}

		emit resultReady(dat_out);
}

void SimTemplate::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_timerId){
		//qDebug() << "Operate emitted.";
		emit operate("");
	}
}



void SimTemplate::renderDataLater(const QList<double>& data)
{
	//qDebug() << "RenderDataLater called...";
	if (!m_update_pending) {
			//qDebug() << "\tWith no pending update.";
			m_update_pending = true;
			result = data;
			result_ready = true;
			QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// render
////////////////////////////////////////////////////////////////////////////////////////////////////
void SimTemplate::render(QPainter *p)
{
	//qDebug() << "Render called.";
	/*
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    p->setRenderHint(QPainter::Antialiasing);
    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    p->setPen(Qt::NoPen);
    p->setBrush(hourColor);

    QTime time = QTime::currentTime();

    p->save();
    p->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    p->drawConvexPolygon(hourHand, 3);
    p->restore();

    p->setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        p->drawLine(88, 0, 96, 0);
        p->rotate(30.0);
    }
    p->setPen(Qt::NoPen);
    p->setBrush(minuteColor);

    p->save();
    p->rotate(6.0 * (time.minute() + time.second() / 60.0));
    p->drawConvexPolygon(minuteHand, 3);
    p->restore();

    p->setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(92, 0, 96, 0);
        p->rotate(6.0);
    }

		*/

	if (result_ready){
    static const QPoint walker[3] = {
        QPoint(5, -5),
        QPoint(-5, -5),
        QPoint(0, 10)
    };
    QColor walkerColor(127, 0, 127);

    p->setRenderHint(QPainter::Antialiasing);

		QBrush brsh(walkerColor);
		QPen pen(walkerColor);

    int side = qMin(width(), height());
    p->scale(side / double(m_gui_size * 1.25), side / double(m_gui_size * 1.25));

		p->setPen(pen);
		p->setBrush(brsh);

		for (int i = 0 ; i < result.size() / 2 ; i++){
			p->save();
    	p->translate(result[3*i], result[3*i+1]);
    	p->rotate(result[3*i+2] * 180./3.14159265359 - 90);
    	p->drawConvexPolygon(walker, 3);
			p->restore();
		}
	}
}
