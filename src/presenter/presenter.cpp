#include "presenter.h"
#include "../configuration/configuration.h"
#include "../dictionary/dictionary.h"
#include "../morse/morse-alphabet.h"
#include "../morse/morse-translator.h"
#include "../utility/utility.h"
#include "presenter_worker.h"
#include "presenter_types.h"
#include <QThread>
#include <boost/algorithm/string/join.hpp>
#include <memory>

namespace presenter
{
    Presenter::Presenter(std::shared_ptr<configuration::Configuration> configuration,
                         std::shared_ptr<dictionary::Dictionary> dictionary,
                         std::shared_ptr<beeper::IBeeper> beeper) : configuration(configuration),
                                                                    beeper(beeper),
                                                                    dict(dictionary),
                                                                    alphabet(),
                                                                    translate(alphabet)
    {
        QThread *thread = new QThread();
        PresenterWorker *worker = new PresenterWorker(this, configuration);
        worker->moveToThread(thread);
        // TODO connect(worker, &PresenterWorker::error, this, &MyClass::errorString);
        connect(thread, &QThread::started, worker, &PresenterWorker::process);
        connect(worker, &PresenterWorker::finished, thread, &QThread::quit);
        connect(worker, &PresenterWorker::finished, worker, &PresenterWorker::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(worker, &PresenterWorker::morseSymbolInput, this, &Presenter::slotMorseSymbolInput);
        thread->start();
    }
    int Presenter::getInputStateFlags()
    {
        return stateFlags;
    }
    int Presenter::getPause()
    {
        return eventProcessingPauseMs;
    }
    bool Presenter::resetPause(int oldValueInMs)
    {
        const std::lock_guard<std::mutex> lock(pauseLock);
        if(oldValueInMs == eventProcessingPauseMs && eventProcessingPauseMs >0){
            eventProcessingPauseMs = 0;
            return true;
        }
        return false;
    }
    void Presenter::stopKeyProcessingFor(int ms)
    {
        const std::lock_guard<std::mutex> lock(pauseLock);
        eventProcessingPauseMs = ms;
    }
    void Presenter::slotKeyPressed(InputState state)
    {
        if (state == backspacePressed)
        {
            goBack();
        }
        else if (state == helpKeyPressed)
        {
        }
        else
        {
            if (state == singleKeyPressed && !(stateFlags & singleKeyPressed))
            {
                beeper->beepOn();
            }
            stateFlags |= state;
        }
    }
    void Presenter::slotKeyReleased(InputState state)
    {
        if (state == singleKeyPressed && (stateFlags & singleKeyPressed))
        {
            beeper->beepOff();
        }
        stateFlags &= ~state;
    }
    void Presenter::slotMorseSymbolInput(char s, bool isSingleKey)
    {
        morse::MorseString morse(1, s);
        if (!isSingleKey)
        {
            beeper->schedule(morse);
        }
        // the changes to be assembled
        DisplayChange change;

        char currentChar = tokenChars[tokenCharsIndex];

        if (s == morse::wordEnd)
        {
            if (currentChar == ' ')
            {
                change.charsToHighlight = 1;
                change.areCorrect = true;
                ++tokenCharsIndex;
                prepareNextTokenIfNeeded();
            }
        }
        else if (s == morse::letterEnd)
        {
            if (currentLetter.length() > 0)
            {
                currentLetter.push_back(s);
                char translated = '\0';
                char currentCharPreprocessed = '\0';
                change.charsToHighlight = 1;
                if (alphabet.tryTranslateLetter(currentLetter, translated) &&
                    cw_utility::tryPreprocessAscii(currentChar, currentCharPreprocessed) &&
                    translated == currentCharPreprocessed)
                {
                    change.areCorrect = true;
                }
                else
                {
                    change.areCorrect = false;
                }

                ++tokenCharsIndex;
                cw_utility::clear(currentLetter);
                prepareNextTokenIfNeeded();
            }
        }
        else
        {
            currentLetter.push_back(s);
        }

        change.textToAppendToMorse = morse;
        emit displayChange(change);
    }

    void Presenter::refillInputTokensIfNeeded()
    {
        if (tokens.size() <= tokensIndex)
        {
            tokensIndex = 0;
            auto newTokens = dict->getNextTokens(numberOfTokensGeneratedAtOnce);
            std::string joinedString = boost::algorithm::join(newTokens, " ");
            DisplayChange change;
            change.textAppendToWords = joinedString;
            emit displayChange(change);
            for (auto &&i : newTokens)
            {
                tokens.push_back(i);
            }
        }
    }

    void Presenter::initiateHelpFunction()
    {
        const std::string& currentToken = getCurrentToken();
        morse::MorseString translation = translate.translateTextToMorse(currentToken);
        beeper.

    }

    void Presenter::goBack()
    {
        cw_utility::clear(currentLetter);
        if (tokensIndex < 2 && tokenCharsIndex == 0)
        {
            return;
        }
        else if (tokenCharsIndex > 0)
        {
            --tokenCharsIndex;
        }
        else
        {
            cw_utility::clear(tokenChars);
            tokensIndex -= 2;
            prepareNextTokenIfNeeded();
            tokenCharsIndex = tokenChars.size() - 1;
        }
        DisplayChange change;
        change.charsToDelete = 1;
        emit displayChange(change);
    }

    void Presenter::init()
    {
        refillInputTokensIfNeeded();
        prepareNextTokenIfNeeded();
    }

    const std::string& Presenter::getCurrentToken()
    {
        return tokens[tokensIndex-1];
    }

    void Presenter::prepareNextTokenIfNeeded()
    {
        if (tokenChars.size() <= tokenCharsIndex)
        {
            refillInputTokensIfNeeded();
            cw_utility::clear(tokenChars);
            tokenCharsIndex = 0;
            cw_utility::clear(currentLetter);

            std::string &top = tokens[tokensIndex];
            ++tokensIndex;

            for (auto &&i : top)
            {
                tokenChars.push_back(i);
            }
            tokenChars.push_back(' ');
        }
    }
}