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
         * Lock for all beeper related activities. Only while this mutex is locked can input processing, that has the ability to 
         * produce sound, be done.
         */
        std::mutex beeperLock;

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
        const std::string &getCurrentToken();
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

        const int numberOfTokensGeneratedAtOnce = 5;
    };
}

#endif