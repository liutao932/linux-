#ifndef _PROTO_H_
#define _PROTO_H
#define KEYPATH "/etc/services"
#define KEYPROJ 'g'
#define NAMESIZE 32

struct msg_st
{
     long mytype;
     char name[NAMESIZE];
     int math;
     int chinese;
};





#endif