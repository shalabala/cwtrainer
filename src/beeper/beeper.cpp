#include "beeper.h"
#include "beeper_types.h"
#include "SDL.h"
#include "SDL_audio.h"
#include "../morse/morse-types.h"
namespace beeper
{

    Beeper::Beeper(int freq, int amplitude, int dotDurationMS) : freq(freq),
                                                                 amplitude(amplitude),
                                                                 dotDurationMS(dotDurationMS),
                                                                 isConstantBeepOn(false),
                                                                 t(0)
    {
        SDL_AudioSpec desiredSpec;

        desiredSpec.freq = sampling;
        desiredSpec.format = AUDIO_S16SYS;
        desiredSpec.channels = 1;
        desiredSpec.samples = 2048;
        desiredSpec.callback = audioCallback;
        desiredSpec.userdata = this;

        SDL_AudioSpec obtainedSpec;

        // you might want to look for errors here
        SDL_OpenAudio(&desiredSpec, &obtainedSpec);

        // start play audio
        SDL_PauseAudio(0);
    }

    Beeper::~Beeper()
    {
        SDL_CloseAudio();
    }

    void Beeper::beepOn()
    {
        SDL_LockAudio();
        isConstantBeepOn = true;
        SDL_UnlockAudio();
    }

    void Beeper::beepOff()
    {
        SDL_LockAudio();
        isConstantBeepOn = false;
        SDL_UnlockAudio();
    }

    void Beeper::schedule(const morse::MorseString &s)
    {
        SDL_LockAudio();
        for (auto &&c : s)
        {
            symbols.push(c);
        }
        SDL_UnlockAudio();
    }

    void Beeper::wait()
    {
        int size;
        do
        {
            SDL_Delay(20);
            SDL_LockAudio();
            size = beeps.size();
            SDL_UnlockAudio();
        } while (size > 0);
    }

    void Beeper::generateSamples(Sint16 *stream, int length)
    {
        int i = 0;

        while (i < length)
        {
            if (isConstantBeepOn)
            {
                while (i < length)
                {
                    stream[i] = getInstantaneousAmplitude(freq);
                    ++i;
                }
            }
            else if (beeps.empty() && symbols.empty())
            {
                while (i < length)
                {
                    stream[i] = 0;
                    i++;
                }
            }
            else
            {
                if (beeps.empty())
                {

                    addBeeps();
                }

                Beep &bo = beeps.front();

                int samplesToDo = std::min(i + bo.samplesLeft, length);
                bo.samplesLeft -= samplesToDo - i;
                while (i < samplesToDo)
                {
                    stream[i] = getInstantaneousAmplitude(bo.freq);
                    ++i;
                }

                if (bo.samplesLeft == 0)
                {
                    beeps.pop();
                    t = 0;
                }
            }
        }
    }
    void Beeper::addBeeps()
    {
        morse::MorseSymbol sym = symbols.front();
        symbols.pop();
        switch (sym)
        {
        case morse::dot:
            beeps.push(Beep(freq, dotDuration()));
            beeps.push(Beep(0, dotDuration()));
            break;

        case morse::dash:
            beeps.push(Beep(freq, dashDuration()));
            beeps.push(Beep(0, dotDuration()));
            break;

        case morse::letterEnd:
            beeps.push(Beep(0, letterEndDuration()));

        case morse::wordEnd:
            beeps.push(Beep(0, wordEndDuration()));
        }
    }

    void audioCallback(void *_beeper, Uint8 *_stream, int _length)
    {
        Sint16 *stream = (Sint16 *)_stream;
        int length = _length / 2;
        Beeper *beeper = (Beeper *)_beeper;

        beeper->generateSamples(stream, length);
    }
}