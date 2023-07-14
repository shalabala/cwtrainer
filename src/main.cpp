#include "display/main_window.h"
#include "../presenter/presenter.h"
#include "../configuration/configuration.h"
#include "../dictionary/dictionary.h"
#include <memory>
#include <iostream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<configuration::Configuration> config = std::make_shared<configuration::Configuration>();
    std::shared_ptr<dictionary::Dictionary> dictionary =
        std::make_shared<dictionary::Dictionary>(config);
    std::shared_ptr<presenter::Presenter> present = std::make_shared<presenter::Presenter>(config, dictionary);
    display::MainWindow window(present, config);
    
    window.show();

    return app.exec();
}
