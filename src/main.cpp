#include "display/main_window.h"
#include "presenter/presenter.h"
#include "configuration/configuration.h"
#include "dictionary/dictionary.h"
#include "beeper/beeper.h"
#include "beeper/ibeeper.h"
#include "morse/morse-alphabet.h"
#include "morse/morse-translator.h"
#include <memory>
#include <iostream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::shared_ptr<configuration::Configuration> config = std::make_shared<configuration::Configuration>();
    std::shared_ptr<dictionary::Dictionary> dictionary =
        std::make_shared<dictionary::Dictionary>(config);
    std::shared_ptr<beeper::IBeeper> beeper = std::make_shared<beeper::Beeper>(config);
    std::shared_ptr<presenter::Presenter> present = std::make_shared<presenter::Presenter>(config, dictionary, beeper);
    display::MainWindow window(present, config);
    
    window.show();
    return app.exec();
}
