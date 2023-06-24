#include "location.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structs -----

struct locations {
  LocationNode *first;
};

struct location_node {
  char location[MAX_FILE_NAME];
  int n_matches;
  LocationNode *next;
};

// operations ----

LocationList *create_empty_location_list() {
  LocationList *l = (LocationList *)malloc(sizeof(LocationList));
  l->first = NULL;
  return l;
}


LocationList *create_location_list()
{ 
  FILE *fp;
  char line[MAX_LINE];

  LocationList *locations;
  locations = create_empty_location_list();

  fp = fopen("./base/locations.txt", "rt");
  fgets(line, MAX_LINE, fp);
  insert_into_location_list(locations, strtok(line, "\n"), 0);

  while(!feof(fp)){
      fgets(line, MAX_LINE, fp);
      insert_into_location_list(locations, strtok(line, "\n"), 0);
  }

  return locations;
}


int locations_is_empty(LocationList *l) { return l->first == NULL; }

void insert_into_location_list(LocationList *l, char location[MAX_FILE_NAME], int n_matches) {
  LocationNode *node = (LocationNode *)malloc(sizeof(LocationNode));
  strcpy(node->location, location);
  node->n_matches = n_matches;
  node->next = l->first;
  l->first = node;
}

void free_location_list(LocationList *l) {
  LocationNode *p = l->first;
  while (p != NULL) {
    LocationNode *t = p->next; // keep the reference for the next node
    free(p);               // free the current node
    p = t;                 // go to the next node
  }
  free(l); // free the list structure
}

int size_location_list(LocationList *l) {
  int cnt = 0;
  for (LocationNode *p = l->first; p != NULL; p = p->next)
    cnt++;
  return cnt;
}

void print_location_list(LocationList *l) {
  for (LocationNode *p = l->first; p != NULL; p = p->next)
    printf("%s | %d \n", p->location, p->n_matches);
}

// void getBestLocations(LocationList *l, int n_loc)
// {
// }

int compare_match(LocationList *l, int matches, char *location)
{
  for (LocationNode *p = l->first; p != NULL; p = p->next)
  {
    if (strcmp(p->location, location)){
      if(matches > p->n_matches)
        p->n_matches = matches;
        return 0;
    }
  }
}

