#pragma once
#if defined(__CYGWIN__) || defined(__unix__) || defined(__APPLE__)
// POSIX-like platforms (Cygwin, Unix, macOS)
#include <csignal>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "Coord.hpp"

typedef Coord Size;
class Drawable;
enum Color
{
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37
};

class Console
{
private:
    winsize size;
    Coord pos;
    std::ostream &interface;
    std::vector<void (*)(Console *)> funvector;

public:
    Console(std::ostream &interface, const bool nosetup);
    ~Console();
    Size getSize();
    void moveCursorUp(const int &n);
    void moveCursorDown(const int &n);
    void moveCursorRight(const int &n);
    void moveCursorLeft(const int &n);
    void clearLine();
    void clearStart();
    void clearEnd();
    void clearScreen();
    void cursorPos(const int &row, const int &col);
    void write(const Drawable &object);
    void write(const Size &data);
    template <typename OStreamWritable>
    void write(const OStreamWritable &data);
    int mainLoop();
};

#elif defined(_WIN32)
// Windows platforms
#error no native Windows support. Use Cygwin. Compilation aborted.
#else
#error "Unknown platform: compilation aborted"
#endif
