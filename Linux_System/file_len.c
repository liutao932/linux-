#include<stdio.h>
#include<stdlib.h>



int main(int argc,char **argv)
{
        if(argc < 2)
        {
                fprintf(stderr,"Usge:%s<dst_file>",argv[1]);
                exit(1);
        }
        FILE *fp = NULL;
        fp = fopen(argv[1],"r");
        if(fp == NULL)
        {
                perror("fopen()");
                exit(1);
        }
        fseek(fp,0,SEEK_END);
        printf("%ld",ftell(fp));
}
