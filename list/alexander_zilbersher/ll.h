typedef struct f {
    char c; 
    struct f *next;
  } foo;

int print_list(foo* h);
foo *insert_front(foo* h,char c);
foo *free_list(foo* h);
