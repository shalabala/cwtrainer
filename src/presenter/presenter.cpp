#include "presenter.h"
#include "../configuration/configuration.h"
#include "presenter_worker.h"
#include "presenter_types.h"
#include <QThread>
#include <memory>

namespace presenter
{
    Presenter::Presenter(std::shared_ptr<configuration::Configuration> configuration) : configuration(configuration),
                                                                                        beeper(configuration),
                                                                                        stateFlags(0)
    {
        QThread *thread = new QThread();
        PresenterWorker *worker = new PresenterWorker(this, configuration);
        worker->moveToThread(thread);
        // TODO connect(worker, &PresenterWorker::error, this, &MyClass::errorString);
        connect(thread, &QThread::started, worker, &PresenterWorker::process);
        connect(worker, &PresenterWorker::finished, thread, &QThread::quit);
        connect(worker, &PresenterWorker::finished, worker, &PresenterWorker::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(worker, &PresenterWorker::morseSymbolInputed, this, &Presenter::slotMorseSymbolInputed);
        connect(worker, &PresenterWorker::inputChanged, this, &Presenter::clearBeeper);
        thread->start();
    }
    int Presenter::getInputState()
    {
        return stateFlags;
    }
    void Presenter::slotDashKeyPressed()
    {
        stateFlags |= dashKeyPressed;
    }
    void Presenter::slotSingleKeyReleased()
    {
        if (stateFlags & singleKeyPressed)
        {
            beeper.beepOff();
            stateFlags &= ~singleKeyPressed;
        }
    }
    void Presenter::slotDotKeyReleased()
    {
        stateFlags &= ~dotKeyPressed;
    }

    void Presenter::slotDashKeyReleased()
    {
        stateFlags &= ~dashKeyPressed;
    }
    void Presenter::slotDotKeyPressed()
    {
        stateFlags |= dotKeyPressed;
    }
    void Presenter::slotSingleKeyPressed()
    {
        stateFlags |= singleKeyPressed;
        beeper.beepOn();
    }
    void Presenter::slotMorseSymbolInputed(char s)
    {
        beeper.schedule(morse::MorseString(1, s));
    }
    void Presenter::clearBeeper()
    {
        beeper.clearSchedule();
    }
}