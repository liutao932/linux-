#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>
#include<errno.h>
#include<unistd.h>
#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFSIZE 1024
enum 
{
	STATE_R = 1,
	STATE_W,
	STATE_Ex,
	STATE_T
};
struct fsm_st
{
	int state;
	int sfd;
	int dfd;
	char buf[BUFSIZE];
	int len;
	int pos;
	char *errstr;
};
static void fsm_driver(struct fsm_st* st)
{
	int ret;
	switch(st->state)
	{
		case STATE_R:
		st->len = read(st->sfd,st->buf,BUFSIZE);
		if(st->len == 0)
		{
			st->state = STATE_T;
		}
		else if(st-> len < 0)
		{
			if(errno == EAGAIN)
			{
				st->state = STATE_R;
			}
			else
			{
				st->errstr = "read()";
				st->state = STATE_Ex;
			}
		}
		else
		{
			st->pos = 0;
			st->state = STATE_W;
		}
		break;
		case STATE_W:
		ret = write(st->dfd,st->buf+st->pos,st->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
				{
					st->state = STATE_W;
				}
				else
				{
					st->errstr = "wirte()";
					st->state = STATE_Ex;
				}
			}
			else
			{
				st->pos += ret;
				st->len -= ret;
				if(st->len == 0)
				{
					st->state = STATE_R;
				}
				else
				{
					st->state = STATE_W;
				}
			}
		break;
		case STATE_Ex :
		perror(st->errstr);
		st->state = STATE_T;
		break;
		case STATE_T:
		/*do samething*/
		break;
		default:
		abort();
		break;
	}
}

void relay(int fd1,int fd2)
{
	int fd1_save,fd2_save;

	struct fsm_st fsm12;
	struct fsm_st fsm21;
	fd1_save = fcntl(fd1,F_GETFL);
	fcntl(fd1,F_SETFL,fd1_save|O_NONBLOCK);

	fd2_save = fcntl(fd2,F_SETFL);
	fcntl(fd2,F_SETFL,fd2_save|O_NONBLOCK);
	

	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;


	fsm21.state = STATE_R;
	fsm21.sfd = fd1;
	fsm21.dfd = fd2;

	while(fsm12.state != STATE_T || fsm21.state != STATE_T)
	{
		fsm_driver(&fsm12);
		fsm_driver(&fsm21);
	}

	fcntl(fd1,F_SETFL,fd1_save);
	fcntl(fd2,F_SETFL,fd2_save);
}
int main()
{	
	int fd1,fd2;
	fd1 = open(TTY1,O_RDWR);
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	fd2 = open(TTY2,O_RDWR|O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	relay(fd1,fd2);

}
