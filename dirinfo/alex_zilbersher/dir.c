#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "dir.h"

DIR* get_dir(){
  DIR* d;
  char a[256];
  printf("Statistics for directory: ");
  scanf("%s", a);
  d=opendir(a);
  if(d==0){
    printf("Directory not found\nShowing results for current directory\n");
    return opendir(".");
  }
  return d;
}

int get_file_sizes(DIR* d){
  rewinddir(d);
  int sum=0;
  struct dirent* entry;
  struct stat s;
  while(entry=readdir(d)){
    if(entry->d_type!=4&&entry->d_type!=0){
      stat(entry->d_name,&s);
      sum+=s.st_size;
    }
  }return sum;
}

int print_files(DIR* d){
  rewinddir(d);
  struct dirent* entry;
  printf("Directories: \n");
  while(entry=readdir(d)){
    if(entry->d_type==4||entry->d_type==0){
      printf("%s\n",entry->d_name);
    }
  }
  rewinddir(d);
  printf("Regular files: \n");
  while(entry=readdir(d)){
    if(entry->d_type!=4&&entry->d_type!=0){
      printf("%s\n",entry->d_name);
    }
  }
  return 0;
}
