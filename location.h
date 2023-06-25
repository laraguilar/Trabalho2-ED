#ifndef LOCATION_H
#define LOCATION_H
#define MAX_FILE_NAME 100
#define MAX_LINE 100

// types
typedef struct locations LocationList;
typedef struct location_node LocationNode;

// operations

// create empty list
LocationList *create_empty_location_list();

LocationList *create_location_list();

// verify if is empty
int locations_is_empty(LocationList *l);

// add an element at the beginning of the list
void insert_into_location_list(LocationList *l, char location[MAX_FILE_NAME], int n_matches);

// free memory
void free_location_list(LocationList *l);

// show all elements of the list
void print_location_list(LocationList *l);

int location_is_in_the_list(LocationList *l, char *location);

LocationNode* getTail(LocationNode* head);

LocationNode* partition(LocationNode* head, LocationNode* end, LocationNode** newHead, LocationNode** newEnd);

LocationNode* quickSortRecur(LocationNode* head, LocationNode* end);

void quickSort(LocationList* list);

int getBestLocations(LocationList *l, int n_loc);

int compare_match(LocationList *l, int matches, char *location, char *img_path);

#endif