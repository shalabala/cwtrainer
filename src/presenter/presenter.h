#ifndef CWTRAINER_PRESENTER
#define CWTRAINER_PRESENTER
#include "../configuration/configuration.h"
#include "../beeper/ibeeper.h"
#include "../dictionary/dictionary.h"
#include "../morse/morse-alphabet.h"
#include "../morse/morse-translator.h"
#include "presenter_types.h"
#include <QObject>
#include <memory>
#include <string>
#include <vector>
#include <mutex>
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
        /**
         * Gets for how long should the event processor thread be paused
        */
        int getPause();
        /**
         * Resets the pause counter thread safely. This should indicate that the
         * event processor thread has paused for the given amount of time.
         * 
         * The int parameter is provided for checking wether the pause value is still the same,
         * as it was before accessing it. 
         * If it receives a value that is 0 or not the same as the current value of the pause milliseconds,
         * it will return false and the pause value will not be changed
         * 
         * In other cases it returns true and the pause variable will be set to 0
         * 
         */
        bool resetPause(int oldValueToCheck);
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
        const std::string& getCurrentToken();
        /**
         * Stops the key processing for the given period
         */
        void stopKeyProcessingFor(int ms);
        /**
         * Prepares the next token to be processed, in that it splits it up into characters.
         * puts the characters into the tokenChars queue, and empties the so far inputed morse characters
         */
        void prepareNextTokenIfNeeded();

        /**
         * If the token queue is empty, it requests more tokens from the dictionary
         */
        void refillInputTokensIfNeeded();

        /**
         * Plays the current token on the beeper. Stops the user input for that time
         */
        void initiateHelpFunction();

        /**
         * Goes back by one character
         */
        void goBack();

        int eventProcessingPauseMs = 0;
        std::mutex pauseLock;

        int stateFlags = 0;
        int tokenIndex = 0;

        std::vector<std::string> tokens;
        size_t tokensIndex = 0;

        std::vector<char> tokenChars;
        size_t tokenCharsIndex = 0;

        morse::MorseString currentLetter;

        std::shared_ptr<beeper::IBeeper> beeper;

        morse::MorseAlphabet alphabet;
        morse::MorseTranslate translate;
        std::shared_ptr<configuration::Configuration> configuration;
        std::shared_ptr<dictionary::Dictionary> dict;

        const int numberOfTokensGeneratedAtOnce = 100;
    };
}

#endif