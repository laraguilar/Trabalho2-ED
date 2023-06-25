#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h> 

#define MAX_FILE_NAME 70

// remove extension from the image file name 
char* getFileNameWithoutExtension(char *filename){
    for (int i = 0; i < strlen(filename); i++){
        if ( filename[i] == '.' ) {
            filename[i] = '\0';
            return filename;
        }
    }
}

// generate a descriptor path based on the filename
char* getDescriptorPath(char* descriptor_path, char* extractor_dir, char* filename)
{
    strcat(descriptor_path, extractor_dir);
    strcat(descriptor_path, "/");
    strcat(descriptor_path, getFileNameWithoutExtension(filename));
    return descriptor_path;
}

// count the quantity of images from de index file
int counter_img(DIR *dir, struct dirent *lsdir, struct dirent *lsimg){
    int imgcounter = 0;
    dir = opendir("./base/img");
    
    /*  scan all the directories and files from "img" folder and save them into a text file (.txt) */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        DIR *location;

        char img_path[MAX_FILE_NAME] = "./base/img/";
        char folder_name[MAX_FILE_NAME] = "";

        strcat(folder_name, lsdir->d_name);
        strcat(img_path, folder_name);
        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            location = opendir(img_path);

            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char imgext[MAX_FILE_NAME];
                char filename[MAX_FILE_NAME];

                strcpy(filename, lsimg->d_name);
                strcpy(imgext, filename);

                int backfolder1 = strcmp(imgext, "..");
                int samefolder1 = strcmp(imgext, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {           
                    imgcounter++;
                }
            }
            closedir(location);
        } 
    }
    closedir(dir);

    return imgcounter;
}

// create the descriptor file
void create_descriptor(char *img_path, char *descriptor_path){
    char command[150] = "python3 ";
    char file[40] = "extractor/extractor.py ";

    strcat(command, file);
    strcat(command, img_path);
    strcat(command, " ");
    strcat(command, descriptor_path);

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
        char img_path[MAX_FILE_NAME] = "./base/img/";
        char folder_name[MAX_FILE_NAME] = "";

        strcat(folder_name, lsdir->d_name);
        strcat(img_path, folder_name);
        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            // Command to create a new folder 

            // access the location folder
            location = opendir(img_path);
            fprintf(loc, "%s \n", folder_name);

            // create the extractor folder 
            char command[150] = "mkdir ";
            char extractor_dir[MAX_FILE_NAME] = "./base/extractor_";
            strcat(extractor_dir, folder_name);
            strcat(command, extractor_dir);
            system(command);

            // walks through images from the location folder
            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char filename[MAX_FILE_NAME] = "";

                strcpy(filename, lsimg->d_name);

                int backfolder1 = strcmp(filename, "..");
                int samefolder1 = strcmp(filename, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {
                    char img_file[MAX_FILE_NAME] = "";
                    strcat(img_file, img_path);
                    strcat(img_file, "/");
                    strcat(img_file, filename);
                    fprintf(fhist, "%s ", img_file);

                    // generate the descriptor path
                    char descriptor_path[MAX_FILE_NAME] = "";
                    getDescriptorPath(descriptor_path, extractor_dir, filename);

                    // run the python file
                    create_descriptor(img_file, descriptor_path);

                    fprintf(fhist, "%s ", descriptor_path);
                    fprintf(fhist, "%s\n", folder_name);
                }
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