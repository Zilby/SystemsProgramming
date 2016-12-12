#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <errno.h>

int board[10][10];
int board2[10][10];

int print_board(int i);
int place_ship(int length,int i);
int place_ships();
int fire(char* coord,char* landed);
char* hit(char* coord);
int receiving(int sock, int b, char buffer[256], char temp[256]);
int firing(int sock, int b, char buffer[256], char coors[256]);
int taken(char* coord);
int lost();
int send_status(int sock, int b, char buffer[256], char coors[256], int cont);
int receive_status(int sock, int b, char buffer[256], char coors[256], int cont);

void modify(char *s); //This is probably temporary
