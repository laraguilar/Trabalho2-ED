#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h> 
#include <unistd.h>

#define PYTHON "python3 "

// count the quantity of images from de index file
int counter_img(DIR *dir, struct dirent *lsdir, struct dirent *lsimg){
    int imgcounter = 0;
    dir = opendir("./base/img");
    
    /*  scan all the directories and files from "img" folder and save them into a text file (.txt) */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        DIR *location;

        char *folder_name = createString(lsdir->d_name);

        char *img_path= createString("./base/img/");
        concatString(&img_path, folder_name);
        
        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            location = opendir(img_path);

            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char *filename = createString(lsimg->d_name);

                int backfolder1 = strcmp(filename, "..");
                int samefolder1 = strcmp(filename, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {           
                    imgcounter++;
                }
                free(filename);
            }
            closedir(location);
        } 
        free(folder_name);
        free(img_path);
    }
    closedir(dir);

    return imgcounter;
}

// create the descriptor file
void create_descriptor(char *img_path, char *descriptor_path){
    char *command = createString(PYTHON);
    char *file = createString("extractor/extractor.py ");

    concatString(&command, file);
    concatString(&command, img_path);
    concatString(&command, " ");
    concatString(&command, descriptor_path);

    system(command);
}

int main(void)
{   
    // time_t begin = time(NULL);

    //create the dir variable
    DIR *dir;
    struct dirent *lsdir, *lsimg;
    dir = opendir("./base/img");

    // create the file that save the locations (used on query after)
    FILE *loc;
    loc = fopen("./base/locations.txt", "wt");
    if(loc == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }

    // create the index file 
    FILE *fhist;
    fhist = fopen("index_histogram-extractor.txt", "w");
    if(fhist == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }
    fprintf(fhist, "%d\n", counter_img(dir, lsdir, lsimg));

    /* 
    scan all the directories and files from "img" folder and save them in a text file (.txt)
    */
    while (( lsdir = readdir(dir) ) != NULL )
    {
        DIR *location;
        char *folder_name = createString(lsdir->d_name);

        char *img_path= createString("./base/img/");
        concatString(&img_path, folder_name);

        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            // Command to create a new folder 

            // access the location folder
            location = opendir(img_path);
            fprintf(loc, "%s \n", folder_name);

            // create the extractor folder 
            char* extractor_dir = createString("./base/extractor_");
            concatString(&extractor_dir, folder_name);

            mkdir(extractor_dir);

            // walks through images from the location folder
            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char *filename = createString(lsimg->d_name);

                int backfolder1 = strcmp(filename, "..");
                int samefolder1 = strcmp(filename, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {
                    char* img_file = createString(img_path);
                    concatString(&img_file, "/");
                    concatString(&img_file, filename);

                    fprintf(fhist, "%s ", img_file);

                    // generate the descriptor path
                    char* descriptor_path = getDescriptorPath(extractor_dir, filename, 0);

                    // run the python file
                    create_descriptor(img_file, descriptor_path);

                    fprintf(fhist, "%s ", descriptor_path);
                    fprintf(fhist, "%s\n", folder_name);

                    free(img_file);
                    free(descriptor_path);
                }
                free(filename);
            }
            closedir(location);
        }
    }
    closedir(dir);
    fclose(loc);
    fclose(fhist);

    // time_t end = time(NULL);
 
    // // calcula o tempo decorrido encontrando a diferença (end - begin)
    // int time = end - begin;
    // printf("The elapsed time is %d seconds", time);
 
    return 0;
}