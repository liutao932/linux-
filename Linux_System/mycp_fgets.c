#include<stdio.h>
#include<stdlib.h>
#define BUFSIZE 1024


int main(int argc,char **argv)
{

        if( argc < 3)
        {
                fprintf(stderr,"Usage:%s<src_file><des_file>\n",argv[0]);
                exit(1);
        }
        char buf[BUFSIZE];
        FILE *fbs,*fdp;
        int ch;
        fbs = fopen(argv[1],"r");
        if(fbs == NULL)
        {
                perror("fopen");
                exit(-1);
        }
        fdp = fopen(argv[2],"w");
        if(fdp == NULL)
        {
                fclose(fbs);
                perror("fopen()");
                exit(-1);
        }
        while(fgets(buf,BUFSIZE,fbs) != NULL)
        {
                fputs(buf,fdp);
        }
        fclose(fdp);
        fclose(fbs);
        exit(0);
}
