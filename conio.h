
#ifndef _CONIO_H_
#define _CONIO_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

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

    char * cgets(char * _Buffer);

    void clreol(void);
    void clrscr();
    int cputs(const char *str);

    void delline(void);
    int getch(void);
    int getche(void);

    char *getpass(const char *prompt);
    int gettext(int left, int top, int right, int bottom, void*destin);
    void gettextinfo(struct text_info *r);
    void gotoxy(int x, int y);
    void highvideo();

    void insline(void);
    int kbhit(void);

    void lowvideo();
    int movetext(int left, int top, int right, int bottom, int destleft, int desttop);
    void normvideo();

    int putch(int c);

    int puttext(int left, int top, int right, int bottom, const char*source);
    void _setcursortype(int cur_t);
    void textattr(int newattr);
    int textbackground(int newcolor);
    int textcolor(int newcolor);
    int ungetch(int ch);
    int wherex();
    int wherey();

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif //CONIO_H

