#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
    FILE * fp = NULL;
    if(argc <2)
     {
       fprintf(stderr,"Uage:%s<filename>",argv[0]);
     }
    fp = fopen(argv[1],"r");
    if(NULL == fp)
    {
        perror("fopen()");
        exit(1);
    }

    fseek(fp,0,SEEK_END);
    printf("%d\n",ftell(fp));
}
