#include "simtemplate.h"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
		
		int seed = -1;
		
		if (argc == 2){
			seed = atoi(argv[1]);
		}

		SimTemplate sim_window(seed);


		sim_window.show();
    app.exec();
}
