#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "dir.h"

int main(){
  DIR* d;
  d=get_dir();
  printf("Total Diectory Size: %d Bytes\n",get_file_sizes(d));
  print_files(d);
  closedir(d);
}
