#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILE_NAME 100
// #define ANSI_COLOR_RED "\x1b[31m"
// #define ANSI_COLOR_RESET "\e[0;37m"

// struct Imagem
// {
//     char img_path[MAX_FILE_NAME];
//     char descriptor_path[MAX_FILE_NAME];
//     char location_name[MAX_FILE_NAME];
// };

char* getLocationName(char* location, char* folder_name){
    char line[MAX_FILE_NAME];
    char size[6];
    FILE *fp;
    int i;

    fp = fopen("locations.txt", "rt");
    if(fp == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }

    fgets(line, 99, fp);
    location = strtok(line, ";");
    
    if(strcmp(folder_name, location) == 0)
    {
        fclose(fp);
        return strtok(NULL, ";");
    }

    while(!feof(fp))
    {
        fgets(line, 99, fp);
        location = strtok(line, ";");
       if(strcmp(folder_name, location) == 0)
        {
            fclose(fp);
            return strtok(NULL, ";");
        }
    }
    fclose(fp);
    return 0;
}

char* getFileNameWithoutExtension(char *filename){
    for (int i = 0; i < strlen(filename); i++){
        if ( filename[i] == '.' ) {
            filename[i] = '\0';
            return filename;
        }
    }
}

char* getDescriptorPath(char* descriptor_path, char* extractor_dir, char* filename)
{
    strcat(descriptor_path, extractor_dir);
    strcat(descriptor_path, "/");
    strcat(descriptor_path, getFileNameWithoutExtension(filename));
    strcat(descriptor_path, ".txt");
    return descriptor_path;
}

int counter_img(DIR *dir, struct dirent *lsdir, struct dirent *lsimg){
    int imgcounter = 0;
    dir = opendir("./base/img");

    /* 
    scan all the directories and files from "img" folder and save them in a text file (.txt)
    */
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
            char command[150] = "mkdir ";

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
void create_descriptor(char *img_file, char *filename, char* extractor_dir, char *descriptor_path){
    char command[150] = "python3 ";
    char file[40] = "extractor/extractor_teste.py ";

    strcat(command, file);
    strcat(command, img_file);
    strcat(command, " ");
    strcat(command, descriptor_path);

    system(command);
}

int main(void)
{
    DIR *dir;
    struct dirent *lsdir, *lsimg;
    dir = opendir("./base/img");

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

            // create the extractor folder 
            char command[150] = "mkdir ";
            char extractor_dir[MAX_FILE_NAME] = "./base/extractor_";
            strcat(extractor_dir, folder_name);
            strcat(command, extractor_dir);
            system(command);

            // walks through images from the location folder
            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char imgext[MAX_FILE_NAME] = "";
                char filename[MAX_FILE_NAME] = "";

                strcpy(filename, lsimg->d_name);
                strcpy(imgext, filename);

                int backfolder1 = strcmp(imgext, "..");
                int samefolder1 = strcmp(imgext, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {
                    char img_file[MAX_FILE_NAME] = "";
                    strcat(img_file, img_path);
                    strcat(img_file, "/");
                    strcat(img_file, filename);
                    fprintf(fhist, "%s ", img_file);

                    char descriptor_path[MAX_FILE_NAME] = "";
                    getDescriptorPath(descriptor_path, extractor_dir, filename);

                    create_descriptor(img_file, filename, extractor_dir, descriptor_path);
                    fprintf(fhist, "%s ", descriptor_path);
                    
                    // char nameLocation[MAX_FILE_NAME]; 
                    // strcpy(nameLocation, identifyLocation(nameLocation, folder_name));
                    fprintf(fhist, "%s\n", folder_name);
                }
            }
            closedir(location);
        } 
    }
    closedir(dir);

    fclose(fhist);

    return 0;
}