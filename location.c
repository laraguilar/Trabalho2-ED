#include "location.h"
#include "functions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structs -----

struct locations {
  LocationNode *first;
};

struct location_node {
  char *location;
  int n_matches;
  char *img_path;
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
  insert_into_location_list(locations, strtok(line, " "), 0);

  while(!feof(fp)){
      fgets(line, MAX_LINE, fp);
      insert_into_location_list(locations, strtok(line, " "), 0);
  }

  return locations;
}


int locations_is_empty(LocationList *l) { return l->first == NULL; }

void insert_into_location_list(LocationList *l, char location[MAX_FILE_NAME], int n_matches) {
  LocationNode *node = (LocationNode *)malloc(sizeof(LocationNode));
  concatString(node->location, location);
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

int location_is_in_the_list(LocationList *l, char *location)
{
  for (LocationNode *p = l->first; p != NULL; p = p->next)
  {
    if(strcmp(location, p->location) == 0)
      return 1;
  }
  return 0;
}

LocationNode* getTail(LocationNode* head) {
    LocationNode* current = head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

LocationNode* partition(LocationNode* head, LocationNode* end, LocationNode** newHead, LocationNode** newEnd) {
    LocationNode* pivot = end;
    LocationNode* prev = NULL;
    LocationNode* current = head;
    LocationNode* tail = pivot;

    while (current != pivot) {
        if (current->n_matches > pivot->n_matches) {
            if (*newHead == NULL)
                *newHead = current;

            prev = current;
            current = current->next;
        } else {
            if (prev)
                prev->next = current->next;

            LocationNode* temp = current->next;
            current->next = NULL;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }

    if (*newHead == NULL)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

// recursive part of the quick sort
LocationNode* quickSortRecur(LocationNode* head, LocationNode* end) {
    if (!head || head == end)
      return head;

    LocationNode* newHead = NULL;
    LocationNode* newEnd = NULL;

    LocationNode* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        LocationNode* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

// sort the list by number of matches using the quick method
void quickSort(LocationList* list) {
    list->first = quickSortRecur(list->first, getTail(list->first));
}

// sort the list and save the file name on txt file
int getBestLocations(LocationList *l, int n_loc)
{
  quickSort(l);  
  // print_location_list(l);
  LocationNode *current = l->first;

  FILE *fp;
  fp = fopen("./results/result.txt", "wt");
  if(fp == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }

  for(int i = 0; i < n_loc; i++){
    fprintf(fp, "%s \n", current->img_path);  
    current = current->next;
  }
  fclose(fp);
  printf("Resultado no arquivo results/result.txt");
  return 0;
}

int compare_match(LocationList *l, int matches, char *location, char *img_path)
{
  for (LocationNode *p = l->first; p != NULL; p = p->next)
  { 
    if (strcmp(p->location, location) == 0){
      if (matches > p->n_matches)
      {
        p->n_matches = matches;
        strcpy(p->img_path, img_path);
        return 1;
      }      
    }
  }
  return 0;
}
