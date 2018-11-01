# Conio.h for windows and linux

This library implements (parts) the of old Turbo C conio.h
See header file for suported functions.

Help wanted for linux!

## How to try the orignal samples? 

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
