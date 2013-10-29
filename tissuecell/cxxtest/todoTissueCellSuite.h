
	/*

	








	void testEquilibrate(void){
		TissueCell::SimSystem simulation;
		simulation.SetRNGSeed(seed);

		simulation.GenerateNRandom(10000);
		
		int fail = simulation.EqStep();
			
		TS_ASSERT_EQUALS(fail,1);
	}

	void testPile(void){
		TissueCell::SimSystem simulation;
		simulation.SetRNGSeed(seed);
		simulation.SetFadh(0);
		simulation.SetFrep(0);

		simulation.GenerateNPile(10000, 5, 5);
		simulation.RandomizeAngles();
		
		simulation.EqStep();

		double xmean = 0;
		double ymean = 0;
		double xsigma = 0;
		double ysigma = 0;
		TissueCell::Vector data(simulation.ViewSystem());
		for (auto& cell : data){
			xmean += cell.x;
			ymean += cell.y;
			xsigma += (cell.x - 5) * (cell.x - 5);
			ysigma += (cell.y - 5) * (cell.y - 5);
		}

		xmean /= data.size();
		ymean /= data.size();
		xsigma = sqrt(xsigma) / data.size();
		ysigma = sqrt(ysigma) / data.size();

		TS_ASSERT_DELTA(xmean, 5, .02);
		TS_ASSERT_DELTA(ymean, 5, .02);
		TS_ASSERT_DELTA(xsigma, ysigma, .01);
	}	

	void testWander(void){
		TissueCell::SimSystem simulation;
		simulation.SetRNGSeed(seed);

		simulation.GenerateCubicLattice(10);
		simulation.RandomizeAngles();
	
		for (int i = 0 ; i < 1000 ; i ++){	
			simulation.TimeStep();
		}

		// No assertions in this test, just wandering.

	}


	*/
