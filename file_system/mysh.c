#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<glob.h>
#include<wait.h>
#include<string.h>
#define CONTINE " \t\n"
struct cmd_st
{
        glob_t globres;
};
static void promat(void)
{
        printf("mysh0.1$:");
}
static void  parse(char * buf,struct cmd_st * st)
{
        char *tok;
        int i = 0;
        while(1)
        {
                tok = strsep(&buf,CONTINE);
                if(tok == NULL)
                        break;
                if(tok[0] == '\0')
                        continue;
                glob(tok,GLOB_NOCHECK|GLOB_APPEND * i,NULL,&st->globres);//frist nor append
                i = 1;
        }
}
int main()
{
        struct cmd_st st;
        char *bufline = NULL;
        pid_t pid;
        size_t bufsize = 0;
        while(1)
        {
                promat();
                if(getline(&bufline,&bufsize,stdin) < 0)
                        break;
                parse(bufline,&st);
                if(0)
                {
                        /*doing samething */
                }
                else
                {
                        pid = fork();
                        if(pid < 0)
                        {
                                perror("fork()");
                                exit(1);

                        }
                        else if( pid == 0)   //child
                        {
                                execvp(st.globres.gl_pathv[0],st.globres.gl_pathv);
                                perror("execXX()");
                                exit(1);
                        }
                        else   //parent
                        {
                                wait(NULL);
                        }
                }
        }
}
