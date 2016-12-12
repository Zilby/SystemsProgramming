#include "exeggcute.h"

int main(){
  printf("What would you like to do? ");
  char s[256];
  fgets(s,255,stdin);
  s[strlen(s)-1]=0;
  char *args[256];
  char *s1=s;
  char *s2;
  int i=0;
  while(s2=strsep(&s1," ")){
    args[i]=s2;
    i++;
  }
  args[i]=0;
  //printf("%s, %s, %s\n",args[0],args[1],args[2]);
  execvp(args[0],args);
}
