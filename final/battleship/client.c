#include "battleship.h"

static void sighandler(int signo) {
  if (signo == SIGINT)
    quit();
}

int main(int argc, char **argv) {
  if(argc<=1){
    printf("Please enter an IP address that you would like to connect\nto after the program, such as ./client 127.0.0.1\n");
    quit();
  }
  signal(SIGINT, sighandler);
  //create socket
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  char buffer[256];
  char coors[256]="";
  int b;
  //bind to ip address and port
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(12321);
  inet_aton(argv[1], &(sock.sin_addr));
  bind(socket_id, (struct sockaddr*) &sock, sizeof(sock));
  //connect
  int i = connect(socket_id, (struct sockaddr*) &sock, sizeof(sock));
  if(i){
    printf("Connection Error %d : %s\n", i, strerror(errno));
    quit();
  }else{
    printf("Connected %d\n", i);
    int cont=1;
    printf("Waiting for opponent...\n");
    b = read(socket_id, buffer, sizeof(buffer));
    printf("%s would like to battle.\n",buffer);
    printf("Enter Name: ");
    fgets(buffer, sizeof(buffer), stdin);
    *(strchr(buffer, '\n')) = '\0';
    b = write(socket_id, buffer, sizeof(buffer));
    place_ships();
    while(cont){  
      receiving(socket_id,b,buffer,coors);
      cont=send_status(socket_id,b,buffer,coors,cont);
      if(cont){
	firing(socket_id,b,buffer,coors);
	cont=receive_status(socket_id,b,buffer,coors,cont);
      }
    }
  }
  //quit();
}

int quit() {
  //printf("\e[2J\e[H");
  //fflush(stdout);
  exit(0);
}
