#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "signals.h"

static void sighandler(int signo) {
  if (signo == SIGUSR1) { //kill -30
    int f = fork();
    if(f){
      wait(&f);
      printf("Appended who to f1\n");
    }else{
      int fd = open("f1.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
      dup2(fd, STDOUT_FILENO); 
      execlp("who", "who", NULL);
      close(fd);
    }
  }else if (signo == SIGUSR2) { //kill -31
    int f = fork();
    if(f){
      wait(&f);
      printf("Appended ps to f2\n");
    }else{
      int fd = open("f2.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
      dup2(fd, STDOUT_FILENO); 
      execlp("ps", "ps", NULL);
      close(fd);
    }
  }else if (signo == SIGINT){ //kill -2
    char b1[1000];
    char b2[1000];
    int r=0;
    int f1 = open("f1.txt",O_RDONLY);
    int f2 = open("f2.txt",O_RDONLY);
    if(f1!=-1){
    r=read(f1,&b1,1000);
      b1[r/sizeof(char)]=0;
      printf("\n%s",b1);
    }
    if(f2!=-1){
    r=read(f2,&b2,1000);
      b2[r/sizeof(char)]=0;
      printf("\n%s",b2);
    }
    close(f1);
    close(f2);
    printf("\nSIGINT has quit, master\n");
    exit(-1);
  }
}

int main() {
  signal(SIGUSR1, sighandler);
  signal(SIGUSR2, sighandler);
  signal(SIGINT, sighandler);
  while(1) {
    printf("Anticipating your signal. PID = %d\n", getpid());
    sleep(2);
  }
}
