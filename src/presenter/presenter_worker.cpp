#include "presenter_worker.h"
#include "../utility/utility.h"
#include "presenter_types.h"
#include "presenter.h"
#include <memory>
#include <iostream>
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
            InputState state = presenter->getInputState();
            if (state == dotKeyPressed && elapsed >= (configuration->getDotLength() + configuration->getDotLength()))
            {
                //std::cout << "dot key detected, ellapsed "+ elapsed <<std::endl;
                emit morseSymbolInputed(morse::dot);
                lastSymbolEmission = currentTime;
            }
            else if (state == dashKeyPressed && elapsed >= (configuration->getDashLength() + configuration->getDotLength()))
            {
                emit morseSymbolInputed(morse::dash);
                lastSymbolEmission = currentTime;
            }
            if (state != lastInputState)
            {
                if (lastInputState == singleKeyPressed)
                {
                    if (elapsed >= configuration->getDashThresholdLength())
                    {
                        emit morseSymbolInputed(morse::dash);
                    }
                    else
                    {
                        emit morseSymbolInputed(morse::dot);
                    }
                }
                if (state == dashKeyPressed)
                {
                    emit morseSymbolInputed(morse::dash);
                }
                else if (state == dotKeyPressed)
                {
                    emit morseSymbolInputed(morse::dot);
                }
                lastSymbolEmission = currentTime;
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
