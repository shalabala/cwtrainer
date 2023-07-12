#ifndef CWTRAINER_PRESENTER
#define CWTRAINER_PRESENTER
#include "../configuration/configuration.h"
#include "../beeper/beeper.h"
#include "presenter_types.h"
#include <QObject>
#include <memory>


namespace presenter
{
    class Presenter : public QObject
    {
        Q_OBJECT
    public:
        Presenter(std::shared_ptr<configuration::Configuration> configuration);
        InputState getInputState();
    public slots:
        void slotSingleKeyPressed();
        void slotDotKeyPressed();
        void slotDashKeyPressed();
        void slotKeyReleased();
        void slotMorseSymbolInputed(char s);
        void clearBeeper();
    private:
        beeper::Beeper beeper;
        InputState state;
        std::shared_ptr<configuration::Configuration> configuration;
    };
}

#endif