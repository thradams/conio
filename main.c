#include <stdio.h>
#include <stdlib.h>
#include "conio.h"


int main1(void)
{
    char ch = 0;
    printf("Input a string:");
    while ((ch != '\n'))
    {
        ch = getch();
        putch(ch);
    }
    return 0;
}


int main2(void)
{
    int i, j;
    clrscr();
    for (i=0; i<9; i++)
    {
        for (j=0; j<80; j++)
            cprintf("C");
        cprintf("\r\n");
        textcolor(i+1);
        textbackground(i);
    }
    return 0;
}

int main3(void)
{
    cprintf("Press any key to continue:");
    while (!kbhit()) /* do nothing */ ;
    cprintf("\r\nA key was pressed...\r\n");
    return 0;
}

int main4(void)
{
    clrscr();
    gotoxy(35, 12);
    cprintf("Hello world");
    getch();
    return 0;
}

int main5(void)
{
    char ch;
    printf("Input a character:");
    ch = getche();
    printf("\nYou input a '%c'\n", ch);
    return 0;
}

int main6(void)
{
    int c;
    int extended = 0;
    c = getch();
    if (!c)
        extended = getch();
    if (extended)
        printf("The character is extended\n");
    else
        printf("The character isn't extended\n");
    return 0;
}

int main7(void)
{
    int i;
    clrscr();
    for (i = 0; i < 20; i++)
        cprintf("%d\r\n", i);
    cprintf("\r\nPress any key to clear screen");
    getch();
    clrscr();
    cprintf("The screen has been cleared!");
    getch();
    return 0;
}

int main(void)
{
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();


    return 0;
}

