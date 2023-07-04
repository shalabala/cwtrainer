#include "display/main_window.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    display::MainWindow window;

    window.show();

    return app.exec();
}
