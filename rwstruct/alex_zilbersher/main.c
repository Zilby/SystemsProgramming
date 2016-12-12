#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "reading.h"

int main(){
  readme** r;
  r=malloc(sizeof(readme)*10);
  r[0]=new_struct("Karkat",56);
  r[1]=new_struct("Aradia",45);
  r[2]=new_struct("Tavros",67);
  r[3]=new_struct("Sollux",78);
  r[4]=new_struct("Nepeta",34);
  r[5]=new_struct("Terezi",64);
  r[6]=new_struct("Vriska",88);
  r[7]=new_struct("Equius",90);
  r[8]=new_struct("Gamzee",12);
  r[9]=new_struct("Eridan",3);

  int b=add_structs(r);
  printf("\nBytes Written: %d\n",b);
  read_file_structs();
  print_entry(r);
  modify_entry(r);
  read_file_structs();
  free_structs(r);
  printf("\nTesting Completed\n");
}
