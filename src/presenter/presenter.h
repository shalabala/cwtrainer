#ifndef CWTRAINER_PRESENTER
#define CWTRAINER_PRESENTER
#include "../configuration/configuration.h"
#include "../beeper/beeper.h"
#include "../dictionary/dictionary.h"
#include "presenter_types.h"
#include <QObject>
#include <memory>


namespace presenter
{
    /**Handles the central input processing, and the view management
     * 
    */
    class Presenter : public QObject
    {
        Q_OBJECT
    public:
        Presenter(std::shared_ptr<configuration::Configuration> configuration,
        std::shared_ptr<dictionary::Dictionary> dictionary);
        /**Gets the input state flags
         * 
        */
        int getInputStateFlags();
    public slots:
        /**Sets the state that the single key has been pressed
         * 
        */
        void slotSingleKeyPressed();
        /**Sets the state that the dot key has been pressed
         * 
        */
        void slotDotKeyPressed();
        /**Sets the state that the dash key has been pressed
         * 
        */
        void slotDashKeyPressed();
        /**Sets the state that the single key has been released
         * 
        */
        void slotSingleKeyReleased();
        /**Sets the state that the dot key has been released
         * 
        */
        void slotDotKeyReleased();
        /**Sets the state that the dash key has been released
         * 
        */
        void slotDashKeyReleased();
        /**Processes the inputed morse signal
         * 
        */
        void slotMorseSymbolInput(char s);
    private:
        beeper::Beeper beeper;
        int stateFlags=0;
        std::shared_ptr<configuration::Configuration> configuration;
    };
}

#endif