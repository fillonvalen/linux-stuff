#ifndef __CONIO4LINUX_H
#define __CONIO4LINUX_H
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

void clearLine()
{
    printf("\033[K");
}

void insertLine()
{
    printf("\x1b[1L");
}

void deleteLine()
{
    printf("\033[1M");
}



int ungetch(int ch)
{
    return ungetc(ch, stdin);
}

int setEchoMode(bool enable)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    if (enable)
        newt.c_lflag |= ECHO;
    else
        newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int getch()
{
    return setEchoMode(false);
}

int getche()
{
    return setEchoMode(true);
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int putch(const char c)
{
    printf("%c", c);
    return (int)c;
}

int cputs(const char *str)
{
    printf("%s", str);
    return 0;
}
int gettext(int l, int t, int r, int b, void *destination)
{
    // Provide a meaningful implementation or remove the parameters if not needed.
    return 0;
}


// DEV C++ only has the following functions (version: 4.9.9.2)
#define _cprintf cprintf
#define _cscanf cscanf
#define _cputs cputs
#define _getche getche
#define _kbhit kbhit
#define _putch putch
#define _ungetch ungetch

#endif
