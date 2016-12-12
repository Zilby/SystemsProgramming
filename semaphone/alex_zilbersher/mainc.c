#include "semaphone.h"

int f=0;

static void sighandler(int signo) {
  if (signo==SIGINT){
    /*if(f){
      wait(&f);
      printf("\nZilbaphore Quit\n");
      exit(-1);
    }else{
      printf("\nZilbaphore Quit\n");
      exit(-1);
      }*/
  }
}

int main(){
  while(1){
    f = fork();
    if(f){
      wait(&f);
    }else{
      take_command(0,0,0);
    }
  }return 0;
}
