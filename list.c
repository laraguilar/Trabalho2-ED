#include "list.h"
#include "location.h"
#include "functions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PYTHON "python3 "
#define MATCH "extractor/match.py "

// structs -----

struct list {
  ListNode *first;
};

struct list_node {
  char img_path[MAX_FILE_NAME];
  char descriptor_path[MAX_FILE_NAME];
  char location[MAX_FILE_NAME];
  ListNode *next;
};

// operations ----

List *create_empty_list() {
  List *l = (List *)malloc(sizeof(List));
  l->first = NULL;
  return l;
}

int is_empty(List *l) { return l->first == NULL; }

void insert_into_the_list(List *l, char img[MAX_FILE_NAME], char descriptor[MAX_FILE_NAME], char location[MAX_FILE_NAME]) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  strcpy(node->img_path, img);
  strcpy(node->descriptor_path, descriptor);
  strcpy(node->location, location);
  node->next = l->first;
  l->first = node;
}

void free_list(List *l) {
  ListNode *p = l->first;
  while (p != NULL) {
    ListNode *t = p->next; // keep the reference for the next node
    free(p);               // free the current node
    p = t;                 // go to the next node
  }
  free(l); // free the list structure
}

int size_list(List *l) {
  int cnt = 0;
  for (ListNode *p = l->first; p != NULL; p = p->next)
    cnt++;
  return cnt;
}

void print_list(List *l) {
  for (ListNode *p = l->first; p != NULL; p = p->next)
    printf("%s ", p->img_path);
  printf("\n");
}

// read the file and get the number
int get_number_of_matches(){
  char line[MAX_LINE];
  FILE *fp;

  fp = fopen("query/matches", "rt");
  if(fp == NULL) {
    printf("Erro ao criar arquivo"); 
    return 0;
  }

  fgets(line, MAX_LINE, fp);
  fclose(fp);
 
  return atoi(line);
}

// run the python file
void run_extractor(char *query_descriptor, char *current_descriptor){
  char* command =  createString(PYTHON);
  concatString(&command, MATCH);
  concatString(&command, query_descriptor);
  concatString(&command, " ");
  concatString(&command, current_descriptor);
  system(command);
  free(command);
}

int match_images(List *l, char *descriptor_path, int n_locations)
{
  int n_matches;

  // create a location list with the name and the best number of matches
  LocationList *loc;
  loc = create_location_list();

  // iterate the image list
  for (ListNode *p = l->first; p != NULL; p = p->next){

    // compare the two images and save into a txt file
    run_extractor(descriptor_path, p->descriptor_path);

    // get the number of matches 
    n_matches = get_number_of_matches();

    // printf("%s %d\n", p->location, n_matches);

    // compare the matches from a location 
    compare_match(loc, n_matches, p->location, p->img_path);
  }

  // select the N most similars locations
  getBestLocations(loc, n_locations);

  free_location_list(loc);
  return 0;
}