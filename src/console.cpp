#include "console.hpp"
#include "Drawable.hpp"

static volatile sig_atomic_t g_notKilled = 1;
void sig_handler(int sig)
{
    (void)sig;
    g_notKilled = 0;
}
Console::~Console()
{
    this->write("endofline");
    // Destructor implementation
}

Size Console::getSize()
{

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &this->size) == -1)
    {
        perror("ioctl");
    }
    return {this->size.ws_row, this->size.ws_col};
}

void Console::moveCursorUp(const int &n = 1)
{
    if (n > 0)
        this->interface << "\033[" << n << "A";
}
void Console::moveCursorDown(const int &n = 1)
{
    if (n > 0)
        this->interface << "\033[" << n << "B";
}
void Console::moveCursorRight(const int &n = 1)
{
    if (n > 0)
        this->interface << "\033[" << n << "C";
}
void Console::moveCursorLeft(const int &n = 1)
{
    if (n > 0)
        this->interface << "\033[" << n << "D";
}

void Console::clearLine()
{
}
void Console::clearStart()
{
    this->interface << "\033[0J";
}
void Console::clearEnd()
{
    this->interface << "\033[1J";
}

void Console::clearScreen()
{
    this->interface << "\033[2J";
}

void Console::cursorPos(const int &row = 1, const int &col = 1)
{
    if (row > 0 && col > 0)
        this->interface << "\033[" << row << ";" << col << "H";
}

void Console::write(const Drawable &object)
{
    object.draw(this);
}

void Console::write(const Size &data)
{
    this->interface << "Size<row=" << data.getRow() << ";col=" << data.getCol() << ">";
}
template <typename OStreamWritable>
inline void Console::write(const OStreamWritable &data)
{
    this->interface << data;
}

int Console::mainLoop()
{
    while (g_notKilled)
    {
        for (auto fun : this->funvector)
            fun(this);
        this->interface << std::flush;
    }
    this->interface << "mainloopend";
    return 0;
}

Console::Console(std::ostream &interface = std::cout, const bool nosetup = false) : interface(interface), pos(1, 1)
{
    // Constructor implementation
    // Bind internal streambuf to the provided stream to avoid assigning std::ostream (assignment is deleted)
    (void)this->getSize(); // feed size struct with initial data
    if (nosetup)
        return;
    // interface.rdbuf()->pubsetbuf(0, 0); // no buffer
    for (int i = 1; i < this->size.ws_row; i++)
    {
        interface << "\n";
    }
    this->cursorPos(1, 1);
    this->funvector = {[](Console *c)
                       {
                           (void)c->getSize();
                           // std::cout << "1";
                       }};
}

Console c;
int main()
{
    std::signal(SIGINT, sig_handler);
    std::signal(SIGTERM, sig_handler);
    std::signal(SIGWINCH, [](int sig)
                {
                    c.write(c.getSize());
                std::cout <<"new size"<<sig<<std::endl; });
    c.write(c.getSize());
    c.moveCursorRight(15);
    c.moveCursorDown(2);
    c.moveCursorDown();
    c.write("hello");
    c.write("\033[30;107mB");
    c.write("\033[0mHELLO");
    // c.clearScreen();
    /*
        for (int i = 0; i < s.col; i++)
        {
            c << "0";
            c.moveCursorLeft();
            c.moveCursorUp();
        }
        c << "\n";*/
    return c.mainLoop();
}
