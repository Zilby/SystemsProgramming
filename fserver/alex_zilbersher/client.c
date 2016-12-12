#include "fserver.h"

char line[100];
char zname[100];
int to_server;
int from_server;

int main(){    
    sprintf(zname,"%d",getpid());
    mkfifo(zname, 0644);
    printf("Connect to server\n");
 
    to_server = open("zilb",O_WRONLY);
    write(to_server,zname,sizeof(zname));
    
    printf("Waiting for response\n");

    from_server = open(zname,O_RDONLY);
    read(from_server,line,sizeof(line));
    remove(zname);
    printf("<client> received -%s-\n",line);
    remove(line);
    
    while(1) {
        printf("<client> enter test case: ");
        fgets(line,sizeof(line),stdin);
	if(strncmp("exit\n",line,sizeof("exit"))==0){
	  close(to_server);
	  close(from_server);
	  return 0;
	}
        line[strlen(line)-1]=0;
    
        write(to_server,line,sizeof(line));
    
        read(from_server,line,sizeof(line));
        printf("<client> received: -%s-\n",line);
    }
    close(to_server);
    close(from_server);
    return 0;
}
