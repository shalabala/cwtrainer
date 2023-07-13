#include "presenter_worker.h"
#include "../utility/utility.h"
#include "presenter_types.h"
#include "presenter.h"
#include <memory>
#include <iostream>
#include <QThread>
namespace conf = configuration;
namespace presenter
{
    PresenterWorker::PresenterWorker(Presenter *presenter,
                                     std::shared_ptr<conf::Configuration> configuration) : isFinished(false),
                                                                                           lastSymbolEmission(cw_utility::getCurrentTimeInMillis()),
                                                                                           lastInputState(undefined),
                                                                                           presenter(presenter),
                                                                                           configuration(configuration)
    {
    }
    void PresenterWorker::process()
    {
        while (!isFinished)
        {
            int64_t currentTime = cw_utility::getCurrentTimeInMillis();
            int64_t elapsed = currentTime - lastSymbolEmission;
            int state = presenter->getInputState();
            if (state == lastInputState)
            {
                if (state & dotKeyPressed)
                {
                    qDebug("dot key detected, elapsed %ld", elapsed);
                    emit morseSymbolInputed(morse::dot);
                    QThread::msleep(configuration->getDotLength() + configuration->getDotLength());
                    lastSymbolEmission = currentTime;
                }
                else if (state & dashKeyPressed)
                {
                    qDebug("dot dash detected, elapsed %ld", elapsed);
                    emit morseSymbolInputed(morse::dash);
                    QThread::msleep(configuration->getDashLength() + configuration->getDotLength());
                    lastSymbolEmission = currentTime;
                }
            }
            else
            {
                if (lastInputState & singleKeyPressed)
                {
                    qDebug("single key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    if (elapsed >= configuration->getDashThresholdLength())
                    {
                        // emit morseSymbolInputed(morse::dash);
                        qDebug("single key dash");
                    }
                    else
                    {
                        // emit morseSymbolInputed(morse::dot);
                        qDebug("single key dot");
                    }
                    lastSymbolEmission = currentTime;
                }
                if (!(lastInputState & dotKeyPressed) && state & dotKeyPressed)
                {
                    qDebug("dot key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    emit morseSymbolInputed(morse::dot);

                    QThread::msleep(configuration->getDotLength() + configuration->getDotLength());
                    lastSymbolEmission = currentTime;
                }
                else if ((!(lastInputState & dashKeyPressed) || lastInputState & dotKeyPressed) && !(state & dotKeyPressed) && state & dashKeyPressed)
                {
                    qDebug("dash key detected, because of newkey, state %d  state before %d", state, lastInputState);
                    emit morseSymbolInputed(morse::dash);

                    QThread::msleep(configuration->getDashLength() + configuration->getDotLength());
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
}
