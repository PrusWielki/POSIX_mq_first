#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <mqueue.h>
#include <pthread.h>
//#include <string.h>

#define ERR(source) (fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
                     perror(source),kill(0,SIGKILL),\
		     		     exit(EXIT_FAILURE))

int main(int argc, char**argv)
{
    //if(argc!=2)
       // ERR("Wrong number of arguments");

    mqd_t PID;
    struct timespec t= {1,0};
    int pid=(int)getpid();
    char *pid_str=malloc(sizeof(char)*10);
    const char *pid_dest=malloc(sizeof(char)*10);
    char*pid_base=malloc(sizeof(char)*10);


    struct mq_attr attr;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=1;

    pid_base[0]='//';

    snprintf(pid_str,10,"%d",pid);
    strcat(pid_base,pid_str);
    strcpy(pid_dest,pid_base);
    printf("%d   %s\n",pid,pid_dest);
    if((PID=TEMP_FAILURE_RETRY(mq_open(pid_dest, O_RDWR|O_NONBLOCK | O_CREAT, 0600, &attr)))==(mqd_t)-1) ERR("mq open");
   printf("Queue PID_s created\n");

    nanosleep(&t,NULL);
    if(mq_close(PID)==-1)ERR("close PID_s");

    return 0;
}
