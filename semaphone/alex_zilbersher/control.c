#include "semaphone.h"

int take_command(int fd,int shmd,int semd){
  int shmkey = ftok("Z.txt",77);
  int semkey = ftok("control.c",77);
  char s[256];
  //struct shmid_ds d;
  printf("Ready to create, remove, or exit: ");
  fgets(s,255,stdin);
  s[strlen(s)-1]=0;
  if(strcmp(s,"create")==0){
    printf("Creating/Rewriting file, shared memory and semaphore\n");
    fd=open("Z.txt",O_CREAT | O_WRONLY | O_TRUNC,0664);
    close(fd);
    shmd = shmget(shmkey, 1024, IPC_CREAT | IPC_EXCL | 0664);
    semd = semget(semkey, 1, IPC_CREAT | 0664);
    union semun su;
    su.val = 1;
    semctl(semd, 0, SETVAL, su);
    printf("Completed\n");
  }else if(strcmp(s,"remove")==0){
    printf("Removing the shared memory and semaphore\n");
    shmd = shmget(shmkey, 1024, 0664);
    semd = semget(semkey, 1, 0664);
    shmctl(shmd, IPC_RMID, 0);
    semctl(semd, 0, IPC_RMID);
    fd = open("Z.txt", O_RDONLY);
    if (fd >= 0) {
      int s = lseek(fd, 0, SEEK_END);
      char * f = (char *) malloc(sizeof(char) * s);
      lseek(fd, 0, SEEK_SET);
      s = read(fd, f, s);
      printf("Read %d bytes of file:\n%s\n", s, f);
      close(fd);
      free(f);
      printf("Completed\n");
    }
  }else if(strcmp(s,"exit")==0){
    kill(getppid(),SIGINT);
    exit(-1);
  }
  take_command(fd,shmd,semd);
  return(0);
}
