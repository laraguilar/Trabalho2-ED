#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE 150

// read the index file and fill the images list 
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

// extract the descriptor file
void extractDescriptor(char *img_file, char *descriptor_path){
    char file[40] = "extractor/extractor.py ";
    char command[150] = "python3 ";

    strcat(command, file);
    strcat(command, img_file);
    strcat(command, " ");
    strcat(command, descriptor_path);

    system(command);
}

// generate a path for the descriptor
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

        char descriptor_path[MAX_FILE_NAME];
        char extractor_dir[MAX_FILE_NAME] = "query/descriptor";
        char filename[MAX_FILE_NAME] = "img";
        getDescriptorPath(descriptor_path, extractor_dir, filename);
        
        // extract the image descriptors
        extractDescriptor(img_query, descriptor_path);
        
        // get the most similar locations and save them into a file
        match_images(images, descriptor_path, n_location);

        free_list(images);
   }
   else {
      printf("Muitos argumentos inseridos.\n");
   }
    return 0;
}