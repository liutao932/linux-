#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX 100
int main()
{
  char str[4] = "|/-\\";
  int i = 0;
  char buf[MAX + 1];
  memset(buf,'\0',MAX + 1);
  while(i <= 100)
  {
    printf("[%-100s][%3d]%%[%c]\r",buf,i,str[i%4]);
    if(i == 100)
    {
      sleep(2);
    }
    fflush(stdout);
    buf[i] = '=';
    i++;
    usleep(50000);
  }
  printf("\n");
}
