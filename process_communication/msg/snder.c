#include<stdio.h>
#include<stdlib.h>
#include"proto.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

int main()
{
    struct msg_st sbuf;
    key_t key = ftok(KEYPATH,KEYPROJ);
    if(key < 0)
    {
        perror("ftok()");
        exit(1);
    }
    int msgid = msgget(key,0);
    if(msgid < 0)
    {
        perror("ftok()");
        exit(1);
    }   
    sbuf.math  = 1;
    strcpy(sbuf.name,"Alan");
    sbuf.math = rand() %100;
    sbuf.chinese = rand() % 100;
    if( msgsnd(msgid, &sbuf,sizeof(sbuf) - sizeof(long),0) < 0)
         {
              perror("msgsnd()");
              exit(1);
         }

  puts("ok!");
}