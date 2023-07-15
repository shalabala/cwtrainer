#include "presenter.h"
#include "../configuration/configuration.h"
#include "../dictionary/dictionary.h"
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
                                                                    dict(dictionary)
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
        DisplayChange change;
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

    void Presenter::init(){
        refillInputTokensIfNeeded();
    }
}