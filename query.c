#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"

#define MAX_LINE 150
#define PYTHON "python3 "
#define EXTRACTOR_FILE "extractor/extractor.py "
#define EXTRACTOR_DIR "query/descriptor"
#define FILENAME "extractor_query"

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
        fgets(line, MAX_LINE, fp);
        count++;

        char* img_path = createString(strtok(line, " "));
        char* descriptor_path = createString(strtok(NULL, " "));
        char* location = createString(strtok(NULL, "\n"));

        insert_into_the_list(images, img_path, descriptor_path, location);

        free(img_path);
        free(descriptor_path);
        free(location);
    }

    fclose(fp);
    return 0;
}


// extract the descriptor file
void extractDescriptor(char *img_file, char *descriptor_path){
    char* command = createString(PYTHON);
    concatString(&command, EXTRACTOR_FILE);
    
    concatString(&command, img_file);
    concatString(&command, " ");
    concatString(&command, descriptor_path);
    system(command);
    free(command);
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

        char *descriptor_path = getDescriptorPath(EXTRACTOR_DIR, "extractor_query.txt", 1);
        

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