
//http://docs.embarcadero.com/products/rad_studio/radstudio2007/RS2007_helpupdates/HUpdate4/EN/html/devwin32/coniohpart_xml.html


#ifdef _WIN32

#include <windows.h>
#include "conio.h"

struct text_info
{
  unsigned char winleft;        /* left window coordinate */
  unsigned char wintop;         /* top window coordinate */
  unsigned char winright;       /* right window coordinate */
  unsigned char winbottom;      /* bottom window coordinate */
  unsigned char attribute;      /* text attribute */
  unsigned char normattr;       /* normal attribute */
  unsigned char currmode;       /* current video mode:
                  BW40, BW80, C40, C80, or C4350 */
  unsigned char screenheight;   /* text screen's height */
  unsigned char screenwidth;    /* text screen's width */
  unsigned char curx;           /* x-coordinate in current window */
  unsigned char cury;           /* y-coordinate in current window */
};

static void clearbits(unsigned char * v,
  int bit_index,
  int nbits)
{
  unsigned mask = ~((unsigned char)(0)) << (sizeof(v) * CHAR_BIT - (unsigned char)(nbits));
  mask = mask >> (sizeof(v) * CHAR_BIT - (unsigned char)(bit_index)-(unsigned char)(nbits));
  *v &= ~mask;
}


static void setbits(unsigned char *v,
  int bit_index,
  int nbits,
  unsigned char number)
{
  clearbits(&number, nbits, sizeof(number) * CHAR_BIT - nbits);

  unsigned char big = number;
  big = (big << bit_index);

  clearbits(v, bit_index, nbits);
  *v |= big;
}


static unsigned char getbits(unsigned char v, int bit_index, int nbits)
{
  unsigned char r = v >> bit_index;
  clearbits(&r, nbits, sizeof(unsigned char) * CHAR_BIT - nbits);
  return r;
}


void gettextinfo(struct text_info *r)
{
  if (r == 0)
    return;

  CONSOLE_SCREEN_BUFFER_INFO csbi;
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
  case _NOCURSOR://     (turns off the cursor)
    ci.bVisible = FALSE;
    ci.dwSize = 1;
    break;

  case _SOLIDCURSOR://  (solid block cursor)
    ci.bVisible = TRUE;
    ci.dwSize = 100;
    break;

  default:
  case _NORMALCURSOR: // (normal underscore cursor)
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

void textbackground(int newcolor)
{
  struct text_info ti;
  gettextinfo(&ti);
  unsigned char wColor = ti.attribute;
  unsigned char old = getbits(wColor, 4, 4);
  setbits(&wColor, 4, 4, newcolor);
  textattr(wColor);
}

void textcolor(int newcolor)
{
  struct text_info ti;
  gettextinfo(&ti);
  unsigned char wColor = ti.attribute;
  int old = getbits(wColor, 0, 4);
  setbits(&wColor, 0, 4, newcolor);
  textattr(wColor);
}


int wherex()
{
  CONSOLE_SCREEN_BUFFER_INFO cbsi;
  if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
  {
    return cbsi.dwCursorPosition.X + 1;
  }
  return -1;
}

int wherey()
{
  CONSOLE_SCREEN_BUFFER_INFO cbsi;
  if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
  {
    return cbsi.dwCursorPosition.Y;
  }
  return -1;
}

void gotoxy(int x, int y)
{
  COORD point ;
  point.X = x - (short)1;
  point.Y = y;
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



#elif __linux__


#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "conio.h"

int kbhit(void)
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


static int getCursorPosition2(int *rows, int *cols)
{
  *rows = -1;
  *cols = -1;

  struct termios orig_termios;
  int er = tcgetattr(STDIN_FILENO, &orig_termios);
  if (er == -1)
  {
    printf("error\n");
    return -1;
  }


  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
  {
    printf("error\n");
    return -1;
  }

  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[') return -1;

  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
  {
    printf("error\n");
    return -1;
  }


  return 0;
}

int wherex(void)
{
  int x, y;
  getCursorPosition2(&x, &y);
  return x;
}

int wherey(void)
{
  int x, y;
  getCursorPosition2(&x, &y);
  return y;
}


void gotoxy(int x, int y)
{
  printf("\x1b[%d;%dH", y, x);
  fflush(stdout);
}

void clrscr()
{
  printf("\x1b[2J\x1b[1;1H");
  fflush(stdout);
}

void textcolor(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[30m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[30m";
    break;

  case BLUE:
    s = "\x1b[34m";
    break;

  case GREEN:
    s = "\x1b[32m";
    break;

  case CYAN:
    s = "\x1b[36m";
    break;

  case RED:
    s = "\x1b[31;1m";
    break;

  case MAGENTA:
    s = "\x1b[35m";
    break;

  case BROWN:
    s = "\x1b[31m";
    break;

  case LIGHTGRAY:
    s = "\x1b[30;1m";
    break;

  case DARKGRAY:
    s = "\x1b[30m";
    break;

  case LIGHTBLUE:
    s = "\x1b[34;1m";
    break;

  case LIGHTGREEN:
    s = "\x1b[32,1m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[36;1m";
    break;

  case LIGHTRED:
    s = "\x1b[31;1m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[35;1m";
    break;

  case YELLOW:
    s = "\x1b[33;1m";
    break;

  case WHITE:
    s = "\x1b[37;1m";
    break;

  case BLINK:
    s = "\x1b[30m";
    break;
  };

  printf(s);
}

void textbackground(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[40m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[40m";
    break;

  case BLUE:
    s = "\x1b[44m";
    break;

  case GREEN:
    s = "\x1b[42m";
    break;

  case CYAN:
    s = "\x1b[46m";
    break;

  case RED:
    s = "\x1b[41;1m";
    break;

  case MAGENTA:
    s = "\x1b[45m";
    break;

  case BROWN:
    s = "\x1b[41m";
    break;

  case LIGHTGRAY:
    s = "\x1b[40;1m";
    break;

  case DARKGRAY:
    s = "\x1b[40m";
    break;

  case LIGHTBLUE:
    s = "\x1b[44;1m";
    break;

  case LIGHTGREEN:
    s = "\x1b[42,1m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[46;1m";
    break;

  case LIGHTRED:
    s = "\x1b[41;1m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[45;1m";
    break;

  case YELLOW:
    s = "\x1b[43;1m";
    break;

  case WHITE:
    s = "\x1b[47;1m";
    break;

  case BLINK:
    s = "\x1b[40m";
    break;
  };

  printf(s);
}


/* Read 1 character - echo defines echo mode */
static char getch_(int echo)
{
  struct termios orig_termios;
  if (tcgetattr(STDIN_FILENO, &orig_termios) != -1)
  {
    return -1;
  }


  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ICANON | IEXTEN | ISIG);

  if (echo)
    raw.c_lflag &= ~(ECHO);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
  {
    return -1;
  }

  char ch = getchar();

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
  {
    return -1;
  }


  return ch;
}

/* Read 1 character without echo */
int getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
int getche(void)
{
  return getch_(1);
}

int putch(int c)
{
  printf("%c", (char)c);
}


int cputs(const char *str)
{
  printf("%s", str);
  return 1;
}

void _setcursortype(int cur_t)
{
  switch (cur_t)
  {
  case _NOCURSOR:
    printf("\x1b[?25l");
    break;

  case _NORMALCURSOR:
    printf("\x1b[?25h");
    break;

  case _SOLIDCURSOR:
    printf("\x1b[?25h");
    break;
  }
}


#endif //linux




