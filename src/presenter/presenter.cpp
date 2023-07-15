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
    void Presenter::slotKeyPressed(InputState state)
    {
        if (state == singleKeyPressed && !(stateFlags & singleKeyPressed))
        {
            beeper->beepOn();
        }
        stateFlags |= state;
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

        char currentChar = tokenChars.front();

        if (s == morse::wordEnd)
        {
            if (currentChar == ' ')
            {
                change.charsToHighlight = 1;
                change.areCorrect = true;
                tokenChars.pop();
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
                change.areCorrect = alphabet.tryTranslateLetter(currentLetter, translated) &&
                                    cw_utility::tryPreprocessAscii(currentChar, currentCharPreprocessed) &&
                                    translated == currentCharPreprocessed;
                if (!change.areCorrect)
                {
                    tokenChars.empty();
                }
                tokenChars.pop();
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
        if (tokens.empty())
        {
            auto newTokens = dict->getNextTokens(numberOfTokensGeneratedAtOnce);
            std::string joinedString = boost::algorithm::join(newTokens, " ");
            DisplayChange change;
            change.textAppendToWords = joinedString;
            emit displayChange(change);
            for (auto &&i : newTokens)
            {
                tokens.push(i);
            }
        }
    }

    void Presenter::init()
    {
        refillInputTokensIfNeeded();
        prepareNextTokenIfNeeded();
    }

    void Presenter::prepareNextTokenIfNeeded()
    {
        if (tokenChars.empty())
        {
            refillInputTokensIfNeeded();
            std::string top = tokens.front();
            for (auto &&i : top)
            {
                tokenChars.push(i);
            }
            tokenChars.push(' ');
            cw_utility::clear(currentLetter);
        }
    }
}