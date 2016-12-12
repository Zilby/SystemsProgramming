typedef struct song{ 
  char nam[256];
  char art[256];
  struct song *next;
} song;

int print_songs(song* t); //prints a linked list of songs
int print_song(song* t); //prints a single song
song *new_song(char* n, char* a); //creates a new song
song *insert_front(song* t,song* s); //inserts song to front of linked list of songs
song *insert_order(song* t,song* s); //inserts song in alpha-order into linked list of songs
song *free_songs(song* t); //frees all songs in a linked list
song *first_art_song(song* t,char* name);//finds first song in a linked list by the name of a particular artist
song *find_song(song* t,char* name); //finds pointer to song based on song name
song *remove_song(song* t,char* name); //removes and frees a song from a linked list

song **add_song(song**t,song* s); //adds song to table
song *find_song_t(song** t,char* name);//finds song in table given its name
song *find_art_t(song** t,char* name); //finds first song in table by an artist given their name
int print_letter(song** t,char c); //prints all songs starting with a certain letter
int print_art_songs(song** t,char* name); //prints all songs by a specified artist
int print_t_songs(song** t); //prints all songs in the table
int shuffle(song** t,int i); //randomly prints a given number of songs from the table
song** delete_song(song** t,char* name); //deletes a song from the table
int delete_table(song** t); //deletes and frees the table
