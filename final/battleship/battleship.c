#include "battleship.h"

int print_board(int i){
  int x=0;
  int y=0;
  char s[4096]="   A B C D E F G H I J\n1 ";
  while(y<10){
    while(x<10){
      if(i==1){
	if(board[y][x]==0){
	  strcat(s," ~");
	}else if(board[y][x]==1){
	  strcat(s," #");
	}else if(board[y][x]==2){
	  strcat(s," X");
	}else if(board[y][x]==3){
	  strcat(s," @");
	}
      }else{
	if(board2[y][x]==0){
	  strcat(s," *");
	}else if(board2[y][x]==1){
	  strcat(s," @");
	}else if(board2[y][x]==2){
	  strcat(s," X");
	}
      }
      x++;
    }
    y++;
    if(y<10){
      char temp[256];
      if(y==9){
	sprintf(temp,"\n%d",y+1);
      }else{
	sprintf(temp,"\n%d ",y+1);
      }
      strcat(s,temp);
    }
    x=0;
  }
  printf("\n%s\n",s);
}
 
//ship sizes are 2,3,3,4,5
int place_ship(int length,int i){
  int x,y;
  printf("\nEnter top left coordinates for ship of length %d:",length);
  char coord[256];
  fgets(coord, 255, stdin);
  //strcat(coord,"extra");//to avoid seg faults
  printf("Enter h for horizontal or v for vertical orientation:");
  char orient[256];
  fgets(orient, 255, stdin);
  //strcat(orient,"extra");//to avoid seg faults
  if(coord[0]<97){
    y=coord[0]-65;
  }else{
    y=coord[0]-97;
  }
  x=coord[1]-49;
  if(coord[2]=='0'&&x==0){ //special case if 10 ie: 2 digits
    x=9;
  }
  if((orient[0]=='v'&&(x+length>10))||
     (orient[0]=='h'&&(y+length>10))||
      orient[0]==10||x>9||x<0||y>9||y<0){
    printf("Invalid Coordinates, please reenter\n");
    return place_ship(length,i);
  }
  else{
    int invalid=0;
    int l=length;
    int x1=x;
    int y1=y;
    while(l){
      if(i==1){
	if(board[x1][y1]==1){
	  invalid=1;
	}
      }else{
	if(board2[x1][y1]==1){
	  invalid=1;
	}
      }
      if(orient[0]=='h'){
	y1++;
      }else{
	x1++;
      }
      l--;
    }
    if(invalid){
      printf("Coordinates already occupied, please reenter\n");
      return place_ship(length,i);
    }else{
      while(length){
	if(i==1){
	  board[x][y]=1;
	}else{
	  board2[x][y]=1;
	}
	if(orient[0]=='h'){
	  y++;
	}else{
	  x++;
	}
	length--;
      }
    }
  }
  return 0;
}

int place_ships(){
  print_board(2);
  print_board(1);
  place_ship(2,1);
  print_board(2);
  print_board(1);
  place_ship(3,1);
  print_board(2);
  print_board(1);
  place_ship(3,1);
  print_board(2);
  print_board(1);
  place_ship(4,1);
  print_board(2);
  print_board(1);
  place_ship(5,1);
  print_board(2);
  print_board(1);
}

int fire(char* coord,char* landed){
  //printf("got to fire\n");
  //printf("coord: %s, landed: %s\n",coord,landed);
  int x,y;
  if(coord[0]<97){
    y=coord[0]-65;
  }else{
    y=coord[0]-97;
  }
  x=coord[1]-49;
  if(coord[2]=='0'&&x==0){ //special case if 10 ie: 2 digits
    x=9;
  }
  if(strcmp(landed,"y")==0){
    board2[x][y]=2;
  }else{
    board2[x][y]=1;
  }
}

char* hit(char* coord){
  int x,y;
  if(coord[0]<97){
    y=coord[0]-65;
  }else{
    y=coord[0]-97;
  }
  x=coord[1]-49;
  if(coord[2]=='0'&&x==0){ //special case if 10 ie: 2 digits
    x=9;
  }
  if(board[x][y]==1){
    board[x][y]=2;
    return "y";
  }else{
    board[x][y]=3;
    return "n";
  }
}

int receiving(int sock, int b, char buffer[256], char coors[256]){
  printf("Waiting for enemy to fire...\n");
  b = read(sock, buffer, sizeof(buffer));
  strcpy(coors,buffer);
  strcpy(buffer,hit(buffer));
  b = write(sock, buffer, sizeof(buffer));
  print_board(2);
  print_board(1);
  if(strcmp(buffer,"y")==0){
    printf("Enemy hit!: %s\n",coors);
  }else{
    printf("Enemy missed: %s\n",coors);
  }
}

int firing(int sock, int b, char buffer[256], char coors[256]){
  printf("Prepared to fire on coordinates: "); 
  fgets(buffer, sizeof(buffer), stdin);
  *(strchr(buffer, '\n')) = '\0';
  if(taken(buffer)==0){
    printf("Already fired upon coordinates %s, try again.\n",buffer);
    return firing(sock,b,buffer,coors);
  }
  if(taken(buffer)==2){
    printf("Invalid coordinates %s, try again.\n",buffer);
    return firing(sock,b,buffer,coors);
  }
  strcpy(coors,buffer);
  b = write(sock, buffer, sizeof(buffer));
  b = read(sock, buffer, sizeof(buffer));
  fire(coors,buffer);
  print_board(2);
  print_board(1);
  if(strcmp(buffer,"n")==0){
    printf("Missed...\n");
  }else{
    printf("Hit!\n");
  }
}

int taken(char* coord){
  int x,y;
  if(coord[0]<97){
    y=coord[0]-65;
  }else{
    y=coord[0]-97;
  }
  x=coord[1]-49;
  if(coord[2]=='0'&&x==0){ //special case if 10 ie: 2 digits
    x=9;
  }
  if(x>9||x<0||y>9||y<0){
    return 2;
  }else if(board2[x][y]==0){
    return 1;
  }else{
    return 0;
  }
}

int lost(){
  int sunk=1;
  int x=10;
  int y=10;
  while(y){
    while(x){
      //printf("x:%d, y:%d, coor:%d\n",x,y,board[y-1][x-1]);
      if(board[y-1][x-1]==1){
	sunk=0;
      }x--;
    }
    x=10;
    y--;
  }
  return sunk;
}

int send_status(int sock, int b, char buffer[256], char coors[256], int cont){
  if(lost()){
    strcpy(buffer,"lost");
    cont=0;
    printf("You Lose!\n");
  }else{
    strcpy(buffer,"cont");
  }
  b = write(sock, buffer, sizeof(buffer));
  return cont;
}

int receive_status(int sock, int b, char buffer[256], char coors[256], int cont){
  b = read(sock, buffer, sizeof(buffer));
  if(strcmp(buffer,"lost")==0){
    cont=0;
    printf("You Win!\n");
  }
  return cont;
}
