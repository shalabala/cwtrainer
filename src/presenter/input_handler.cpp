#include "input_handler.h"
#include "SDL.h"
#include "SDL_events.h"
#include "../beeper/beeper.h"
#include "../utility/utility.h"
#include <iostream>
#include <chrono>
#include <ncurses.h>
namespace chrono = std::chrono;
namespace presenter
{
    const int freq = 550;
    const int amplitude = 28000;

    InputHandler::InputHandler()
    {
    }

    void InputHandler::startListening()
    {
        beeper::Beeper beeper(freq, amplitude, 55);
        SDL_Event event;
        int quit = 0;

        initscr();
        cbreak();
        keypad(stdscr, TRUE);
        noecho();

        // Aktiviere das Abfangen von Tastatureingaben
        nodelay(stdscr, TRUE); // Non-blocking input

        int ch;
        int64_t keyDown = -1;
        while ((ch = getch()) != KEY_F(1))
        {
            if (ch == ' ' && keyDown < 0)
            {
                printw("Key pressed: %d\n", ch);
                keyDown = cw_utility::getCurrentTimeInMillis();
                // beeper.beepOn();
            }
            else if (ch != ' ' && keyDown >=0)
            {
                int64_t currentTime = cw_utility::getCurrentTimeInMillis();
                printw("Key released: %d, was held for %d ms\n", ch, cw_utility::getCurrentTimeInMillis() - keyDown);
                keyDown = -1;
                // beeper.beepOff();
            }
        }

        // Beende die ncurses-Bibliothek
        endwin();
    }

    InputHandler::~InputHandler()
    {
    }
}
