# Conio.h for windows and linux

This library implements (parts) the of old Turbo C conio.h

See header file for suported functions.

Help wanted for linux! (thanks comp lang c)


## How to try the original samples? 

Turbo C online
https://www.naclbox.com/gallery/turboc


## Original documentation:

http://docs.embarcadero.com/products/rad_studio/radstudio2007/RS2007_helpupdates/HUpdate4/EN/html/devwin32/coniohpart_xml.html

## VT 100
http://ascii-table.com/ansi-escape-sequences-vt-100.php


## Samples

```c
#include <conio.h>
int main(void)
{
   cprintf("Press any key to continue:");
    while (!kbhit()) /* do nothing */ ;
    cprintf("\r\nA key was pressed...\r\n");
    return 0;
}
```

```c
#include <conio.h>
int main(void)
{
   clrscr();
   gotoxy(10,10);
   cprintf("Current location is X: %d  Y: %d\r\n", wherex(), wherey());
   getch();
   return 0;
}
```

```c

#include <conio.h>
int main(void)
{
    clrscr();
    gotoxy(35, 12);
    cprintf("Hello world");
    getch();
    return 0;
}
```

```c
#include <conio.h>
int main(void)
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
```

```c



#include "conio.h"
#include <unistd.h>

int main(void)
{
    printf("Part1\n");
    printf("Part2\n");

    _setcursortype(_NOCURSOR);
    int y = wherey();
    
    for (int k = 0; k <= 100; k += 5)
    {
        cprintf("[");
        
        
        for (int i = 0; i <= 100 / 5; i++)
        {
            if (i < k / 5)
              cprintf("#");
            else
              cprintf(" ");
        }
        

        printf("] %d%%  ", k);
        sleep(1);
        gotoxy(1, y);
    }
    printf("\n");
    _setcursortype(_NORMALCURSOR);
    printf("Completed\n");
    return 0;

}
```

## Windows WSL

```
sudo service ssh start
```
https://www.hanselman.com/blog/WritingAndDebuggingLinuxCApplicationsFromVisualStudioUsingTheWindowsSubsystemForLinux.aspx
