#include "fserver.h"

int from_client;
int to_client;
char line[100];

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("\nServer Excommunicated\n");
    close(from_client);
    close(to_client);
    remove("zilb");
    exit(0);
  }
}

void modify(char *s){
  strncat(s,", the Zilb",strlen(s)+1);
}

int main(){
  signal(SIGINT, sighandler);
  printf("Ready to receive\n");
  while(1){
    mkfifo("zilb",0644);
    from_client=open("zilb",O_RDONLY);
    char line[100];

    int f=fork();
    if(!f){
      read(from_client, line, sizeof(line));

      printf("<child> sent data -%s-\n",line);

      to_client=open(line,O_WRONLY);
      
      remove(line);
      strncpy(line,"Message received Agent Z",sizeof(line));
      write(to_client,line,sizeof(line));
      
      while(1){
	read(from_client,line,sizeof(line));
	modify(line);
	printf("%s\n",line);
	write(to_client,line,sizeof(line));
      }
      //close(to_client);
      //close(from_client);
    }
    else{
      close(to_client);
      close(from_client);
      remove("zilb");
      exit(0);
    }
  }
}

