#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE 150

int generateImagesList(List *images, char *histogram_extractor)
{
    FILE *fp;
    char line[MAX_LINE];
    int qt_images;
    int count = 0; 

    fp = fopen(histogram_extractor, "rt");
        if(fp == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }

    fgets(line, MAX_LINE, fp);
    qt_images = atoi(line);

    while (!feof(fp) & count < qt_images)
    {
        char img_path[MAX_FILE_NAME];
        char descriptor_path[MAX_FILE_NAME];
        char location[MAX_FILE_NAME];

        fgets(line, MAX_LINE, fp);
        count++;

        strcpy(img_path, strtok(line, " "));
        strcpy(descriptor_path, strtok(NULL, " "));
        strcpy(location, strtok(NULL, "\n"));
        insert_into_the_list(images, img_path, descriptor_path, location);
    }

    fclose(fp);
    return 0;
}

// create the descriptor file
void createDescriptor(char *img_file, char *descriptor_path){
    char file[40] = "extractor/extractor_teste.py ";

    char command[150] = "python3 ";
    strcat(command, file);
    strcat(command, img_file);
    strcat(command, " ");
    strcat(command, descriptor_path);

    system(command);
}

char* query(char *descriptor_path, List *images){

    // for (ListNode *p = images->first; p != NULL; p = p->next)
    //     printf("%s ", p->img_path);

    // char file[40] = "extractor/match.py ";
    // char command[150] = "python3 ";
    // strcat(command, file);
    // strcat(command, descriptor_path);
    // system(command);

}

char* getDescriptorPath(char* descriptor_path, char* extractor_dir, char* filename)
{
    strcat(descriptor_path, extractor_dir);
    strcat(descriptor_path, "/");
    strcat(descriptor_path, filename);
    strcat(descriptor_path, ".txt");
    return descriptor_path;
}

int main(int argc, char *argv[])
{
    // verify the quantity of arguments passed by command line
    if( argc <= 2 ) {
      printf("Faltou argumentos.");
   }
   else if( argc > 2 & argc < 5) {
        // get data from command line
        char* img_query = argv[1];
        char* histogram_extractor = argv[2];
        int n_location = atoi(argv[3]);

        //create a linked list with the images information
        List *images;
        images = create_empty_list();
        generateImagesList(images, histogram_extractor);
        
        // create a linked list with the matches information
        // List *matches;
        // matches = create_empty_list();

        char descriptor_path[MAX_FILE_NAME];
        char extractor_dir[MAX_FILE_NAME] = "query/extractor";
        char filename[MAX_FILE_NAME] = "img";
        getDescriptorPath(descriptor_path, extractor_dir, filename);
        
        createDescriptor(img_query, descriptor_path);
        
        match_images(images, descriptor_path, n_location);

        free_list(images);
   }
   else {
      printf("Muitos argumentos inseridos.\n");
   }

    return 0;
}