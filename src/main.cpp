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
#include <string>

int main(int argc, char **argv)
{
    std::shared_ptr<configuration::Configuration> config = std::make_shared<configuration::Configuration>();

    if (argc == 2)
    {
        std::string firstArg(argv[1]);
        if(firstArg == "-e"){
            config->set<configuration::defaultDifficulty>(configuration::easy);
            std::cout << "Difficulty set to easy" << std::endl;
        }else if(firstArg =="-m"){
            config->set<configuration::defaultDifficulty>(configuration::medium);
            std::cout << "Difficulty set to medium" << std::endl;
        }else if(firstArg =="-h"){
            config->set<configuration::defaultDifficulty>(configuration::hard);
            std::cout << "Difficulty set to hard" << std::endl;
        }
    }
    QApplication app(argc, argv);
    std::shared_ptr<dictionary::Dictionary> dictionary =
        std::make_shared<dictionary::Dictionary>(config);
    std::shared_ptr<beeper::IBeeper> beeper = std::make_shared<beeper::Beeper>(config);
    std::shared_ptr<presenter::Presenter> present = std::make_shared<presenter::Presenter>(config, dictionary, beeper);
    display::MainWindow window(present, config);

    window.show();
    return app.exec();
}
