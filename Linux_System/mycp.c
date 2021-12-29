 #include<stdio.h>
 #include<stdlib.h>
 int main(int argc,char *argv[])
 {
         int ch;
         FILE *ftb,*ftp;
         if(argc <3)
         {
                 printf("uage%s :<srcfile> <desfile>\n",argv[0]);
                 exit(1);
         }
         ftb = fopen(argv[1],"r");
         if(ftb == NULL)
         {
                 perror("fopen()");
                 exit(1);
         }
         ftp = fopen(argv[2],"w");
         if(ftp ==  NULL)
         {
                 perror("fopen()");
                 exit(1);
         }
         while(1)
         {
              ch = fgetc(ftb);
              if(ch ==  EOF)
                  break;
              fputc(ch,ftp);
         }
         fclose(ftp);
         fclose(ftb);
         exit(0);
 }
