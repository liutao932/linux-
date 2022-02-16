#ifndef _PROTO_H_
#define _PROORO_H_
#define NAMESIZE 11
#define RCVPORT "1989"


struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
}__attribute__((packed));




#endif
