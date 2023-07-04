#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "input_processor.h"
#include <memory>
namespace presenter
{
    class InputHandler
    {
    public:
        InputHandler(); // std::shared_ptr<InputProcessor> inputProcessor);
        void startListening();
        ~InputHandler();

    private:
        // std::shared_ptr<InputProcessor> processorThread;
        // bool isListeningOn;
    };
}
#endif
