#include "simtemplate.h"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    SimTemplate sim_window;
    sim_window.show();

    app.exec();
}
