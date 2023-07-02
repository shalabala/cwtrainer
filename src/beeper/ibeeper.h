#ifndef I_BEEPER_H
#define I_BEEPER_H
#include "../morse/morse-types.h"
#include <queue>
namespace beeper
{
    /**Generates morse beeps
     *
     */
    class IBeeper
    {
    public:
        virtual ~IBeeper() = default;

        /**Turns a continuos beep on
         * 
         */
        virtual void beepOn() = 0;

        /**Turns a continuos beep off
         * 
         */
        virtual void beepOff() = 0;

        /**Schedules beeps according to the morse symbols in the given string
         * 
         */
        virtual void schedule(const morse::MorseString &s) = 0;

        /**Waits until the scheduled queue is empty
         *
         */
        virtual void wait() = 0;
    };

}
#endif
