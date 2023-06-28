#include "SDL.h"
#include "SDL_audio.h"
#include "morse/morse-types.h"
#include "morse/morse-alphabet.h"
#include "morse/morse-translator.h"
#include <queue>
#include <iostream>
#include <cmath>

const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

struct BeepObject
{
    double freq;
    int samplesLeft;
    int bpm = 0;
};

class Beeper
{
private:
    double v;
    std::queue<BeepObject> beeps;
    Sint16 generateWave(const BeepObject &bo);

public:
    Beeper();
    ~Beeper();
    void beep(double freq, int duration);
    void recurringBeep(double freq, int duration, int bpm);
    void silence(int duration);
    void generateSamples(Sint16 *stream, int length);
    void wait();
};

void audio_callback(void *, Uint8 *, int);

Beeper::Beeper()
{
    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;
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

void Beeper::generateSamples(Sint16 *stream, int length)
{
    int i = 0;

    while (i < length)
    {

        if (beeps.empty())
        {
            while (i < length)
            {
                stream[i] = 0;
                i++;
            }
            return;
        }
        BeepObject &bo = beeps.front();

        int samplesToDo = std::min(i + bo.samplesLeft, length);
        bo.samplesLeft -= samplesToDo - i;
        while (i < samplesToDo)
        {
            stream[i] = generateWave(bo); // AMPLITUDE * std::sin((v * 2 * M_PI) / FREQUENCY);
            i++;
        }

        if (bo.samplesLeft == 0)
        {
            beeps.pop();
            // v should not overflow ever
            v = 0;
        }
    }
}
Sint16 Beeper::generateWave(const BeepObject &bo)
{
    // factor in BPM
    bool beatOn = true;
    if (bo.bpm > 0)
    {
        double samplePerBeat = (60 * FREQUENCY) / bo.bpm;
        double currentSample = v / bo.freq;

        beatOn = std::fmod(std::floor(currentSample / samplePerBeat), 2) == 0;
    }
    // generate sign wave or silence
    Sint16 soundValue;
    if (beatOn)
    {
        soundValue = AMPLITUDE * std::sin((v * 2 * M_PI) / FREQUENCY);
    }
    else
    {
        soundValue = 0;
    }
    v += bo.freq;
    return soundValue;
}
void Beeper::beep(double freq, int duration)
{
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}

void Beeper::recurringBeep(double freq, int duration, int bpm)
{
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;
    bo.bpm = bpm;

    SDL_LockAudio();
    beeps.push(bo);
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

void audio_callback(void *_beeper, Uint8 *_stream, int _length)
{
    Sint16 *stream = (Sint16 *)_stream;
    int length = _length / 2;
    Beeper *beeper = (Beeper *)_beeper;

    beeper->generateSamples(stream, length);
}

int calculateDurationFromBeats(int beats, int bpm)
{
    double milisecPerBeat = (60.0 * 1000.0) / bpm;
    double milisecs = milisecPerBeat * beats * 2;
    return static_cast<int>(std::ceil(milisecs));
}

int beeper_test(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO);

    int duration = 1000;
    int bpmDot = 500;
    int bpmDash = 200;
    double Hz = 850;

    Beeper b;
    // b.beep(Hz, duration);
    b.recurringBeep(Hz, calculateDurationFromBeats(3, bpmDot), bpmDot);
    b.recurringBeep(Hz, calculateDurationFromBeats(3, bpmDash), bpmDash);
    b.recurringBeep(Hz, calculateDurationFromBeats(3, bpmDot), bpmDot);

    b.wait();

    return 0;
}

int main()
{
    morse::MorseAlphabet alphabet;
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        const morse::MorseStringIterator &letter = alphabet.translateLetter(c);
        char retranslate = alphabet.translateLetter(letter);
        std::cout << c << ": " << letter << " : " << retranslate << std::endl;
    }

    morse::MorseTranslate translate(alphabet);

    morse::MorseString translationToMorse = translate.translateTextToMorse("Hello vilag");

    std::cout << translationToMorse << std::endl;
    
    std::string translationToText = translate.translateMorseToText(".... . .-.. .-.. --- /...- .. .-.. .- --.");

    std::cout << translationToText << std::endl;

    
    return 0;
}