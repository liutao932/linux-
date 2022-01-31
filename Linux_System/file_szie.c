 #include<stdio.h>
 #include<stdlib.h>
 int main(int argc,char **argv)
 {
         FILE * fdp = NULL;
         int count = 0;
         if(argc < 2)
         {
                 printf("Uage%s:<file>",argv[1]);
                 exit(1);
         }
         fdp = fopen(argv[1],"r");
         if(fdp == NULL)
         {
             perror("fopen()");
             exit(1);
         }
         while(fgetc(fdp) != EOF)
         {
                 count++;
         }
         printf("conut = %d\n",count);
         fclose(fdp);
 
 }
