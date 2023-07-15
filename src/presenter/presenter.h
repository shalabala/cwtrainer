#ifndef CWTRAINER_PRESENTER
#define CWTRAINER_PRESENTER
#include "../configuration/configuration.h"
#include "../beeper/ibeeper.h"
#include "../dictionary/dictionary.h"
#include "presenter_types.h"
#include <QObject>
#include <memory>
#include <string>
#include <queue>

namespace presenter
{
    /**Handles the central input processing, and the view management
     *
     */
    class Presenter : public QObject
    {
        Q_OBJECT
    public:
        Presenter(std::shared_ptr<configuration::Configuration> configuration,
                  std::shared_ptr<dictionary::Dictionary> dictionary,
                  std::shared_ptr<beeper::IBeeper> beeper);
        /**Gets the input state flags
         *
         */
        int getInputStateFlags();
    signals:
        /**
         * Signals in what way should the display be changed
         */
        void displayChange(const DisplayChange &change);
    public slots:
        /**
         * Adds the key from the state and undertakes the appropriate action
         */
        void slotKeyPressed(InputState state);
        /**
         * Removes the key from the state and undertakes the appropriate action
         */
        void slotKeyReleased(InputState state);
        /**Processes the inputed morse signal
         *
         */
        void slotMorseSymbolInput(char s, bool isSingleKey);
        /**
         * Initialises the presenter and sends instructions to the display
         */
        void init();

    private:
        void refillInputTokensIfNeeded();

        int stateFlags = 0;
        int tokenIndex = 0;
        std::queue<std::string> tokens;
        std::shared_ptr<beeper::IBeeper> beeper;
        std::shared_ptr<configuration::Configuration> configuration;
        std::shared_ptr<dictionary::Dictionary> dict;

        const int numberOfTokensGeneratedAtOnce = 100;
    };
}

#endif