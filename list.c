#include "list.h"
#include "location.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int match_images(List *l, char *descriptor_path, int n_locations)
{  
  int max_line = 100;
  char n_matches_str[max_line];
  int n_matches;
  FILE *fp;

  List *matches;
  matches = create_empty_list();

  LocationList *loc;
  loc = create_location_list();

  for (ListNode *p = l->first; p != NULL; p = p->next){
    char file[40] = "extractor/match.py ";
    char command[150] = "python3 ";
    strcat(command, file);
    strcat(command, descriptor_path);
    strcat(command, " ");
    strcat(command, p->descriptor_path);
    system(command);

    fp = fopen("query/matches", "rt");
        if(fp == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }
    fgets(n_matches_str, max_line, fp);
    n_matches = atoi(n_matches_str);
    fclose(fp);

    compare_match(loc, n_matches, p->location);

  }
  print_location_list(loc);
  return 0;
}
