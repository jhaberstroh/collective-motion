/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QtGui>
#include <QtCore>

#include "rasterwindow.h"
#include "MersenneTwister.h"
#include "tissuesimulation.h"
#include "nematic.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Simulation object, to run in a thread
////////////////////////////////////////////////////////////////////////////////////////////////////
class Sim : public QObject
{
Q_OBJECT
			QThread workerThread;
			MTRand rng;
			NematicSim sim;

	public:
			Sim(int seed_in = -1){
				int seed;
				if (seed_in == -1){
					seed = rng.rand(10000000);
					qDebug() << "SEED: "<<seed;
				}
				else{
					seed = seed_in; 
					qDebug() << "SEED-IN: "<<seed;
				}
				sim.set_seed(seed);
				sim.LinearZoom(20);
				sim.GenerateSquareLattice(20);
				sim.RandomizeAngles();
				sim.dt = .01;
			}
	public slots:
			void doWork(const QString &parameter);
 	signals:
			void resultReady(const QList<double>& result);
	protected:
			void formatAndEmit();
};



////////////////////////////////////////////////////////////////////////////////////////////////////
// Main window
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimTemplate : public RasterWindow
{
Q_OBJECT
			QThread simThread;	
			QList<double> result;
			bool result_ready;
			int m_timerId;
			int m_gui_size;

public:
	SimTemplate(int seed_in):RasterWindow()
	{
    setTitle("Cell Tissue Simulation");
		m_gui_size = 300;
    resize(m_gui_size, m_gui_size);

		result_ready = false;

		Sim *sim = new Sim(seed_in);
		sim->moveToThread(&simThread);
		connect(&simThread, &QThread::finished, sim, &QObject::deleteLater);
		connect(this, &SimTemplate::operate, sim, &Sim::doWork);
		connect(sim, &Sim::resultReady, this, &SimTemplate::renderDataLater);
		simThread.start();

		m_timerId = startTimer(100);
	}
	
	~SimTemplate()
	{
		simThread.quit();
		simThread.wait();
	}


protected:
    void timerEvent(QTimerEvent *);
    void render(QPainter *p);

public slots:
		void renderDataLater(const QList<double>& data);

signals:
		void operate(const QString &);
};



#endif //ANALOGCLOCK_H

