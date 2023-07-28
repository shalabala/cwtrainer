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
namespace di = boost::di;

class App
{
public:
    App(std::shared_ptr<display::MainWindow> displayWindow,
        std::shared_ptr<configuration::Configuration> config) : displayWindow(displayWindow),
                                                                config(config)
    {
    }
    int start(int argc, char **argv, QApplication &app)
    {
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

        displayWindow->show();
        return app.exec();
    }

private:
    std::shared_ptr<display::MainWindow> displayWindow;
    std::shared_ptr<configuration::Configuration> config;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto injector = di::make_injector(
        di::bind<beeper::IBeeper>.to<beeper::Beeper>());

    
    return injector.create<std::shared_ptr<App>>()->start(argc,argv,app);
}
