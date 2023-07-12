#include "display/main_window.h"
#include "../presenter/presenter.h"
#include "../configuration/configuration.h" 
#include <memory>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<configuration::Configuration> config= std::make_shared<configuration::Configuration>();
    std::shared_ptr<presenter::Presenter> present= std::make_shared<presenter::Presenter>(config);
    display::MainWindow window(present, config);

    window.show();

    return app.exec();
}
