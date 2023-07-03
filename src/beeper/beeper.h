#ifndef BEEPER_H
#define BEEPER_H
#include "ibeeper.h"
#include "../morse/morse-types.h"
#include "beeper_types.h"
#include "SDL.h"
#include "SDL_audio.h"
#include <queue>
namespace beeper
{
    class Beeper : public IBeeper
    {
    public:
        /**Construct the beeper class. The first parameter specifies the frequency of the beeps,
         * the second the amplitude, the third the unit length
         *
         */
        Beeper(int freq, int amplitude, int dotDurationMS);

        /**Turns a continuos beep on
         *
         */
        virtual void beepOn() override;

        /**Turns a continuos beep off
         *
         */
        virtual void beepOff() override;

        /**Schedules beeps according to the morse symbols in the given string
         *
         */
        virtual void schedule(const morse::MorseString &s) override;

        /**Waits until the scheduled queue is empty
         *
         */
        virtual void wait() override;

        /** Ends the audio stream.
         *
         */
        ~Beeper();

    private:
        /**Samples per second
         *
         */
        const int sampling = 44100;

        /**Frequency of the beep
         *
         */
        const int freq;

        /**Amplitude of the sine wave
         *
         */
        const int amplitude;

        /**Dot beep duration in milliseconds
         *
         */
        const int dotDurationMS;

        /** Input variable for the wave generation. Reset after each sampling to be equal to <old value> % sampling
         *
         */
        int t;

        /** Is the constant beep on or off
         *
         */
        bool isConstantBeepOn;

        /** Scheduled morse symbols which weren't yet processed
         *
         */
        std::queue<morse::MorseSymbol> symbols;

        /**
         * Scheduled beeps and silences
         */
        std::queue<Beep> beeps;

        /**Method for generating audio samples based on the symbols, and wether the constant
         * beep is on or off.
         * This method should only be called from the audio thread!
         *
         */
        void generateSamples(Sint16 *stream, int length);

        /**Adds the corresponding Beeps to the beeps queue from the symbols queue. Pops
         * one element from the symbols queue.
         * This method should only be called from the audio thread!
         *
         */
        void addBeeps();

        /**Duration of a dot beep expressed in number of samples
         *
         */
        int dotDuration()
        {
            return dotDurationMS * sampling / 1000;
        }

        /**Duration of a dash beep expressed in number of samples
         *
         */
        int dashDuration()
        {
            return dotDuration() * 3;
        }

        /**Duration of the silence after a letter expressed in number of samples
         *
         */
        int letterEndDuration()
        {
            return dotDuration() * 3;
        }

        /**Duration of the silence after a word expressed in number of samples
         * Its value is only 1, since every word end char is always preceded by, and followed by
         * a letter end character. This means that the full value of a word end char will be 3+1+3,
         * as per specification.
         *
         */
        int wordEndDuration()
        {
            return dotDuration() * 1;
        }

        /** Gets the instantaneous amplitude of the sine wave based on the sample count,
         * the frequency, the amplitude, und the sampling rate. Increments the current sample by 1;
         *
         */
        Sint16 getInstantaneousAmplitude(int freq)
        {
            Sint16 ia = amplitude * std::sin((t * 2 * M_PI) / sampling);
            t+=freq;
            return ia;
        }

        friend void audioCallback(void *_beeper, Uint8 *_stream, int _length);
    };

    /** The callback that is called on the audio thread.
     *
     */
    void audioCallback(void *_beeper, Uint8 *_stream, int _length);
}

#endif