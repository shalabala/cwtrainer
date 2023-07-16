#ifndef CWTRAINER_PRESENTER_WORKER_H
#define CWTRAINER_PRESENTER_WORKER_H
#include "../morse/morse-types.h"
#include "presenter.h"
#include "../configuration/configuration.h"
#include <QObject>
#include <memory>
namespace presenter
{
    /**The worker class that implements the processing of the inputed characters
     *
     */
    class PresenterWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit PresenterWorker(Presenter *presenter,
                                 std::shared_ptr<configuration::Configuration> configuration);
        ~PresenterWorker() = default;
    public slots:
        /**Starts the main loop
         *
         */
        void process();
        /**The work should be finished soon
         *
         */
        void finish();
    signals:
        /**Here get emitted the generated morse symbols
         *
         */
        void morseSymbolInput(char s, bool isSingleKey);
        /**
         * This signal gets emitted after the worker has finished, somewhat later than the 
         * finish() slot was called
         */
        void finished();
        /**Error signal
         *
         */
        void error(QString err);

    private:
        /**
         * sends the processed morse signal, and records it as the last signal sent
         */
        void emitMorseSymbolInput(morse::MorseSymbol s, bool isSingleKey);
        /**The presenter that records its current state of pressed keys
         *
         */
        Presenter *presenter;
        /**Global configuration
         *
         */
        std::shared_ptr<configuration::Configuration> configuration;
        /** Is the worker finished
         *
         */
        bool isFinished;
        /** Timestamp when the last morse symbol was emitted
         *
         */
        int64_t lastSymbolEmission;
        /** The last processed state of the input keys
         *
         */
        int lastInputState;
        /**
         * Last morse symbol to be emitted
         */
        morse::MorseSymbol lastEmittedSymbol;
    };
}

#endif