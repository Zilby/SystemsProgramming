typedef struct readme{
  char nam[256];
  int num;
} readme;

readme* new_struct(char* n,int i);
int add_structs();
int read_file_structs();
int print_entry(readme** r);
int modify_entry(readme** r);
int free_structs(readme** r);
