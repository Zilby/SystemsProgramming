#include "semaphone.h"

int write_stuff(int fd,int shmd,int semd){
  int shmkey = ftok("Z.txt",77);
  int semkey = ftok("control.c",77);
  shmd = shmget(shmkey, 1024, 0664);
  semd = semget(semkey, 1, 0664);
  char s[1024];
  struct shmid_ds d;
  printf("Enter text to  write or exit: ");
  fgets(s,1023,stdin);
  s[strlen(s)-1]=0;
  if(strcmp(s,"exit")==0){
    kill(getppid(),SIGINT);
    exit(-1);
  }
  struct sembuf semb;
  semb.sem_op = -1;
  semb.sem_num = 0;
  semb.sem_flg = SEM_UNDO;
  printf("Trying to access file\n");
  if (semop(semd,&semb,1) != -1) {
    fd = open("Z.txt",O_RDWR);
    int* offset = (int *)shmat(shmd, 0, 0);
    if (fd != -1 && offset != (int *) -1){
      printf("Accessed file\n");
      lseek(fd,-1*(*offset),SEEK_END);
      char * f = (char *)malloc(sizeof(char)*(*offset));
      int w = read(fd,f,*offset);
      printf("Previous line: %s\n",f);
      *offset = strlen(s);
      lseek(fd, 0, SEEK_END);
      w = write(fd, s, strlen(s));
      printf("Wrote %d bytes.\n", w);
      close(fd);
      w = shmdt(offset);
      if(w)
	printf("%s\n", strerror(errno));
    }
    else {
      printf("File or Shared Memory Access Error\n");
      printf("%s\n", strerror(errno));
    }
    semb.sem_op = 1;
    semop(semd, &semb, 1);
  }
  else {
    printf("Semaphore Error Occured\n%s\n", strerror(errno));
  }
  write_stuff(fd,shmd,semd);
  return(0);
}
