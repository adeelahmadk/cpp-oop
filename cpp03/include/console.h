// console.h
// https://github.com/BrentFarris/lttp/blob/master/src/client/display.h
#ifndef _CONSOLE_H
#define _CONSOLE_H

#if !defined(_WIN32) && !defined(_WIN64)

#include <iostream>
#include <cstdio>
#include <termios.h> // general terminal interface: tcgetattr, tcsetattr, tcflushcgetattr, tcsetattr, tcflush
#include <unistd.h> // synchronous I/O multiplexing: select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO
#include <fcntl.h>
using namespace std;

enum COLORS {
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    NORMAL
};

const char *textColor[9] = {
  "\033[0;30m",// black
  "\033[0;31m",// red
  "\033[0;32m",// green
  "\033[0;33m",// yellow
  "\033[0;34m",// blue
  "\033[0;35m",// magenta
  "\033[0;36m",// cyan
  "\033[0;37m",// white
  "\033[0m"    // normal
};

const char *boldColor[9] = {
  "\033[1;30m",
  "\033[1;31m",
  "\033[1;32m",
  "\033[1;33m",
  "\033[1;34m",
  "\033[1;35m",
  "\033[1;36m",
  "\033[1;37m",
  "\033[0m"    // normal
};

const char *bgColor[9] = {
  "\033[40m",
  "\033[41m",
  "\033[42m",
  "\033[43m",
  "\033[44m",
  "\033[45m",
  "\033[46m",
  "\033[47m",
  "\033[0m"    // normal
};

// clear console screen and move cursor to {X, Y}
#define gotoxy(X,Y) printf( "\033[%d;%dH", Y, X )
// clear console screen and move cursor to {0, 0}
#define clrscr() printf( "\033[2J\x1B[H" )

void textcolor( COLORS color, bool bold = false )
{
    // set console text color
    if( bold )
    {
        cout << boldColor[ color ];
    }
    else
    {
        cout << textColor[ color ];
    }
}

void textbackground( COLORS color )
{
    // set console text background color
    cout << bgColor[ color ];
}

void flush_stdin()
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
}

/**
 *  set_mode_
 *
 *  enable/disable terminal echo
 *
 *  want_key: enable/disable echo, logic is reversed.
 *
 *  returns: nothing
 *
 */
void set_mode_(int want_key)
{
    static struct termios savedState, newState;
    if (!want_key) {
        // resotre saved state
        tcsetattr(STDIN_FILENO, TCSANOW, &savedState);
        return;
    }

    // save current state
    tcgetattr(STDIN_FILENO, &savedState);
    newState = savedState;
    newState.c_lflag &= ~(ICANON | ECHO);
    newState.c_cc[VMIN] = 1;
    // update the state
    tcsetattr(STDIN_FILENO, TCSANOW, &newState);
}

/**
 *  get_key_
 *
 *  read and return a keypress
 *
 *  returns: nothing
 *
 */
int get_key_()
{
    int c = 0;
    struct timeval tv;
    fd_set fs;
    tv.tv_usec = tv.tv_sec = 0;

    FD_ZERO(&fs);
    FD_SET(STDIN_FILENO, &fs);
    select(STDIN_FILENO + 1, &fs, 0, 0, &tv);
    if (FD_ISSET(STDIN_FILENO, &fs)) {
        c = getchar();
        set_mode_(0);
    }
    return c;
}

/**
 *  getch
 *
 *  read a keypress without echo
 *
 *  returns: the key code read
 *
 */
int getch(){
    int c = 0;
    set_mode_(1);
    /* flush pending input so we won't crash a space ship just
       because user accidentally typed 'y' before we even prompted*/
    flush_stdin();
    /*  force C library buffers to be written to kernel buffers */
    fflush(stdout);
    while ( ! ( c = get_key_() ) ) usleep(1000);
    return c;
}

/**
 *  getche
 *
 *  read a keypress with echo
 *
 *  returns: the key code read
 *
 */
int getche(){
    int c = getch();
    printf( "%c", c );
    return c;
}

#else

#include <cstdio>
#include <windows.h>

void gotoxy(X,Y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {X, Y};
    SetConsoleCursorPosition(hConsole, pos);
}

void _cls(HANDLE hConsole)
{
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void clrscr()
{
    HANDLE hStdout;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    _cls(hStdout);
}

#define getch() _getch()

#endif

#endif
