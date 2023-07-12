#ifndef CWTRAINER_PRESENTER_WORKER_H
#define CWTRAINER_PRESENTER_WORKER_H
#include "../morse/morse-types.h"
#include "presenter.h"
#include "../configuration/configuration.h"
#include <QObject>
#include <memory>
namespace presenter
{
   class PresenterWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit PresenterWorker(Presenter* presenter,
        std::shared_ptr<configuration::Configuration> configuration);
        ~PresenterWorker()= default;
    public slots:
        void process();
        void finish();
    signals:
        void morseSymbolInputed(char s);
        void inputChanged();
        void finished();
        void error(QString err);
    private:
        Presenter* presenter;
        std::shared_ptr<configuration::Configuration> configuration;
        bool isFinished;
        int64_t lastSymbolEmission;
        InputState lastInputState;
    };
}

#endif