#include <graphics.h>
#include <conio.h>
 
main()
{
   int gd=DETECT,gm,points[]={320,150,440,340,230,340,320,150};
 
   initgraph(&gd, &gm, "C:\\TC\\BGI");
 
   fillpoly(4, points);
 
   getch();
   closegraph();
   return 0;
}