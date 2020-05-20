#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  int i;
     time_t t;
int y;

 int funkcja_biblioteka1()
 {
  srand(time(t));
y=rand()%10+1;
   return y;
 }
 int funkcja_biblioteka2()
 {

  srand(time(0));
i=rand()%10+1;
if(i==y)
    i=rand()%10+1;

   return i;
 }
