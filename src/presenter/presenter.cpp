#include "presenter.h"
#include "../configuration/configuration.h"
#include "presenter_worker.h"
#include "presenter_types.h"
#include <QThread>
#include <memory>

namespace presenter
{
    Presenter::Presenter(std::shared_ptr<configuration::Configuration> configuration) : configuration(configuration),
                                                                                        beeper(configuration)
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
        connect(worker, &PresenterWorker::sleep, thread, &QThread::sleep);
        thread->start();
    }
    int Presenter::getInputState()
    {
        return state;
    }
    void Presenter::slotDashKeyPressed()
    {
        state |= dashKeyPressed;
    }
    void Presenter::slotSingleKeyReleased()
    {
        if (state & singleKeyPressed)
        {
            beeper.beepOff();
            state &= ~singleKeyPressed;
        }
    }
    void Presenter::slotDotKeyReleased()
    {
        state &= ~dotKeyPressed;
    }

    void Presenter::slotDashKeyReleased()
    {
        state &= ~dashKeyPressed;
    }
    void Presenter::slotDotKeyPressed()
    {
        state |= dotKeyPressed;
    }
    void Presenter::slotSingleKeyPressed()
    {
        state |= singleKeyPressed;
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