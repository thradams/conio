
#ifndef _CONIO_H_
#define _CONIO_H_

#ifdef _WIN32
#include <conio.h> //from window
#endif

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
 
#include <stdio.h>
#define cprintf printf

enum COLORS
{
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHTGRAY = 7,
  DARKGRAY = 8,
  LIGHTBLUE = 9,
  LIGHTGREEN = 10,
  LIGHTCYAN = 11,
  LIGHTRED = 12,
  LIGHTMAGENTA = 13,
  YELLOW = 14,
  WHITE = 15,
  BLINK = 128
};

enum CURSORTYPE
{
  _NOCURSOR,//     (turns off the cursor
  _SOLIDCURSOR,//  (solid block cursor
  _NORMALCURSOR // (normal underscore cursor
};


#ifndef _WIN32
char * cgets(char * _Buffer);
int cputs(const char *str);
int getch(void);
int getche(void);
/*
Checks for currently available keystrokes.
kbhit checks to see if a keystroke is currently available.
Any available keystrokes can be retrieved with getch or getche.
*/
int kbhit(void);
int putch(int c);
int ungetch(int ch);
#else
#define getch _getch
#define putch _putch
#define kbhit _kbhit
#define cputs _cputs
#define ungetch _ungetch
#define getche _getche
#define putch _putch
#define cputs _cputs
#endif


void clrscr();
void gotoxy(int x, int y);
void _setcursortype(int cur_t);
void textbackground(int newcolor);
void textcolor(int newcolor);
int wherex(void);
int wherey(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif //CONIO_H


