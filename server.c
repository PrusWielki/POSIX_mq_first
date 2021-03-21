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

int main()
{
    mqd_t PID_s,PID_d,PID_m;
    struct timespec t= {1,0};
    int pid=(int)getpid();
    char *pid_str=malloc(sizeof(char)*10);
    const char *pid_dest=malloc(sizeof(char)*10);
    char *pid_base=malloc(sizeof(char)*10);
    const char* pid_s=malloc(sizeof(char)*10);
    struct mq_attr attr;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=1;
    pid_base[0]='//';
    snprintf(pid_str,10,"%d",pid);
    strcat(pid_base,pid_str);
    strcpy(pid_dest,pid_base);
    strcat(pid_dest,"_s");
    printf("%d   %s\n",pid,pid_dest);
    if((PID_s=TEMP_FAILURE_RETRY(mq_open(pid_dest, O_RDWR|O_NONBLOCK | O_CREAT, 0600, &attr)))==(mqd_t)-1) ERR("mq open");
    printf("Queue PID_s created\n");
    strcpy(pid_dest,pid_base);
    strcat(pid_dest,"_d");
    printf("%d   %s\n",pid,pid_dest);
    if((PID_d=TEMP_FAILURE_RETRY(mq_open("/PID_d", O_RDWR|O_NONBLOCK | O_CREAT, 0600, &attr)))==(mqd_t)-1) ERR("mq open");
    printf("Queue PID_d created\n");
    strcpy(pid_dest,pid_base);
    strcat(pid_dest,"_m");
    printf("%d   %s\n",pid,pid_dest);
    if((PID_m=TEMP_FAILURE_RETRY(mq_open("/PID_m", O_RDWR|O_NONBLOCK | O_CREAT, 0600, &attr)))==(mqd_t)-1) ERR("mq open");
    printf("Queue PID_m created\n");
    nanosleep(&t,NULL);
    if(mq_close(PID_s)==-1)ERR("close PID_s");
    if(mq_close(PID_d)==-1)ERR("close PID_d");
    if(mq_close(PID_m)==-1)ERR("close PID_m");
    return 0;
}
