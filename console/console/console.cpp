// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"

int main(void)
{

    int i;
    char buffer[80*25];
    cputs("This will be stored in the buffer\n");
    cputs("This also\n");
    gettext(1, 1, 10, 1, buffer);
    gotoxy(1, 25);
    clrscr();
    gotoxy(1, 25);
    cputs("hit some key to restore");
    getch();
    puttext(1, 1, 80, 25, buffer);
    gotoxy(1, 25);
    return 0;
}