#include <stdio.h>
#include "conio.h"

// sudo service ssh start
//~/projects/Linux/bin/x64/Debug

void Test1()
{
  int i;
  c_clrscr();
  for (i = 0; i < 20; i++)
  {
    printf("%d\r\n", i);
  }
  printf("\r\nPress any key to clear screen");
  c_getch();
  c_clrscr();
  printf("The screen has been cleared!");
  c_getch();  
}


void Test2()
{

  struct text_info ti;
  c_gettextinfo(&ti);
  printf("attribute        %2d\r\n", ti.attribute);
  printf("normal attribute %2d\r\n", ti.normattr);
  printf("screen height    %2d\r\n", ti.screenheight);
  printf("screen width     %2d\r\n", ti.screenwidth);
  printf("current x        %2d\r\n", ti.curx);
  printf("current y        %2d\r\n", ti.cury);

}

void Test3()
{
  /*
  Gets character from keyboard, does not echo to screen. 
  getch reads a single character directly from the keyboard, 
  without echoing to the screen
  */

  int c;
  int extended = 0;
  c = c_getch();
  
  if (!c)
    extended = c_getch();
  if (extended)
    printf("The character is extended\n");
  else
    printf("The character isn't extended\n");
}

void Test4()
{
  int ch;
  printf("Input a character:");
  ch = c_getche();
  if (ch)
  {
    printf("\nYou input a '%c'\n", ch);
  }
 

}

void Test5()
{
  int i;
  c_clrscr();
  for (i = 0; i < 9; i++)
  {
    c_textattr(i + ((i + 1) << 4));
    printf("This is a test\r\n");
  }
}

void Test6()
{
  c_clrscr();
  c_gotoxy(35, 12);
  printf("Hello world");
  c_getch();
}

void  Test7()
{
  printf("Press any key to continue:");
  while (!c_kbhit())
  {
  }
  
  printf("\r\nA key was pressed...\r\n"); 
  
}
int main(void)
{
  //Test1();
  //Test2();
  Test3();
  //Test4();
  //Test5();
  //Test6();
  //Test7();
  return 0;
}
