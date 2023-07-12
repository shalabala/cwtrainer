#ifndef CWTRAINER_DISPLAY_TYPES_H
#define CWTRAINER_DISPLAY_TYPES_H
namespace display{
    enum InputType {correct, incorrect, backspace};
    struct Input{
        InputType type;
        morse::MorseString morseValue;
        char charValue;
    } ;
}

#endif