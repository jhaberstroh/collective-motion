#include "simtemplate.h"
#include <iostream>

void SimTemplate::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_timerId)
		qDebug() << "Operate emitted.";
		emit operate("");
}


void SimTemplate::renderDataLater(const QList<double>& data)
{
	qDebug() << "RenderDataLater called...";
	if (!m_update_pending) {
			qDebug() << "\tWith no pending update.";
			m_update_pending = true;
			result = data;
			result_ready = true;
			QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
	}
}


void Sim::doWork(const QString &parameter) {
		QList<double> x;
		for (int i = 0 ; i < 11 ; ++i){
			x.append(178. * rng.rand() + 10);
		}
		qDebug() << "Pre-send: " << x[0];
		emit resultReady(x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// render
////////////////////////////////////////////////////////////////////////////////////////////////////
void SimTemplate::render(QPainter *p)
{
	qDebug() << "Render called.";
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
		QBrush brsh(Qt::SolidPattern);
		QPen pen(brsh, 2, Qt::SolidLine);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

		p->setPen(pen);
		p->setBrush(brsh);

		for (int i = 0 ; i < result.size() / 2 ; i++){
			p->drawEllipse(result[2*i], result[2*i+1], 10,10);
		}
		qDebug() << "Post-send: "	<< result[0];
	}
}
