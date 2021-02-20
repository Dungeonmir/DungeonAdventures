#pragma once
#include <libtcod.hpp>
#include <SDL.h> //SDL2 renderer
class RenderWindow {
public:
    void init( int x, int y);

    ~RenderWindow() {
        context.release();
        console.release();
    }
    int getConsoleX() {
        return consoleX;
    }
    int getConsoleY() {
        return consoleY;
    }
    void print(int x, int y, std::string text, TCOD_color_t* foreground, TCOD_color_t* background, TCOD_bkgnd_flag_t flag) {
        tcod::print(*console, x, y, text, foreground, background, flag, TCOD_LEFT);
    }
    void print(int x, int y, std::string text, TCOD_color_t* foreground, TCOD_color_t* background) {
        tcod::print(*console, x, y, text, foreground, background, TCOD_BKGND_SET, TCOD_LEFT);
    }
    void print(int x, int y, std::string text) {
        tcod::print(*console, x, y, text, nullptr, nullptr, TCOD_BKGND_NONE, TCOD_LEFT);
    }
    /*Print char*/
    void print(int x, int y, char ch, TCOD_color_t* foreground) {
        std::string str(1, ch);
        tcod::print(*console, x, y, str, foreground, nullptr, TCOD_BKGND_NONE, TCOD_LEFT);
    }
    void clear() {
        TCOD_console_clear(console.get());
    }
    void update() {
        context->present(*console); // Updates the visible display.
        
    }
    
private:
    int consoleX;
    int consoleY;
    tcod::ContextPtr context;
    tcod::ConsolePtr console;
};