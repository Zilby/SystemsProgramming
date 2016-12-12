#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "reading.h"

readme* new_struct(char* n,int i){ 
  readme* r;
  r=(readme*)malloc(sizeof(readme));
  strcpy(r->nam,n);
  r->num=i;
  return r;
}

int add_structs(readme** r){
  int b=0;
  int fd=open("read.txt",O_WRONLY | O_TRUNC);
  int i=0;
  while(r[i]){
    b+=write(fd,r[i],sizeof(readme));
    i++;
  }
  return b;
}

int read_file_structs(){
  int fd=open("read.txt",O_RDONLY);
  readme line;
  int c;
  int i=0;
  while(i<10){
    c=read(fd,&line,sizeof(readme));
    printf("%d: Bytes Read: %d Num: %d, Name: %s\n",i,c,line.num,line.nam);
    i++;
  }
  return 0;
}

int print_entry(readme** r){
  printf("\nPlease input entry to retrieve: ");
  int i;
  scanf("%d",&i);
  int fd=open("read.txt",O_RDONLY);
  lseek(fd,i*sizeof(readme),SEEK_SET);
  readme line;
  int c;
  c=read(fd,&line,sizeof(readme));
  printf("%d: Bytes Read: %d Num: %d, Name: %s\n",i,c,line.num,line.nam);
}

int modify_entry(readme** r){
  printf("\nPlease input entry to modify: ");
  int i;
  scanf("%d",&i);
  strcpy(r[i]->nam,"Feferi");
  r[i]->num=33;
  add_structs(r);
}

int free_structs(readme** r){
  int i=0;
  while(r[i]){
    free(r[i]);
    i++;
  }
  free(r);
  return 0;
}
