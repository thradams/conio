#include "conio.h"

#define __STDC__ 1
#include <conio.h> //from window
#undef __STDC__ 
#define __STDC__ 0


#include <assert.h>
#include <windows.h>

/* a = target variable, b = bit number to act upon 0 - n */

#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) ((x) & (y))

union BB
{
    unsigned char v;
    int f : 4;
    int s : 4;
};

int GetLow(unsigned char value)
{
    union BB b;
    b.v = value;
    return b.f;
}

int GetHigh(unsigned char value)
{
    union BB b;
    b.v = value;
    return b.s;
}

void SetLow(unsigned char* value, unsigned char n)
{
    union BB b;
    b.v = 0;
    b.f = n;
    *value = b.v;
}
void SetHigh(unsigned char* value, unsigned char n)
{
    union BB b;
    b.v = 0;
    b.s = n;
    *value = b.v;
}

char * cgets(char * _Buffer)
{
    return _cgets(_Buffer);
}

int getch(void)
{
    return _getch();
}

int getche(void)
{
    return _getche();
}

int kbhit(void)
{
    return _kbhit();
}

int cputs(const char *str)
{
    return _cputs(str);
}

void gettextinfo(struct text_info *r)
{
    if (r == 0)
        return;

    struct _CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    r->attribute = (unsigned char)csbi.wAttributes;
    r->curx = (unsigned char)csbi.dwCursorPosition.X;
    r->cury = (unsigned char)csbi.dwCursorPosition.Y;
    r->screenwidth = (unsigned char)csbi.dwMaximumWindowSize.X;
    r->screenheight = (unsigned char)csbi.dwMaximumWindowSize.X;
    r->winleft = (unsigned char)csbi.srWindow.Left;
    r->wintop = (unsigned char)csbi.srWindow.Top;
    r->winright = (unsigned char)csbi.srWindow.Right;
    r->winbottom = (unsigned char)csbi.srWindow.Bottom;
    r->normattr = 0;
    r->currmode = 3;
}

void _setcursortype(int cur_t)
{
    CONSOLE_CURSOR_INFO ci;
    switch (cur_t)
    {
    case _NOCURSOR://     (turns off the cursor
        ci.bVisible = FALSE;
        ci.dwSize = 0;
        break;
    case _SOLIDCURSOR://  (solid block cursor
        ci.bVisible = TRUE;
        ci.dwSize = 100;
        break;
    default:
    case _NORMALCURSOR: // (normal underscore cursor
        ci.bVisible = TRUE;
        ci.dwSize = 50;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void textattr(int newattr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
}

int putch(int c)
{
    return _putch(c);
}

void clreol(void)
{
    //clreol clears all characters from the curso
    //position to the end of the line within th
    //current text window, without moving th
    //cursor
}

char *getpass(const char *prompt)
{
    //reads passwor
    //  getpass reads a password from the syste
    //console, after prompting with th
    //null-terminated string prompt and disablin
    //the echo

    //It returns a pointer to a null-terminate
    //string of up to eight characters (no
    //counting the null terminator)

    return 0;
}

void delline(void)
{
    //tODO inserts blank lin
}

void insline(void)
{
    //tODO inserts blank lin
}

int movetext(int left, int top, int right, int bottom, int destleft, int desttop)
{
    //TOD
    return 0;
}

int gettext(int left, int top, int right, int bottom, void*destin)
{
    if (destin == 0)
        return 0;
    char * pszText = (char *)destin;

    int count = 0;
    for (int k = top; (k <= bottom) && (*pszText); k++)
    {
        for (int i = left; (i <= right) && (*pszText); i++)
        {
            COORD point = { (SHORT)i, (SHORT)k
            };

            wchar_t ch;
            DWORD c;
            ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &ch, 1, point, &c);
            *pszText = (char)ch;
            count++;
            pszText++;
        }
    }
    *pszText = 0;
    return count;
}

int puttext(int left, int top, int right, int bottom, const char*source)
{
    if (source == 0)
        return 0;
    char * pszText = (char *)source;
    struct text_info ti;
    gettextinfo(&ti);
    int count = 0;
    for (int k = top; (k <= bottom) && (*pszText); k++)
    {
        for (int i = left; (i < right) && (*pszText); i++)
        {
            gotoxy(i, k);
            putch(*pszText);
            count++;
            pszText++;
        }
    }
    gotoxy(ti.curx, ti.cury);
    return count;
}

int textbackground(int newcolor)
{
    struct text_info ti;
    gettextinfo(&ti);
    unsigned char wColor = ti.attribute;
    int old = GetHigh(wColor);
    SetHigh(&wColor, newcolor);
    //unsigned char old = getbits(unsigned char, wColor, 4, 4);
    //setbits(unsigned char, wColor, 4, 4, newcolor);
    textattr(wColor);
    return old;
}

int textcolor(int newcolor)
{
    struct text_info ti;
    gettextinfo(&ti);
    unsigned char wColor = ti.attribute;
    int old = GetLow(wColor);
    //setbits(unsigned char, wColor, 0, 4,  newcolor);
    SetLow(&wColor, (unsigned char)newcolor);
    textattr(wColor);
    return old;
}

void highvideo()
{
    struct text_info ti;
    gettextinfo(&ti);
    //setbits(ti.attribute, 3, 1, 1);
    ti.attribute |= 1 << 3;
    textattr(ti.attribute);
}

void lowvideo()
{
    struct text_info ti;
    gettextinfo(&ti);
    // setbits(ti.attribute, 3, 1, 0);
    ti.attribute &= ~(1 << 3);
    textattr(ti.attribute);
}

void normvideo()
{
    struct text_info ti;
    gettextinfo(&ti);
    //setbits(ti.attribute, 3, 1, 0);
    //setbits(ti.attribute, 7, 1, 0);
    ti.attribute &= ~(1 << 3);
    ti.attribute &= ~(1 << 7);
    textattr(ti.attribute);
}

int wherex()
{
    struct text_info ti;
    gettextinfo(&ti);
    return ti.curx;
}

int wherey()
{
    struct text_info ti;
    gettextinfo(&ti);
    return ti.cury;
}

void gotoxy(int x, int y)
{
    COORD point = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void clrscr()
{
    COORD coordScreen = { 0, 0 };
    unsigned long cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    unsigned long dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

int ungetch(int ch)
{
    return _ungetch(ch);
}

