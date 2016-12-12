#include "battleship.h"

int main() {
  char buffer[256];
  int b;
  char coors[256]="";
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port = htons(12321);
  listener.sin_addr.s_addr = INADDR_ANY;
  bind (socket_id, (struct sockaddr*) &listener, sizeof(listener));
  listen(socket_id, 1);
  printf("Waiting for opponent to connect...\n");
  int socket_client = accept(socket_id, NULL, NULL);
  printf("Connected %d\n", socket_client);
  int cont=1;

  printf("Enter Name: ");
  fgets(buffer, sizeof(buffer), stdin);
  *(strchr(buffer, '\n')) = '\0';
  b = write(socket_client, buffer, sizeof(buffer));
  printf("waiting for opponent...\n");
  b = read(socket_client, buffer, sizeof(buffer));
  printf("%s would like to battle.\n",buffer);
  place_ships();
  while(cont){
    firing(socket_client,b,buffer,coors);
    cont=receive_status(socket_client,b,buffer,coors,cont);
    if(cont){
      receiving(socket_client,b,buffer,coors);
      cont=send_status(socket_client,b,buffer,coors,cont);
    }
  }
}

int quit() {
  exit(0);
}
