 #include<stdio.h>
 #include<stdlib.h>

 int main(int argc,char ** argv)
 {
         int count = 0;
         if(argc < 2)
         {
                 fprintf(stderr,"Useg:%s<src_file>",argv[0]);
                 exit(1);
         }

         FILE * fbs = NULL;
         fbs = fopen(argv[1],"r");
         if(fbs == NULL)
         {
                 perror("fopen()");
                 exit(1);
         }
         while(fgetc(fbs) != EOF)
         {
                 count++;
         }
         printf("%d\n",count);
         fclose(fbs);
 }
