#ifndef LIST_H
#define LIST_H
#define MAX_FILE_NAME 100
// #define MAX_LINE 100

// types
typedef struct list List;
typedef struct list_node ListNode;

// operations

// create empty list
List *create_empty_list();

// add an element at the beginning of the list
void insert_into_the_list(List *l, char img[MAX_FILE_NAME], char descriptor[MAX_FILE_NAME], char location[MAX_FILE_NAME]);

// size of hte list
int size_list(List *l);

// check whether an element is in the list
int is_in_the_list(List *l, int v);

// check whether the list is empty
int is_empty(List *l);

// free memory
void free_list(List *l);

// show all elements of the list
void print_list(List *l);

int get_number_of_matches();

void run_extractor(char *query_descriptor, char *current_descriptor);

int match_images(List *l, char *descriptor_path, int n_locations);

#endif