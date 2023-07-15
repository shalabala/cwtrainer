#ifndef CWTRAINER_PRESENTER_TYPES
#define CWTRAINER_PRESENTER_TYPES
namespace presenter
{
    /**
     * Flags that represent the current input configuration
     */
    enum InputState
    {
        noKeyPressed = 0,
        singleKeyPressed = 1,
        dotKeyPressed = 2,
        dashKeyPressed = 4,
    };
    /**
     * Changes that the display should render and show
     */
    struct DisplayChange
    {
        /**
         * Number of characters on the input that should be highlighted
         *  either as correct or incorrect.
         */
        unsigned int charsToHighlight = 0;
        /**
         * Wether the inputed character was correct or not
         */
        bool areCorrect = false;
        /**
         * Number of chars to delete
         */
        unsigned int charsToDelete = 0;
        /**
         * The text to append to the textfield that contains the to be inputed words
         */
        std::string textAppendToWords;
        /**
         * The morse text to be appended to the morse text field
         */
        morse::MorseString textToAppendToMorse;
    };
}

#endif