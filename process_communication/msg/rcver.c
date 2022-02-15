#include<stdio.h>
#include<stdlib.h>
#include"proto.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main()
{
    struct msg_st rbuf;
    
    key_t key = ftok(KEYPATH,KEYPROJ);
    if(key < 0)
    {
        perror("ftok()");
        exit(1);
    }
    int msgid = msgget(key,IPC_CREAT|0600);
    if(msgid < 0)
    {
        perror("ftok()");
        exit(1);
    }
    while(1)
    {
         if( msgrcv(msgid, &rbuf,sizeof(rbuf) - sizeof(long),0,0) < 0)
         {
              perror("ftok()");
              exit(1);
         }
         printf("NAME= %s\n",rbuf.name);
         printf("MATH= %d\n",rbuf.math);
         printf("CHINESE = %d\n",rbuf.chinese);   
    }
    msgctl(msgid,IPC_RMID,NULL);
    exit(0);    
}