#include "presenter_worker.h"
#include "../utility/utility.h"
#include "presenter_types.h"
#include "presenter.h"
#include "../configuration/configuration.h"
#include "../configuration/configuration_types.h"
#include <memory>
#include <iostream>
#include <QThread>
namespace conf = configuration;
namespace presenter
{
    PresenterWorker::PresenterWorker(Presenter *presenter,
                                     std::shared_ptr<conf::Configuration> configuration) : isFinished(false),
                                                                                           lastSymbolEmission(cw_utility::getCurrentTimeInMillis()),
                                                                                           lastInputState(noKeyPressed),
                                                                                           presenter(presenter),
                                                                                           configuration(configuration)
    {
    }
    void PresenterWorker::process()
    {
        while (!isFinished)
        {
            int pause = presenter->getPause();
            if (presenter->getPause() > 0)
            {
                if(presenter->resetPause(pause)){
                    QThread::msleep(pause);
                }
                continue;
            }
            int64_t currentTime = cw_utility::getCurrentTimeInMillis();
            int64_t elapsed = currentTime - lastSymbolEmission;
            int state = presenter->getInputStateFlags();
            if (state == lastInputState)
            {
                if (state == noKeyPressed && lastEmittedSymbol != morse::wordEnd)
                {
                    if (elapsed >= configuration->get<configuration::wordEndLength>())
                    {
                        emitMorseSymbolInput(morse::wordEnd, true);
                        emit morseSymbolInput(morse::letterEnd, true);
                    }
                    else if (lastEmittedSymbol != morse::letterEnd && elapsed >= configuration->get<configuration::letterEndLength>())
                    {
                        emitMorseSymbolInput(morse::letterEnd, true);
                    }
                }
                if (state & singleKeyPressed)
                {
                    // sleep?
                }
                if (state & dotKeyPressed)
                {
                    qDebug("dot key detected, elapsed %ld", elapsed);
                    emitMorseSymbolInput(morse::dot, false);
                    QThread::msleep(configuration->get<int, configuration::dotLength>() * 2);
                    lastSymbolEmission = currentTime;
                }
                else if (state & dashKeyPressed)
                {
                    qDebug("dot dash detected, elapsed %ld", elapsed);
                    emitMorseSymbolInput(morse::dash, false);
                    QThread::msleep(configuration->get<int, configuration::dashLength>() + configuration->get<int, configuration::dotLength>());
                    lastSymbolEmission = currentTime;
                }
            }
            else
            {
                if (lastInputState != noKeyPressed && state == noKeyPressed)
                {
                    lastSymbolEmission = currentTime;
                }
                if (lastInputState == noKeyPressed && state & singleKeyPressed)
                {
                    lastSymbolEmission = currentTime;
                    // sleep?
                }
                else if (lastInputState & singleKeyPressed)
                {
                    qDebug("single key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    if (elapsed >= configuration->get<int, configuration::dashThresholdLength>())
                    {
                        emitMorseSymbolInput(morse::dash, true);
                    }
                    else
                    {
                        emitMorseSymbolInput(morse::dot, true);
                    }
                    lastSymbolEmission = currentTime;
                }
                if (!(lastInputState & dotKeyPressed) && state & dotKeyPressed)
                {
                    qDebug("dot key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    emitMorseSymbolInput(morse::dot, false);

                    QThread::msleep(configuration->get<int, configuration::dotLength>() * 2);
                    lastSymbolEmission = currentTime;
                }
                else if ((!(lastInputState & dashKeyPressed) || lastInputState & dotKeyPressed) && !(state & dotKeyPressed) && state & dashKeyPressed)
                {
                    qDebug("dash key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    emitMorseSymbolInput(morse::dash, false);

                    QThread::msleep(configuration->get<int, configuration::dashLength>() + configuration->get<int, configuration::dotLength>());
                    lastSymbolEmission = currentTime;
                }
                qDebug("keyup detected, because of newkey, state %d  state before %d", state, lastInputState);
                lastInputState = state;
            }
        }

        emit finished();
    }

    void PresenterWorker::finish()
    {
        isFinished = true;
    }
    void PresenterWorker::emitMorseSymbolInput(morse::MorseSymbol s, bool isSingleKey)
    {
        lastEmittedSymbol = s;
        emit morseSymbolInput(s, isSingleKey);
    }
}
